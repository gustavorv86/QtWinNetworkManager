#include "networkprofilelist.h"

NetworkProfileList::NetworkProfileList() {
	this->listProfiles = QLinkedList<NetworkProfile>();
}

QLinkedList<NetworkProfile> NetworkProfileList::getList(void) {
	return this->listProfiles;
}

void NetworkProfileList::toJSON(const QString & filename) const {
	QJsonObject jParent;

	foreach(const NetworkProfile & profile, this->listProfiles) {
		QJsonObject jChild;

		jChild["ipAddr"] = profile.getIpAddr();
		jChild["netmask"] = profile.getNetmask();
		jChild["gateway"] = profile.getGateway();
		jChild["dns1"] = profile.getDns1();
		jChild["dns2"] = profile.getDns2();

		QString name = profile.getName();
		jParent[name] = jChild;
	}

	QJsonDocument jDoc(jParent);

	QFile saveFile(filename);
	saveFile.write(jDoc.toJson());
}

void fromJSON(const QString & filename) {
	QFile loadFile(filename);

	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Couldn't open save file.");
		return;
	}

	QByteArray saveData = loadFile.readAll();
	QJsonDocument jDoc(QJsonDocument::fromJson(saveData));

	QJsonObject jParent = jDoc.object();

	/** TODO: Add values to LinkedList **/
}
