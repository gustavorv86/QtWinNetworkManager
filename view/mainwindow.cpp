#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString MainWindow::DEFAULT_CONFIG_FILE("config.json");

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	this->ui->setupUi(this);
	this->onLoad();
}

MainWindow::~MainWindow() {
	this->onExit();
	std::cout << "Good bye!" << std::endl;
	delete this->ui;
}

void MainWindow::onLoad() {
	networkMap.readJSON(DEFAULT_CONFIG_FILE);
	foreach (const QString & profileName, networkMap.getKeys()) {
		this->ui->listWidgetNetworks->addItem(profileName);
	}
}

void MainWindow::onExit() {
	networkMap.writeJSON(DEFAULT_CONFIG_FILE);
}

void MainWindow::on_checkBoxDhcp_stateChanged(int arg) {
	bool enable = arg == 0;

	this->ui->lineEditAddress->setEnabled(enable);
	this->ui->lineEditNetmask->setEnabled(enable);
	this->ui->lineEditGateway->setEnabled(enable);
	this->ui->lineEditDns1->setEnabled(enable);
	this->ui->lineEditDns2->setEnabled(enable);
}

void MainWindow::on_pushButtonSave_clicked() {
	QMap<QString, QString> cfgMap;

	QString name = this->getSelectedTextList();
	if(name.isEmpty()) {
		name = "default";
	}

	cfgMap["name"] = name;
	cfgMap["ip"] = this->ui->lineEditAddress->text();
	cfgMap["netmask"] = this->ui->lineEditNetmask->text();
	cfgMap["gateway"] = this->ui->lineEditGateway->text();
	cfgMap["dns1"] = this->ui->lineEditDns1->text();
	cfgMap["dns2"] = this->ui->lineEditDns2->text();
	if(this->ui->checkBoxDhcp->isChecked()) {
		cfgMap["dhcp"] = "true";
	}

	DialogSaveAs dialogSaveAs(this, cfgMap);
	dialogSaveAs.exec();

	if(dialogSaveAs.getExitStatus()) {
		NetworkProfile profile = dialogSaveAs.getNetworkProfile();
		this->networkMap.put(profile);
		this->reloadList();
	}
}

void MainWindow::reloadList(void) {
	this->ui->listWidgetNetworks->clear();
	foreach(const QString & profileName, this->networkMap.getKeys()) {
		this->ui->listWidgetNetworks->addItem(profileName);
	}
}

QString MainWindow::getSelectedTextList(void) {
	QList<QListWidgetItem *> allSelection = this->ui->listWidgetNetworks->selectedItems();
	if(allSelection.count() > 0) {
		QListWidgetItem * item = allSelection.last();
		return item->text();
	}
	return "";
}

void MainWindow::on_pushButtonApply_clicked() {
	Network net("Ethernet");

	if(this->ui->checkBoxDhcp->isChecked()) {
		net.dhcp();
	} else {
		QString ipAddr = this->ui->lineEditAddress->text();
		QString netmask = this->ui->lineEditNetmask->text();
		QString gateway = this->ui->lineEditGateway->text();
		QString dns1 = this->ui->lineEditDns1->text();
		QString dns2 = this->ui->lineEditDns2->text();

		net.staticConfig(ipAddr, netmask, gateway, dns1, dns2);
	}

	QMessageBox messageBox;
	messageBox.setText("Configuration done");
	messageBox.exec();
}

void MainWindow::on_listWidgetNetworks_itemSelectionChanged() {
	QList<QListWidgetItem *> allSelection = this->ui->listWidgetNetworks->selectedItems();
	if(allSelection.count() > 0) {

	}
}

void MainWindow::on_pushButtonDelete_clicked() {

}
