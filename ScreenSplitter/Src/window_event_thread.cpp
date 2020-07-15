#include "window_event_thread.h"

WindowEventThread* WindowEventThread::instance = nullptr;

WindowEventThread::WindowEventThread(QWidget* parent)
{
	
	setWinEventHook();

	plist_monitor = QGuiApplication::screens();
	for (int i = 0; i < plist_monitor.size(); i++) {
		plist_splitWindow.push_back(new SplitWindow(Q_NULLPTR, plist_monitor[i]));
		qDebug() << plist_splitWindow[i] << " Rect : " << plist_splitWindow[i]->geometry();

		//plist_splitWindow[i]->show();
	}
	
	//connect(this, &WindowEventThread::windowIsMoving, this, &WindowEventThread::showSplitWindow);
	//connect(this, &WindowEventThread::windowIsMoved, this, &WindowEventThread::hideSplitWindow);
}

WindowEventThread::~WindowEventThread()
{
	if (winmovehook != nullptr) {
		UnhookWinEvent(*winmovehook);
	}

	for (int i = 0; i < plist_monitor.size(); i++) {
		plist_splitWindow[i]->hide();
	}
}

WindowEventThread* WindowEventThread::getInstance()
{
	if (!instance) instance = new WindowEventThread();
	return instance;
}

/*
void WindowEventThread::run()
{
	qDebug() << "WindowEventThread : " << QThread::currentThread();
	if (winmovehook == nullptr) {  }
	
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		sleep(10);
	}
}*/

void WindowEventThread::showSplitWindow()
{
	qDebug() << "\nshow Thread : " << QThread::currentThread();
	for (int i = 0; i < plist_monitor.size(); i++) {
		plist_splitWindow[i]->show();
	}
}

void WindowEventThread::hideSplitWindow()
{
	for (int i = 0; i < plist_monitor.size(); i++) {
		plist_splitWindow[i]->hide();
	}
}

void CALLBACK WindowEventThread::WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
	LONG idObject, LONG idChild,
	DWORD dwEventThread, DWORD dwmsEventTime)
{
	qDebug() << "\ncallback Thread : " << QThread::currentThread();

	WindowEventThread* instance = WindowEventThread::getInstance();

	if (event == EVENT_SYSTEM_MOVESIZESTART) {
		instance->showSplitWindow();
	}
	else if (event == EVENT_SYSTEM_MOVESIZEEND) {
		instance->hideSplitWindow();

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
