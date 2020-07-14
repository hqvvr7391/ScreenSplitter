#pragma once


#include <QSystemTrayIcon>

class SystemTray : public QSystemTrayIcon
{
	Q_OBJECT

public:
	SystemTray(QObject *parent = Q_NULLPTR);
	~SystemTray();

	

private:
	QMenu* TrayMenu;

private slots:
	
};
