#include "window_event_thread.h"

WindowEventThread::WindowEventThread(QWidget* parent)
{
    p_splitwindow.push_back(new SplitWindow());

    winmovehook = SetWinEventHook(
        EVENT_SYSTEM_MOVESIZESTART, EVENT_SYSTEM_MOVESIZEEND,  // Range of events .
        NULL,                                          // Handle to DLL.
        WindowEventCallback,                                // The callback.
        0, 0,              // Process and thread IDs of interest (0 = all)
        WINEVENT_OUTOFCONTEXT); // Flags.
}

WindowEventThread::~WindowEventThread()
{
    UnhookWinEvent(winmovehook);
}

void WindowEventThread::run()
{
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        std::cout << "SDFSDF" << std::endl;
        Sleep(25);        

    }
}


void CALLBACK WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
    LONG idObject, LONG idChild,
    DWORD dwEventThread, DWORD dwmsEventTime)
{
    if (event == EVENT_SYSTEM_MOVESIZESTART)
    {
        qDebug("moving");
    }
    else if (event == EVENT_SYSTEM_MOVESIZEEND)
    {
        qDebug("moved");
    }

}