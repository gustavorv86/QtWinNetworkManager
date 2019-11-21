#include "networkprofile.h"

NetworkProfile::NetworkProfile() {
	this->name = "";
	this->ipAddr = "";
	this->netmask = "";
	this->gateway = "";
	this->dns1 = "";
	this->dns2 = "";
	this->dhcp = true;
}

NetworkProfile::NetworkProfile(const QString & name, const QString & interface, const QString & ipAddr, const QString & netmask, const QString & gateway, const QString & dns1, const QString & dns2, bool dhcp) {
	this->name = name;
    this->interface = interface;
	this->ipAddr = ipAddr;
	this->netmask = netmask;
	this->gateway = gateway;
	this->dns1 = dns1;
	this->dns2 = dns2;
	this->dhcp = dhcp;
}

NetworkProfile::NetworkProfile(const QMap<QString, QString> & map) {
	this->name = map["name"];
    this->interface = map["interface"];
    this->ipAddr = map["ipAddr"];
	this->netmask = map["netmask"];
	this->gateway = map["gateway"];
	this->dns1 = map["dns1"];
	this->dns2 = map["dns2"];
	this->dhcp = map["dhcp"] == "true" ? true : false;
}

const QString & NetworkProfile::getName(void) const {
	return this->name;
}

const QString & NetworkProfile::getInterface(void) const {
    return this->interface;
}

const QString & NetworkProfile::getIpAddr(void) const {
	return this->ipAddr;
}

const QString & NetworkProfile::getNetmask(void) const {
	return this->netmask;
}

const QString & NetworkProfile::getGateway(void) const {
	return this->gateway;
}

const QString & NetworkProfile::getDns1(void) const {
	return this->dns1;
}

const QString & NetworkProfile::getDns2(void) const {
	return this->dns2;
}

bool NetworkProfile::isDhcp(void) const {
	return this->dhcp;
}

void NetworkProfile::setName(const QString & name) {
	this->name = name;
}

void NetworkProfile::setInterface(const QString & interface) {
    this->interface = interface;
}

void NetworkProfile::setIpAddr(const QString & ipAddr) {
	this->ipAddr = ipAddr;
	this->dhcp = false;
}

void NetworkProfile::setNetmask(const QString & netmask) {
	this->netmask = netmask;
	this->dhcp = false;
}

void NetworkProfile::setGateway(const QString & gateway) {
	this->gateway = gateway;
	this->dhcp = false;
}

void NetworkProfile::setDns1(const QString & dns1) {
	this->dns1 = dns1;
	this->dhcp = false;
}

void NetworkProfile::setDns2(const QString & dns2) {
	this->dns2 = dns2;
	this->dhcp = false;
}

void NetworkProfile::setDhcp(bool dhcp) {
	this->dhcp = dhcp;
}
