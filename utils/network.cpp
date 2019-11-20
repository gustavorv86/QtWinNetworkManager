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
        qWarning() << "Invalid index interface " << index;
    }
}

void Network::setInterface(const QString & interface) {
    if(listInterfaces.contains(interface)) {
        this->selectInterface = interface;
    } else {
        qWarning() << "Invalid interface " << interface;
    }
}

void Network::dhcp() const {
    if(this->selectInterface.isEmpty()) {
        qWarning() << "Interface is not selected. Abort ";
        return;
    }

    QFile outputFile("output.txt");
    if (! outputFile.open(QIODevice::WriteOnly)) {
        qCritical() << "Cannot open output.txt file";
        return;
    }

    QFile errorFile("error.txt");
    if (! errorFile.open(QIODevice::WriteOnly)) {
        qCritical() << "Cannot open error.txt file";
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

    outputFile.write(outputStr.toUtf8());
    errorFile.write(errorStr.toUtf8());

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip set dnsservers \"" + this->selectInterface + "\" source=dhcp";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    outputFile.write(outputStr.toUtf8());
    errorFile.write(errorStr.toUtf8());

    outputFile.close();
    errorFile.close();
}

void Network::staticConfig(QString ip, QString netmask, QString gateway, QString dns1, QString dns2) const {
    if(this->selectInterface.isEmpty()) {
        qWarning() << "Interface is not selected. Abort ";
        return;
    }

    QFile outputFile("output.txt");
    if (! outputFile.open(QIODevice::WriteOnly)) {
        qCritical() << "Cannot open output.txt file";
        return;
    }

    QFile errorFile("error.txt");
    if (! errorFile.open(QIODevice::WriteOnly)) {
        qCritical() << "Cannot open error.txt file";
        return;
    }

	QString cmd;
	QProcess proc;

    QString outputStr;
    QString errorStr;

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip set address \"" + this->selectInterface + "\" static " + ip + " " + netmask + + " " + gateway + " 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    outputFile.write(outputStr.toUtf8());
    errorFile.write(errorStr.toUtf8());

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip delete dns \"" + this->selectInterface + "\" all 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    outputFile.write(outputStr.toUtf8());
    errorFile.write(errorStr.toUtf8());

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip add dns \"" + this->selectInterface + "\" addr=\"" + dns1 + "\" 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    outputFile.write(outputStr.toUtf8());
    errorFile.write(errorStr.toUtf8());

    cmd = Network::CMD + " /c " + Network::NETSH + " interface ip add dns \"" + this->selectInterface + "\" addr=\"" + dns2 + "\" 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();

    outputStr = proc.readAllStandardOutput();
    errorStr = proc.readAllStandardError();

    outputFile.write(outputStr.toUtf8());
    errorFile.write(errorStr.toUtf8());

    outputFile.close();
    errorFile.close();
}
