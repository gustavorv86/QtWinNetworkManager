#include "network.h"

const QString Network::CMD = "c:\\Windows\\System32\\cmd.exe";
const QString Network::NETSH = "c:\\Windows\\System32\\netsh.exe";
const QString Network::INTERFACE = "Ethernet";

Network::Network(const QString & interfaceName) {
	this->interfaceName = interfaceName;
}

void Network::dhcp() {
	/*
		netsh interface ip set address "Local Area Connection" source=dhcp
		netsh interface ip set dnsservers "Local Area Connection" source=dhcp
	*/
	QString cmd;
	QProcess proc;

	cmd = Network::CMD + " /c " + Network::NETSH + " interface ip set address \"" + this->interfaceName + "\" source=dhcp 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();

	cmd = Network::CMD + " /c " + Network::NETSH + " interface ip set dnsservers \"" + this->interfaceName + "\" source=dhcp 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();
}

void Network::staticConfig(QString ip, QString netmask, QString gateway, QString dns1, QString dns2) {
	/*
		netsh interface ip set address "Local Area Connection" static XX.XX.XX.XX 255.255.255.0 XX.XX.XX.YY
		netsh interface ip delete dns "Local Area Connection" all
		netsh interface ip add dns "Local Area Connection" addr="8.8.4.4"
		netsh interface ip add dns "Local Area Connection" addr="8.8.8.8"
	 */
	QString cmd;
	QProcess proc;

	cmd = Network::CMD + " /c " + Network::NETSH + " interface ip set address \"" + this->interfaceName + "\" static " + ip + " " + netmask + + " " + gateway + " 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();

	cmd = Network::CMD + " /c " + Network::NETSH + " interface ip delete dns \"" + this->interfaceName + "\" all 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();

	cmd = Network::CMD + " /c " + Network::NETSH + " interface ip add dns \"" + this->interfaceName + "\" addr=\"" + dns1 + "\" 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();

	cmd = Network::CMD + " /c " + Network::NETSH + " interface ip add dns \"" + this->interfaceName + "\" addr=\"" + dns2 + "\" 1>> output.txt 2>> error.txt";
	proc.start(cmd);
	proc.waitForFinished();
}

