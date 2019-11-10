#include "dialogsaveas.h"
#include "ui_dialogsaveas.h"

DialogSaveAs::DialogSaveAs(QWidget *parent) : QDialog(parent), ui(new Ui::DialogSaveAs) {
	ui->setupUi(this);
}

DialogSaveAs::DialogSaveAs(QWidget *parent, const QString & name, const QMap<QString, QString> & map) : QDialog(parent), ui(new Ui::DialogSaveAs) {
	ui->setupUi(this);

	this->ui->lineEditName->setText(name);

	if(map.contains("ip")) {
		this->ui->lineEditAddress->setText(map["ip"]);
	}

	if(map.contains("netmask")) {
		this->ui->lineEditAddress->setText(map["netmask"]);
	}

	if(map.contains("gateway")) {
		this->ui->lineEditAddress->setText(map["gateway"]);
	}

	if(map.contains("dns1")) {
		this->ui->lineEditAddress->setText(map["dns1"]);
	}

	if(map.contains("dns2")) {
		this->ui->lineEditAddress->setText(map["dns2"]);
	}
}

DialogSaveAs::~DialogSaveAs() {
	delete ui;
}
