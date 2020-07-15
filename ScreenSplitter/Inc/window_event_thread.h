#pragma once

#ifndef _WINDOW_EVENT_THREAD_H_
#define _WINDOW_EVENT_THREAD_H_



#include <Windows.h>
#include <iostream>


#include "splitwindow.h"

#include <QDebug>

#include <QApplication>
#include <QDesktopWidget>
#include <QThread>
#include <QTimer>





class WindowEventThread : public QObject
{
    Q_OBJECT

public:
    explicit WindowEventThread(QWidget* parent = Q_NULLPTR);
    ~WindowEventThread();

    QList<QScreen*> plist_monitor;

    static WindowEventThread* getInstance();

    static void CALLBACK WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
        LONG idObject, LONG idChild,
        DWORD dwEventThread, DWORD dwmsEventTime);

    QPoint getMousePoint();
    int getMouseScreen();
/*

protected:
    void run() override;
    void stop();
*/
signals:
    void event_WindowMoveStart();
    void event_WindowMoveChanging();
    void event_WindowMoveEnd();

private:
    static WindowEventThread* instance;
    QTimer* timer;

    QDesktopWidget* desktop;
    QPoint mouse_position;

    MSG msg;
    HWINEVENTHOOK* winmovehook = nullptr;

private slots:
    void setWinEventHook();

    void process();

    void update();

    void windowIsMoving();
    void windowIsMoved();
   
};



#endif // !WINDOW_EVENT_THREAD_H