#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
	Q_OBJECT

public:
	Dialog(QWidget *parent, const QString & name);
	~Dialog();

private:
	Ui::Dialog *ui;
};

#endif // DIALOG_H
