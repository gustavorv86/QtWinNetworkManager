#ifndef NETWORK_H
#define NETWORK_H

#include <QString>
#include <QProcess>

class Network {
private:
	static const QString CMD;
	static const QString NETSH;
	static const QString INTERFACE;

	QString interfaceName;
public:
	Network(const QString & interfaceName);

	void dhcp();
	void staticConfig(QString ip, QString netmask, QString gateway, QString dns1, QString dns2);
};

#endif // NETWORK_H
