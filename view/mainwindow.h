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
#include "model/networkprofilemap.h"

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	static const QString DEFAULT_CONFIG_FILE;

	MainWindow(QWidget * parent = nullptr);
	~MainWindow();

private slots:
	void on_checkBoxDhcp_stateChanged(int arg);
	void on_pushButtonSave_clicked();
	void on_pushButtonApply_clicked();
	void on_listWidgetNetworks_itemSelectionChanged();
	void on_pushButtonDelete_clicked();

private:
	Ui::MainWindow * ui;
	NetworkProfileMap mapNetworkProfile;
    Network network;

	void setNetworkProfileValues(NetworkProfile profile);

    QString comboBoxInterfacesGetSelectedText(void);
	void listWidgetNetworksUpdate(void);
	QString listWidgetNetworksGetSelectedText(void);

	void onLoad(void);
	void onExit(void);
};

#endif // MAINWINDOW_H
