#include "view/dialogdhcpsaveas.h"
#include "ui_dialogdhcpsaveas.h"

Dialog::Dialog(QWidget *parent, const QString & name) : QDialog(parent), ui(new Ui::Dialog) {

}


Dialog::~Dialog() {
	delete ui;
}
