#ifndef DIALOGSAVEAS_H
#define DIALOGSAVEAS_H

#include <QDebug>
#include <QDialog>
#include <QMap>
#include <QMessageBox>

#include "model/networkprofile.h"

namespace Ui {
class DialogSaveAs;
}

class DialogSaveAs : public QDialog {
	Q_OBJECT

public:
    DialogSaveAs(QWidget * parent, const QStringList & listInterfaces, const QString & selectedInterface, const QMap<QString, QString> & map);
	~DialogSaveAs();

	bool getExitStatus();
	NetworkProfile getNetworkProfile();

private:
	Ui::DialogSaveAs *ui;
	bool exitStatus;

private slots:
	void on_pushButtonOk_clicked();
	void on_pushButtonCancel_clicked();
	void on_checkBoxDhcp_stateChanged(int arg1);
};

#endif // DIALOGSAVEAS_H
