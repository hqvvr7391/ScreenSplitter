#include "systemtray.h"

SystemTray::SystemTray(QObject *parent)
	: QSystemTrayIcon(parent)
{
 
	QIcon icon("UI/Src/smart-tv.png");
	this->setIcon(icon);
}

SystemTray::~SystemTray()
{
}
