#ifndef NETWORKPROFILELIST_H
#define NETWORKPROFILELIST_H

#include <QByteArray>
#include <QFile>
#include <QLinkedList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "networkprofile.h"

class NetworkProfileList {
private:
	QLinkedList<NetworkProfile> listProfiles;

public:
	NetworkProfileList();

	QLinkedList<NetworkProfile> getList(void);
	void toJSON(const QString & filename) const;
};

#endif // NETWORKPROFILELIST_H
