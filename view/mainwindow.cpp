#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	this->ui->setupUi(this);

	/*
	this->ui->listWidgetNetworks->addItem("Item 1");
	this->ui->listWidgetNetworks->addItem("Item 2");
	this->ui->listWidgetNetworks->addItem("Item 3");
	*/
}

MainWindow::~MainWindow() {
	std::cout << "Good bye!" << std::endl;
	delete this->ui;
}

void MainWindow::on_checkBoxDhcp_stateChanged(int arg) {
	bool enable = arg != 0;

	this->ui->lineEditAddress->setEnabled(enable);
	this->ui->lineEditNetmask->setEnabled(enable);
	this->ui->lineEditGateway->setEnabled(enable);
	this->ui->lineEditDns1->setEnabled(enable);
	this->ui->lineEditDns2->setEnabled(enable);
}

void MainWindow::on_pushButtonSave_clicked() {
	QMap<QString, QString> cfgMap;

	cfgMap["ip"] = this->ui->lineEditAddress->text();
	cfgMap["netmask"] = this->ui->lineEditNetmask->text();
	cfgMap["gateway"] = this->ui->lineEditGateway->text();
	cfgMap["dns1"] = this->ui->lineEditDns1->text();
	cfgMap["dns2"] = this->ui->lineEditDns2->text();

	QString name = "";
	if(this->ui->listWidgetNetworks->count() > 0) {
		QListWidgetItem * item = this->ui->listWidgetNetworks->selectedItems().first();
		name = item->text();
	}

	DialogSaveAs dialogSaveAs(this, name, cfgMap);
	dialogSaveAs.exec();

	bool statusSave = dialogSaveAs.getExitStatus();
	if(statusSave) {

	}
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
