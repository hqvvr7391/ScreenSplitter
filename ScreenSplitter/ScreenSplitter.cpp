#include "ScreenSplitter.h"

ScreenSplitter::ScreenSplitter(QWidget* parent)
	: QWidget(parent)
{
	/// Main window
	ui.setupUi(this);
	


	this->setStyleSheet("color: black;");
	TrayIcon = new SystemTray(this);
	TrayIcon->show();

	connect(TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), 
		this, SLOT(IconActivated(QSystemTrayIcon::ActivationReason)));



	/// window event

	windowevent = WindowEventThread::getInstance();
	QThread* window_event_thread = new QThread();
	windowevent->moveToThread(window_event_thread);

	
	connect(window_event_thread, SIGNAL(started()), 
		windowevent, SLOT(process()));
	connect(window_event_thread, SIGNAL(finished()), 
		windowevent, SLOT(deleteLater()));
	//connect(windowevent, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	//connect(windowevent, SIGNAL(finished()), window_event_thread, SLOT(quit()));
	//connect(windowevent, SIGNAL(finished()), windowevent, SLOT(deleteLater()));



	window_event_thread->start();

	/// Split Preset

	splitpreset = new SplitPreset(this);
	splitpreset->LoadXmlFile();

	menusplitwindow = new menuSplitWindow(this);

	connect(windowevent, SIGNAL(addScreen(QPlatformScreen*)),
		menusplitwindow, SLOT(setMonitorButton(QPlatformScreen*)));
	connect(windowevent, SIGNAL(removeScreen(QPlatformScreen*)),
		menusplitwindow, SLOT(removeMonitorButton(QPlatformScreen*)));

	

	
	menusplitwindow->createPresetButtons(splitpreset->getTreeList());
	ui.horizontalLayout->addWidget(menusplitwindow);
	menusplitwindow->show();

	windowevent->updateScreen();

	connect(menusplitwindow, SIGNAL(sendRect(QRect)), 
		windowevent, SLOT(getRect(QRect)));
	
	/// Split Window
	

	qDebug() << "Main thread : " << QThread::currentThread();
}

ScreenSplitter::~ScreenSplitter()
{
	TrayIcon->hide();
	delete TrayIcon;

	delete menusplitwindow;

	delete splitpreset;

	delete windowevent;

}


//////////////////////
//Main window
//////////////////////

void ScreenSplitter::hideEvent(QHideEvent* event)
{
	if (this->isMinimized())	this->hide();
	QWidget::hideEvent(event);
}

void ScreenSplitter::closeEvent(QCloseEvent* event)
{

	QWidget::closeEvent(event);

}

void ScreenSplitter::IconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
	case QSystemTrayIcon::Trigger:
		this->showNormal();
		this->activateWindow();
		qDebug("click");
		break;
	case QSystemTrayIcon::Context:
		qDebug("context");
		break;
	case QSystemTrayIcon::DoubleClick:


		
		qDebug("dclick");
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

//////////////////////
// Split Window
//////////////////////

void ScreenSplitter::showSplitWindow()
{
	for (int i = 0; i < plist_splitWindow.size(); i++) {
		if (i == windowevent->getMouseScreen()) {
			plist_splitWindow[i]->show();
		}
		else {
			plist_splitWindow[i]->hide();
		}
	}
}


void ScreenSplitter::hideSplitWindow()
{
	for (int i = 0; i < plist_splitWindow.size(); i++) {
		plist_splitWindow[i]->hide();
	}
}


void ScreenSplitter::updateScreen()
{
	showSplitWindow();
}

void ScreenSplitter::resetScreen()
{
	hideSplitWindow();
}

/*
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
}*/