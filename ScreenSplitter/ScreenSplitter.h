#pragma once


#include "ui_ScreenSplitter.h"


#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <qt_windows.h>
#include <QCloseEvent>

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
    WindowEventThread* windoweventthread;

    void hideEvent(QHideEvent* event);
    void closeEvent(QCloseEvent* event);

    SystemTray* TrayIcon;   

private slots:
    void IconActivated(QSystemTrayIcon::ActivationReason reason);
};
