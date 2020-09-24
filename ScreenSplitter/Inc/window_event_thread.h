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

   
    static WindowEventThread* getInstance();

    static void CALLBACK WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
        LONG idObject, LONG idChild,
        DWORD dwEventThread, DWORD dwmsEventTime);

    QPoint getMousePoint();
    int getMouseScreen();
    void setWindowPos(HWND hwnd);

    QRect rect;

/*

protected:
    void run() override;
    void stop();
*/
signals:
    void event_WindowMoveStart();
    void event_WindowMoveChanging(int id);
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

    void getRect(QRect rct);
   
};

#endif