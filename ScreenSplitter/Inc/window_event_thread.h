#pragma once

#ifndef _WINDOW_EVENT_THREAD_H_
#define _WINDOW_EVENT_THREAD_H_

#include <Windows.h>
#include <iostream>



#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QThread>
#include <QTimer>


#include "screen.h"


class WindowEventThread : public QObject
{
    Q_OBJECT


private:
    static WindowEventThread* instance;
    QTimer* timer;

    QDesktopWidget* desktop;
    QPoint mouse_position;

    MSG msg;
    HWINEVENTHOOK* winmovehook = nullptr;


public:
    explicit WindowEventThread(QWidget* parent = Q_NULLPTR);
    ~WindowEventThread();

    static WindowEventThread* getInstance();

    static void CALLBACK WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
        LONG idObject, LONG idChild,
        DWORD dwEventThread, DWORD dwmsEventTime);

    QPoint getMousePoint();
    int getMouseScreen();
    void setWindowPos(HWND hwnd, QRect rct);


    void updateScreen();
    QRect rect;

    void updatewindowMoving();

    void updateSplitWindow();
    QRect getWindowSplitRect();
    


signals:
    void event_WindowMoveStart();
    void event_WindowMoveChanging(int id);
    void event_WindowMoveEnd();

    void addScreen(QPlatformScreen* screen);
    void removeScreen(QPlatformScreen* screen);

    void setSplitWindoVisible(bool toggle);


private slots:
    void setWinEventHook();
    void process();

    void screenAdded(QScreen* screen);
    void screenRemoved(QScreen* screen);

   

    

    void windowStartMove(HWND hwnd);
    void windoIsMoving(HWND hwnd);
    void windowEndMove(HWND hwnd);

    void getRect(QRect rct);
   
};

#endif