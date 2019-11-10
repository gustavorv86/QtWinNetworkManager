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
	explicit DialogSaveAs(QWidget *parent = nullptr);
	DialogSaveAs(QWidget * parent, const QString & name, const QMap<QString, QString> & map);
	~DialogSaveAs();

private:
	Ui::DialogSaveAs *ui;
};

#endif // DIALOGSAVEAS_H
