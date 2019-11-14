#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <iostream>

#include "dialogsaveas.h"
#include "utils/network.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_checkBoxDhcp_stateChanged(int arg1);

	void on_pushButtonSave_clicked();

	void on_pushButtonApply_clicked();

private:
	Ui::MainWindow *ui;
	void addEvents(void);

	void handlePushButtonApply(void);
	void handlePushButtonSave(void);
	void handleCheckBoxDhcp(bool);

};

#endif // MAINWINDOW_H
