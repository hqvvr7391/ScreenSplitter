#pragma once

#include <Windows.h>
#include <iostream>


#include "splitwindow.h"


#include <QThread>


class WindowEventThread : public QThread
{
    Q_OBJECT

public:
    explicit WindowEventThread(QWidget* parent = Q_NULLPTR);
    ~WindowEventThread();


protected:
    void run() override;
    void stop();

private:
    std::vector<SplitWindow*> p_splitwindow;

    bool is_active = FALSE;


    MSG msg;
    HWINEVENTHOOK winmovehook;
    
};

void CALLBACK WindowEventCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
    LONG idObject, LONG idChild,
    DWORD dwEventThread, DWORD dwmsEventTime);