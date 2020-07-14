#pragma once

#include <Windows.h>
#include <iostream>


#include "splitwindow.h"


#include <QThread>
#include <QDebug>


class WindowEventThread : public QThread
{
    Q_OBJECT

public:
    explicit WindowEventThread(QWidget* parent = Q_NULLPTR);
    ~WindowEventThread();

    static void CALLBACK WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
        LONG idObject, LONG idChild,
        DWORD dwEventThread, DWORD dwmsEventTime);

    
protected:
    void run() override;
    void stop();

private:
    QList<QScreen*> plist_monitor;

    MSG msg;
    HWINEVENTHOOK winmovehook;

private slots:
    void setWinEventHook();
    
};

