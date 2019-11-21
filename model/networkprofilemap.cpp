#include "networkprofilemap.h"

NetworkProfileMap::NetworkProfileMap() {
	this->mapProfiles = QMap<QString, NetworkProfile>();
}

void NetworkProfileMap::put(NetworkProfile profile) {
	this->mapProfiles[profile.getName()] = profile;
}

NetworkProfile & NetworkProfileMap::get(const QString & key) {
	return this->mapProfiles[key];
}

int NetworkProfileMap::remove(const QString & key) {
	return this->mapProfiles.remove(key);
}

QList<QString> NetworkProfileMap::getKeys(void) const {
	return this->mapProfiles.keys();
}

QList<NetworkProfile> NetworkProfileMap::getValues(void) const {
	return this->mapProfiles.values();
}

bool NetworkProfileMap::writeJSON(const QString & filename) const {

	QJsonObject jParent;
	foreach(const NetworkProfile & profile, this->mapProfiles) {
		QJsonObject jChild;

        jChild["interface"] = profile.getInterface();
		jChild["ipAddr"] = profile.getIpAddr();
		jChild["netmask"] = profile.getNetmask();
		jChild["gateway"] = profile.getGateway();
		jChild["dns1"] = profile.getDns1();
		jChild["dns2"] = profile.getDns2();
		jChild["dhcp"] = profile.isDhcp();

		QString name = profile.getName();
		jParent[name] = jChild;
	}

	QJsonDocument jDoc(jParent);

	QFile file(filename);
	if (file.open(QIODevice::WriteOnly)) {
		file.write(jDoc.toJson());
		file.close();
		return true;
	}

	return false;
}

bool NetworkProfileMap::readJSON(const QString & filename) {
	QFile file(filename);
	if(file.exists()) {

        try {

            file.open(QIODevice::ReadOnly);
            QByteArray saveData = file.readAll();
            file.close();

            QJsonDocument jDoc(QJsonDocument::fromJson(saveData));

            QJsonObject jParent = jDoc.object();

            QStringList keys = jParent.keys();
            foreach(const QString & key, keys) {
                QJsonObject jChild = jParent[key].toObject();

                const QString & interface = jChild["interface"].toString();
                const QString & ipAddr = jChild["ipAddr"].toString();
                const QString & netmask = jChild["netmask"].toString();
                const QString & gateway = jChild["gateway"].toString();
                const QString & dns1 = jChild["dns1"].toString();
                const QString & dns2 = jChild["dns2"].toString();
                bool dhcp = jChild["dhcp"].toBool();

                NetworkProfile newNetworkProfile(key, interface, ipAddr, netmask, gateway, dns1, dns2, dhcp);
                QString name = newNetworkProfile.getName();
                this->mapProfiles[name] = newNetworkProfile;
            }

        } catch(...) {
            Logger::getInstance().warning("Error reading file " + filename);
            return false;
        }

	}

	return true;
}
