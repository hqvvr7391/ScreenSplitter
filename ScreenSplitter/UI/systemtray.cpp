#include "systemtray.h"

SystemTray::SystemTray(QObject *parent)
	: QSystemTrayIcon(parent)
{
    

	QIcon icon("UI/Src/smart-tv.png");
	this->setIcon(icon);
}

void SystemTray::IconActivated(QSystemTrayIcon::ActivationReason reason)
{
    qDebug("DFS");
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        //iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1) % iconComboBox->count());
        this->hide();
        break;
    case QSystemTrayIcon::MiddleClick:
        //showMessage();
        qDebug("SDFSDF");
        break;
    default:
        ;
    }
}

SystemTray::~SystemTray()
{
}
