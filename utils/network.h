#ifndef NETWORK_H
#define NETWORK_H

#include <QFile>
#include <QString>
#include <QProcess>

#include "utils/logger.h"

class Network {
private:
	static const QString CMD;
	static const QString NETSH;
    static const QString NETSH_GET_INTERFACES;
	static const QString INTERFACE;

    QStringList listInterfaces;
    QString selectInterface;

    void initializeInterfaces(void);

public:
    Network();
    Network(const QString & interface);

    const QStringList & getInterfaces(void) const;
    void setInterface(int index);
    void setInterface(const QString & name);
    void dhcp() const;
    void staticConfig(QString ip, QString netmask, QString gateway, QString dns1, QString dns2) const;
};

#endif // NETWORK_H
