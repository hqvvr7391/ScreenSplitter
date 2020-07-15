#pragma once

#ifndef _SYSTEM_TRAY_H_
#define _SYSTEM_TRAY_H_

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

#endif
