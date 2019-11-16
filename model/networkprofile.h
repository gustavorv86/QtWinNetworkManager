#ifndef NETWORKPROFILE_H
#define NETWORKPROFILE_H

#include <QMap>
#include <QString>

class NetworkProfile {
private:
	QString name;
	QString ipAddr;
	QString netmask;
	QString gateway;
	QString dns1;
	QString dns2;
	bool dhcp;

public:
	NetworkProfile();
	NetworkProfile(const QString & name, const QString & ipAddr, const QString & netmask, const QString & gateway, const QString & dns1, const QString & dns2, bool dhcp);
	NetworkProfile(const QMap<QString, QString> & map);

	const QString & getName(void) const;
	const QString & getIpAddr(void) const;
	const QString & getNetmask(void) const;
	const QString & getGateway(void) const;
	const QString & getDns1(void) const;
	const QString & getDns2(void) const;
	bool isDhcp(void) const;

	void setName(const QString & name);
	void setIpAddr(const QString & ipAddr);
	void setNetmask(const QString & netmask);
	void setGateway(const QString & gateway);
	void setDns1(const QString & dns1);
	void setDns2(const QString & dns2);
	void setDhcp(bool dhcp);

};

#endif // NETWORKPROFILE_H
