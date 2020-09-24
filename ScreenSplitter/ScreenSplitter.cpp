#include "ScreenSplitter.h"

ScreenSplitter::ScreenSplitter(QWidget* parent)
	: QWidget(parent)
{
	/// Main window
	ui.setupUi(this);
	//setWindowFlags(Qt::FramelessWindowHint);


	/// Tray Icon
	//menuSplitWindow* menu = new menuSplitWindow(ui.frame);
	//menu->show();
	//menu->setGeometry(menu->parentWidget()->rect());
	
	//ui.frame->setFrameStyle(QFrame::Panel);
	//ui.frame->setLineWidth(5);
	//ui.frame->setStyleSheet("color: blue;");
	
	//ui.titlebar->setStyleSheet("background-color:black;");
	//ui.titlebar->show();

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
		window_event_thread, SLOT(deleteLater()));
	//connect(windowevent, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	//connect(windowevent, SIGNAL(finished()), window_event_thread, SLOT(quit()));
	//connect(windowevent, SIGNAL(finished()), windowevent, SLOT(deleteLater()));
	

	window_event_thread->start();

	//connect(windowevent, SIGNAL(event_WindowMoveChanging()), this, SLOT(updateScreen()));
	//connect(windowevent, SIGNAL(event_WindowMoveEnd()), this, SLOT(resetScreen()));


	/// Split Preset

	splitpreset = new SplitPreset(this);
	splitpreset->LoadXmlFile();

	menusplitwindow = new menuSplitWindow(this);
	menusplitwindow->createPresetButtons(splitpreset->getTreeList());
	ui.horizontalLayout->addWidget(menusplitwindow);
	menusplitwindow->show();

	connect(windowevent, SIGNAL(event_WindowMoveStart()), 
		menusplitwindow, SLOT(showSplitWindow(int)));
	connect(windowevent, SIGNAL(event_WindowMoveChanging(int)), 
		menusplitwindow, SLOT(updateSplitWindow(int)));
	connect(windowevent, SIGNAL(event_WindowMoveEnd()), 
		menusplitwindow, SLOT(hideSplitWindow()));
	connect(menusplitwindow, SIGNAL(sendRect(QRect)), 
		windowevent, SLOT(getRect(QRect)));
	
	/// Split Window
	
	for (int i = 0; i < menusplitwindow->plist_monitor.size(); i++) {
		plist_splitWindow.push_back(new SplitWindow(Q_NULLPTR, menusplitwindow->plist_monitor[i]));
	}

	qDebug() << "Main thread : " << QThread::currentThread();
}

ScreenSplitter::~ScreenSplitter()
{
	TrayIcon->hide();
	delete TrayIcon;

	delete windowevent;

	for (int i = 0; i < plist_splitWindow.size(); i++) {
		delete plist_splitWindow[i];
	}
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