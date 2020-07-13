#include "ScreenSplitter.h"

ScreenSplitter::ScreenSplitter(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	SplitWindow* a = new SplitWindow();
	a->show();


	TrayIcon = new SystemTray(this);
	TrayIcon->show();
	
	connect(this, SIGNAL(QSystemTrayIcon::activated), TrayIcon, SLOT(IconActivated));
	//windoweventthread.start();
}

ScreenSplitter::~ScreenSplitter()
{
	TrayIcon->hide();
	delete TrayIcon;
}

void ScreenSplitter::hideEvent(QHideEvent* event)
{
	if (this->isMinimized())	this->hide();
	QWidget::hideEvent(event);
}



bool ScreenSplitter::nativeEvent(const QByteArray& eventType, void* msg, long* result)	// monitor detection when changed
{
	MSG* message = static_cast<MSG*>(msg);

	if (message == nullptr)
		return false;

	switch (message->message)
	{
	case  WM_DEVICECHANGE:
	{

		qDebug("SFSDF");

	}

	break;
	}



	return false;

}