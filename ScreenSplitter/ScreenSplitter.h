#pragma once


#include "ui_ScreenSplitter.h"


#include <QtWidgets/QMainWindow>
#include <qt_windows.h>

#include "splitwindow.h"
#include "window_event_thread.h"

#include "systemtray.h"

class ScreenSplitter : public QMainWindow
{
    Q_OBJECT

public:
    ScreenSplitter(QWidget *parent = Q_NULLPTR);
    ~ScreenSplitter();

    bool nativeEvent(const QByteArray& eventType, void *msg, long *result);
private:
    Ui::ScreenSplitterClass ui;
    WindowEventThread windoweventthread;

    void hideEvent(QHideEvent* event);

    SystemTray* TrayIcon;
};
