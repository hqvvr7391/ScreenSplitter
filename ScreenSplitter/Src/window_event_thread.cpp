#include "window_event_thread.h"

WindowEventThread* WindowEventThread::instance = nullptr;

WindowEventThread::WindowEventThread(QWidget* parent)
{
	
	plist_monitor = QGuiApplication::screens();

	desktop = QApplication::desktop();
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &WindowEventThread::update);
	timer->setInterval(30);
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

void WindowEventThread::process()
{
	qDebug() << "registerd windowHook";
	setWinEventHook();
}

void WindowEventThread::update()
{
	emit event_WindowMoveChanging();
}

QPoint WindowEventThread::getMousePoint() 
{
	QPoint globalCursorPos = QCursor::pos();
	int mousePos = desktop->screenNumber(globalCursorPos);
	return globalCursorPos;
}

int WindowEventThread::getMouseScreen()
{
	int mousePos = desktop->screenNumber(getMousePoint());
	return mousePos;
}


void WindowEventThread::windowIsMoving()
{
	timer->start();
	emit event_WindowMoveStart();
}

void WindowEventThread::windowIsMoved()
{
	timer->stop();
	emit event_WindowMoveEnd();
}


void CALLBACK WindowEventThread::WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
	LONG idObject, LONG idChild,
	DWORD dwEventThread, DWORD dwmsEventTime)
{
	qDebug() << "\ncallback Thread : " << QThread::currentThread();

	WindowEventThread* instance = WindowEventThread::getInstance();

	if (event == EVENT_SYSTEM_MOVESIZESTART) {
		instance->windowIsMoving();
	}
	else if (event == EVENT_SYSTEM_MOVESIZEEND) {
		instance->windowIsMoved();
	}
}

void WindowEventThread::setWinEventHook()
{
	winmovehook = (HWINEVENTHOOK* )SetWinEventHook(
		EVENT_SYSTEM_MOVESIZESTART, EVENT_SYSTEM_MOVESIZEEND,  // Range of events .
		NULL,                                          // Handle to DLL.
		WindowEventCallback,                                // The callback.
		0, 0,              // Process and thread IDs of interest (0 = all)
		WINEVENT_OUTOFCONTEXT); // Flags.
}
