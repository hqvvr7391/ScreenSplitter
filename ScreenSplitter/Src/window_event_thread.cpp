#include "window_event_thread.h"

WindowEventThread::WindowEventThread(QWidget* parent)
{
    plist_monitor = QGuiApplication::screens();

}

WindowEventThread::~WindowEventThread()
{
    if (winmovehook != nullptr) {
        UnhookWinEvent(winmovehook);
    }
}

void WindowEventThread::run()
{
    if (winmovehook == nullptr)
        setWinEventHook();
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        
        Sleep(25);
    }
}


void CALLBACK WindowEventThread::WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
    LONG idObject, LONG idChild,
    DWORD dwEventThread, DWORD dwmsEventTime)
{   
    qDebug() << "callback thread " << QThread::currentThreadId();

    if (event == EVENT_SYSTEM_MOVESIZESTART)
    {
        qDebug("moving");
    }
    else if (event == EVENT_SYSTEM_MOVESIZEEND)
    {
        qDebug("moved");
    }

}


void WindowEventThread::setWinEventHook()
{
    winmovehook = SetWinEventHook(
        EVENT_SYSTEM_MOVESIZESTART, EVENT_SYSTEM_MOVESIZEEND,  // Range of events .
        NULL,                                          // Handle to DLL.
        &WindowEventCallback,                                // The callback.
        0, 0,              // Process and thread IDs of interest (0 = all)
        WINEVENT_OUTOFCONTEXT); // Flags.
}