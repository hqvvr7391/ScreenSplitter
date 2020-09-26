#include "window_event_thread.h"

WindowEventThread* WindowEventThread::instance = nullptr;

WindowEventThread::WindowEventThread(QWidget* parent)
{
	
	desktop = QApplication::desktop();


	connect(qGuiApp, SIGNAL(screenAdded(QScreen*)), 
		this, SLOT(screenAdded(QScreen*)));
	connect(qGuiApp, SIGNAL(screenRemoved(QScreen*)),
		this, SLOT(screenRemoved(QScreen*)));



	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &WindowEventThread::windoIsMoving);
	timer->setInterval(30);

	qDebug() << "wet " << thread();
}


WindowEventThread::~WindowEventThread()
{
	if (winmovehook != nullptr) {
		UnhookWinEvent((HWINEVENTHOOK) winmovehook);
	}
}

WindowEventThread* WindowEventThread::getInstance()
{
	if (!instance) instance = new WindowEventThread();
	return instance;
}


void WindowEventThread::updateScreen() 
{

	QList<QScreen*> plist_monitor = QGuiApplication::screens();
	for (int i = 0; i < plist_monitor.size(); i++)
		emit screenAdded(plist_monitor.at(i));
}







void WindowEventThread::screenAdded(QScreen* screen)
{
	((QPlatformScreen*)screen)->setScreen(screen);
	((QPlatformScreen*)screen)->getSplitWindow()->asdf();

	/*connect(,
		((QPlatformScreen*)screen)->getSplitWindow(), SLOT(show()));
	connect(,
		((QPlatformScreen*)screen)->getSplitWindow(), SLOT(hide()));*/
		
	emit addScreen((QPlatformScreen* )screen);
}

void WindowEventThread::screenRemoved(QScreen* screen)
{
	((QPlatformScreen*)screen)->~QPlatformScreen();
	emit removeScreen((QPlatformScreen*) screen);
}








void WindowEventThread::windowStartMove(HWND hwnd)
{
	Q_UNUSED(hwnd);
	timer->start();
	//((Screen*)qGuiApp->screenAt(QCursor::pos()));

	emit event_WindowMoveStart();
}

void WindowEventThread::windoIsMoving(HWND hwnd)
{
	Q_UNUSED(hwnd);
	int id = getMouseScreen();
	updatewindowMoving();
	emit event_WindowMoveChanging(id);
}

void WindowEventThread::updatewindowMoving()
{
	updateSplitWindow();
	//updateMagnet();
}


void WindowEventThread::updateSplitWindow()
{
	QList<QScreen*> screens = qGuiApp->screens();
	QPlatformScreen* screenat = ((QPlatformScreen*)qGuiApp->screenAt(QCursor::pos()));


	for (int i = 0; i < screens.size(); i++) {
		QPlatformScreen* screen = (QPlatformScreen*)screens.at(i);
		bool toggle = false;
		if (screenat == screen)
		{
			toggle = true;
			screen->getSplitWindow()->update();
		}
				
		else	toggle = false;
		screen->getSplitWindow()->setVisibleState(toggle);
	}
	
	/*else {
		for (int i = 0; i < screens.size(); i++) {
			QPlatformScreen* screen = (QPlatformScreen*)screens.at(i);
			bool toggle = false;

			if (screen->getSplitWindow()->isVisible()) {
				screen->getSplitWindow()->setVisibleState(toggle);
				screen->getSplitWindow()->getRect();
			}
			
		}
	}*/
}

QRect WindowEventThread::getWindowSplitRect()
{
	QList<QScreen*> screens = qGuiApp->screens();
	QPlatformScreen* screenat = ((QPlatformScreen*)qGuiApp->screenAt(QCursor::pos()));

	QRect rct;
	for (int i = 0; i < screens.size(); i++) {
		QPlatformScreen* screen = (QPlatformScreen*)screens.at(i);
		bool toggle = false;

		if (screen->getSplitWindow()->isVisible()) {
			screen->getSplitWindow()->setVisibleState(toggle);
			rct = screen->getSplitWindow()->getRect();
		}
	}
	return rct;
}


void WindowEventThread::windowEndMove(HWND hwnd)
{
	Q_UNUSED(hwnd);
	timer->stop();
	emit event_WindowMoveEnd();
}

void WindowEventThread::setWindowPos(HWND hwnd, QRect rct)
{
	if (rct.isValid())
	{
		SetWindowPos(hwnd, HWND_TOP, rct.x(), rct.y(), rct.width(), rct.height(), SWP_SHOWWINDOW);
	}
}


void WindowEventThread::getRect(QRect rct)
{
	rect = rct;	
}







void CALLBACK WindowEventThread::WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
	LONG idObject, LONG idChild,
	DWORD dwEventThread, DWORD dwmsEventTime)
{
	qDebug() << "\ncallback Thread : " << QThread::currentThread();

	WindowEventThread* instance = WindowEventThread::getInstance();

	if (event == EVENT_SYSTEM_MOVESIZESTART) {
		instance->windowStartMove();
	}
	else if (event == EVENT_SYSTEM_MOVESIZEEND) {
		instance->windowEndMove();
		//cout << "window\t" << hwnd << endl;
		//SetWindowPos(hwnd, HWND_TOP, x, y, cx, cy, SWP_SHOWWINDOW);
		QRect rct = instance->getWindowSplitRect();
		instance->setWindowPos(hwnd, rct);
	}
}

void WindowEventThread::setWinEventHook()
{
	//*
	winmovehook = (HWINEVENTHOOK* )SetWinEventHook(
		EVENT_SYSTEM_MOVESIZESTART, EVENT_SYSTEM_MOVESIZEEND,  // Range of events .
		NULL,                                          // Handle to DLL.
		WindowEventCallback,                                // The callback.
		0, 0,              // Process and thread IDs of interest (0 = all)
		WINEVENT_OUTOFCONTEXT); // Flags.
	//*/
	//qDebug() << "SDFSD";
}

void WindowEventThread::process()
{
	setWinEventHook();
}

QPoint WindowEventThread::getMousePoint()
{
	return QCursor::pos();
}

int WindowEventThread::getMouseScreen()
{
	int mousePos = desktop->screenNumber(getMousePoint());
	return mousePos;
}