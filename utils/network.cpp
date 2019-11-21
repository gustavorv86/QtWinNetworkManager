#include "network.h"

const QString Network::CMD = "c:\\Windows\\System32\\cmd.exe";
const QString Network::NETSH = "c:\\Windows\\System32\\netsh.exe";
const QString Network::NETSH_GET_INTERFACES = NETSH + " interface show interface";

void Network::initializeInterfaces(void) {
    QProcess proc;
    QString cmd = Network::CMD + " /c " + NETSH_GET_INTERFACES;
    proc.start(cmd);
    proc.waitForFinished();
    QString output(proc.readAllStandardOutput());

    QStringList lines = output.split("\r\n");

    int size = lines.size();

    for(int i=3; i<size; i++) {
        QString interface = lines[i];
        interface = interface.replace("Enabled", "");
        interface = interface.replace("Habilitado", "");
        interface = interface.replace("Disabled", "");
        interface = interface.replace("Deshabilitado", "");
        interface = interface.replace("Connected", "");
        interface = interface.replace("Conectado", "");
        interface = interface.replace("Disconnected", "");
        interface = interface.replace("Desconectado", "");
        interface = interface.replace("Dedicated", "");
        interface = interface.replace("Dedicado", "");
        interface = interface.trimmed();
        if(!interface.isEmpty()) {
            this->listInterfaces.append(interface);
        }
    }

    this->listInterfaces.sort();
}

Network::Network() {
    this->initializeInterfaces();
    this->selectInterface = "";
}

Network::Network(const QString & interface) {
    this->initializeInterfaces();
    this->setInterface(interface);
}

const QStringList & Network::getInterfaces(void) const {
    return this->listInterfaces;
}

void Network::setInterface(int index) {
    if(0 <= index && index < this->listInterfaces.size()) {
        this->selectInterface = this->listInterfaces[index];
    } else {
        Logger::getInstance().warning("Invalid index interface " + QString(index));
    }
}

void Network::setInterface(const QString & interface) {
    if(listInterfaces.contains(interface)) {
        this->selectInterface = interface;
    } else {
        Logger::getInstance().warning("Invalid interface " + interface);
    }
}

void Network::dhcp() const {
    if(this->selectInterface.isEmpty()) {
        Logger::getInstance().warning("Interface is not selected. Abort");
        return;
    }

	QString cmd;
	QProcess proc;

    QString outputStr;
    QString errorStr;

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip set address \"" + this->selectInterface + "\" source=dhcp";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    Logger::getInstance().info(cmd + " [STDOUT]: " + outputStr.toUtf8());
    Logger::getInstance().info(cmd + " [STDERR]: " + errorStr.toUtf8());

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip set dnsservers \"" + this->selectInterface + "\" source=dhcp";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    Logger::getInstance().info(cmd + " [STDOUT]: " + outputStr.toUtf8());
    Logger::getInstance().info(cmd + " [STDERR]: " + errorStr.toUtf8());
}

void Network::staticConfig(QString ip, QString netmask, QString gateway, QString dns1, QString dns2) const {
    if(this->selectInterface.isEmpty()) {
        Logger::getInstance().warning("Interface is not selected. Abort");
        return;
    }

	QString cmd;
	QProcess proc;

    QString outputStr;
    QString errorStr;

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip set address \"" + this->selectInterface + "\" static " + ip + " " + netmask + + " " + gateway + "";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    Logger::getInstance().info(cmd + " [STDOUT]: " + outputStr.toUtf8());
    Logger::getInstance().info(cmd + " [STDERR]: " + errorStr.toUtf8());

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip delete dns \"" + this->selectInterface + "\"";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    Logger::getInstance().info(cmd + " [STDOUT]: " + outputStr.toUtf8());
    Logger::getInstance().info(cmd + " [STDERR]: " + errorStr.toUtf8());

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip add dns \"" + this->selectInterface + "\" addr=\"" + dns1 + "\"";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    Logger::getInstance().info(cmd + " [STDOUT]: " + outputStr.toUtf8());
    Logger::getInstance().info(cmd + " [STDERR]: " + errorStr.toUtf8());

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip add dns \"" + this->selectInterface + "\" addr=\"" + dns2 + "\"";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    Logger::getInstance().info(cmd + " [STDOUT]: " + outputStr.toUtf8());
    Logger::getInstance().info(cmd + " [STDERR]: " + errorStr.toUtf8());
}
