#pragma once

#ifndef _WINDOW_EVENT_THREAD_H_
#define _WINDOW_EVENT_THREAD_H_



#include <Windows.h>
#include <iostream>


#include "splitwindow.h"


#include <QThread>
#include <QDebug>




class WindowEventThread : public QObject
{
    Q_OBJECT

public:
    explicit WindowEventThread(QWidget* parent = Q_NULLPTR);
    ~WindowEventThread();

    static WindowEventThread* getInstance();

    static void CALLBACK WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
        LONG idObject, LONG idChild,
        DWORD dwEventThread, DWORD dwmsEventTime);

    void showSplitWindow();
    void hideSplitWindow();
/*

protected:
    void run() override;
    void stop();
*/


signals:
    void windowIsMoving();
    void windowIsMoved();

private:
    static WindowEventThread* instance;

    QList<QScreen*> plist_monitor;
    QList<SplitWindow*> plist_splitWindow;

    MSG msg;
    HWINEVENTHOOK* winmovehook = nullptr;

private slots:
    void setWinEventHook();
    
   
};



#endif // !WINDOW_EVENT_THREAD_H