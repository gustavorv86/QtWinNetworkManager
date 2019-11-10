#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	std::cout << "Constructor" << std::endl;
	this->ui->setupUi(this);
	this->addEvents();

	/*
	this->ui->listWidgetNetworks->addItem("Item 1");
	this->ui->listWidgetNetworks->addItem("Item 2");
	this->ui->listWidgetNetworks->addItem("Item 3");
	*/
}

MainWindow::~MainWindow() {
	std::cout << "Destructor" << std::endl;
	delete this->ui;
}

void MainWindow::addEvents() {
	this->connect(this->ui->pushButtonApply, SIGNAL(released()), this, SLOT(handlePushButtonApply()));
	this->connect(this->ui->pushButtonSave, SIGNAL(released()),this, SLOT(handlePushButtonSave()));
	this->connect(this->ui->checkBoxDhcp, SIGNAL(clicked(bool)), this, SLOT(handleCheckBoxDhcp(bool)));
}

void MainWindow::handlePushButtonApply(void) {
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
	std::cout << "End handlePushButtonApply" << std::endl;
}

void MainWindow::handlePushButtonSave(void) {
	QMap<QString, QString> cfgMap;

	cfgMap["ip"] = this->ui->lineEditAddress->text();
	cfgMap["netmask"] = this->ui->lineEditNetmask->text();
	cfgMap["gateway"] = this->ui->lineEditGateway->text();
	cfgMap["dns1"] = this->ui->lineEditDns1->text();
	cfgMap["dns2"] = this->ui->lineEditDns2->text();

	QListWidgetItem * item = this->ui->listWidgetNetworks->selectedItems().first();

	DialogSaveAs dialogSaveAs(this, item->text(), cfgMap);
	dialogSaveAs.exec();
}

void MainWindow::handleCheckBoxDhcp(bool status) {
	bool enable = !status;
	this->ui->lineEditAddress->setEnabled(enable);
	this->ui->lineEditNetmask->setEnabled(enable);
	this->ui->lineEditGateway->setEnabled(enable);
	this->ui->lineEditDns1->setEnabled(enable);
	this->ui->lineEditDns2->setEnabled(enable);
}
