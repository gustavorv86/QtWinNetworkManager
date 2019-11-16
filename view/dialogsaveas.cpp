#include "dialogsaveas.h"
#include "ui_dialogsaveas.h"

DialogSaveAs::DialogSaveAs(QWidget * parent, const QMap<QString, QString> & map) : QDialog(parent), ui(new Ui::DialogSaveAs) {
	ui->setupUi(this);

	this->exitStatus = false;

	this->ui->lineEditName->setText("default");
	if(map.contains("name")) {
		this->ui->lineEditName->setText(map["name"]);
	}

	if(map.contains("ip")) {
		this->ui->lineEditAddress->setText(map["ip"]);
	}

	if(map.contains("netmask")) {
		this->ui->lineEditNetmask->setText(map["netmask"]);
	}

	if(map.contains("gateway")) {
		this->ui->lineEditGateway->setText(map["gateway"]);
	}

	if(map.contains("dns1")) {
		this->ui->lineEditDns1->setText(map["dns1"]);
	}

	if(map.contains("dns2")) {
		this->ui->lineEditDns2->setText(map["dns2"]);
	}

	if(map.contains("dhcp")) {
		this->ui->checkBoxDhcp->setChecked(true);
	}
}

DialogSaveAs::~DialogSaveAs() {
	delete ui;
}

void DialogSaveAs::on_pushButtonOk_clicked() {
	if(this->ui->lineEditName->text().isEmpty()) {
		QMessageBox::warning(nullptr, "Warning", "The field name cannot be empty");
	} else {
		this->exitStatus = true;
		this->close();
	}
}

void DialogSaveAs::on_pushButtonCancel_clicked() {
	this->exitStatus = false;
	this->close();
}

bool DialogSaveAs::getExitStatus() {
	return this->exitStatus;
}

NetworkProfile DialogSaveAs::getNetworkProfile() {
	QString name = this->ui->lineEditName->text();
	QString ipAddr = this->ui->lineEditAddress->text();
	QString netmask = this->ui->lineEditNetmask->text();
	QString gateway = this->ui->lineEditGateway->text();
	QString dns1 = this->ui->lineEditDns1->text();
	QString dns2 = this->ui->lineEditDns2->text();

	NetworkProfile retNetworkProfile(name, ipAddr, netmask, gateway, dns1, dns2, false);
	return retNetworkProfile;
}

void DialogSaveAs::on_checkBoxDhcp_stateChanged(int arg) {
	bool enable = arg == 0;

	this->ui->lineEditAddress->setEnabled(enable);
	this->ui->lineEditNetmask->setEnabled(enable);
	this->ui->lineEditGateway->setEnabled(enable);
	this->ui->lineEditDns1->setEnabled(enable);
	this->ui->lineEditDns2->setEnabled(enable);
}
