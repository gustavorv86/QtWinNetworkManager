#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <iostream>

#include <dialogsaveas.h>
#include <network.h>

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

private:
	Ui::MainWindow *ui;
	void addEvents(void);

private slots:
	void handlePushButtonApply(void);
	void handlePushButtonSave(void);
	void handleCheckBoxDhcp(bool);

};

#endif // MAINWINDOW_H
