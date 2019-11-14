#include "dialogsaveas.h"
#include "ui_dialogsaveas.h"

DialogSaveAs::DialogSaveAs(QWidget *parent, const QString & name, const QMap<QString, QString> & map) : QDialog(parent), ui(new Ui::DialogSaveAs) {
	ui->setupUi(this);

	this->ui->lineEditName->setText("default");
	if(!name.isEmpty()) {
		this->ui->lineEditName->setText(name);
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
}

void DialogSaveAs::on_pushButtonOk_clicked() {
	this->exitStatus = true;
	this->close();
}

void DialogSaveAs::on_pushButtonCancel_clicked() {
	this->exitStatus = false;
	this->close();
}

bool DialogSaveAs::getExitStatus() {
	return this->exitStatus;
}

DialogSaveAs::~DialogSaveAs() {
	delete ui;
}
