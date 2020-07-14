#include "ScreenSplitter.h"

ScreenSplitter::ScreenSplitter(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	TrayIcon = new SystemTray(this);
	TrayIcon->show();

	connect(TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(IconActivated(QSystemTrayIcon::ActivationReason)));


	SplitWindow* a = new SplitWindow();
	a->show();

	windoweventthread = new WindowEventThread(parent);
	//connect(windoweventthread, SIGNAL(started()), windoweventthread, SLOT(setWinEventHook()));

	windoweventthread->start();

	qDebug() << "\nmain thread " << QThread::currentThreadId();

	

}

ScreenSplitter::~ScreenSplitter()
{
	TrayIcon->hide();
	delete TrayIcon;

	delete windoweventthread;
}

void ScreenSplitter::hideEvent(QHideEvent* event)
{
	//if (this->isMinimized())	this->hide();
	QWidget::hideEvent(event);
}

void ScreenSplitter::closeEvent(QCloseEvent* event)
{

	if (this->isMinimized())
	{
		QWidget::closeEvent(event);
	}
	else {
		event->ignore();
		this->hide();
	}
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

void ScreenSplitter::IconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
	case QSystemTrayIcon::Trigger:
		qDebug("click");
		break;
	case QSystemTrayIcon::Context:
		qDebug("context");
		break;
	case QSystemTrayIcon::DoubleClick:

		this->hide();
		break;
	case QSystemTrayIcon::MiddleClick:
		//showMessage();
		qDebug("zxcvz");
		this->show();
		break;
	default:
		;
	}
}