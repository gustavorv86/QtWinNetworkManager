#ifndef DIALOGSAVEAS_H
#define DIALOGSAVEAS_H

#include <QDialog>
#include <QMap>

namespace Ui {
class DialogSaveAs;
}

class DialogSaveAs : public QDialog {
	Q_OBJECT

public:
	DialogSaveAs(QWidget * parent, const QString & name, const QMap<QString, QString> & map);
	~DialogSaveAs();

	bool getExitStatus();

private:
	Ui::DialogSaveAs *ui;
	bool exitStatus;

private slots:
	void on_pushButtonOk_clicked();
	void on_pushButtonCancel_clicked();
};

#endif // DIALOGSAVEAS_H
