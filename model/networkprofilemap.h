#ifndef NETWORKPROFILEMAP_H
#define NETWORKPROFILEMAP_H

#include <QByteArray>
#include <QFile>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QString>
#include "networkprofile.h"

class NetworkProfileMap {
private:
	QMap<QString, NetworkProfile> mapProfiles;

public:
	NetworkProfileMap();

	void put(NetworkProfile profile);
	NetworkProfile & get(const QString & key);
	QList<QString> getKeys(void) const;
	QList<NetworkProfile> getValues(void) const;

	// QMap<QString, NetworkProfile> & getMap(void);
	void writeJSON(const QString & filename) const;
	void readJSON(const QString & filename);
};

#endif // NETWORKPROFILEMAP_H
