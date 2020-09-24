#pragma once

#ifndef _SCREEN_SPLITTER_H_
#define _SCREEN_SPLITTER_H_

#include "ui_ScreenSplitter.h"


#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <qt_windows.h>
#include <QCloseEvent>
#include <QGraphicsScene>
#include <QGraphicsAnchorLayout>

#include "splitpreset.h"
#include "splitwindow.h"
#include "menusplitwindow.h"
#include "window_event_thread.h"
#include "titlebar.h"

#include "systemtray.h"

class ScreenSplitter : public QWidget
{
    Q_OBJECT

public:
    ScreenSplitter(QWidget *parent = Q_NULLPTR);
    ~ScreenSplitter();

    QList<SplitWindow*> plist_splitWindow;
    SplitPreset* splitpreset;
    
    void showSplitWindow();
    void hideSplitWindow();



    //bool nativeEvent(const QByteArray& eventType, void *msg, long *result);

signals:
    void signal_windowIsMoving();
    void signal_windowIsMoved();

private:
    Ui::Form ui;
    WindowEventThread* windowevent;
    menuSplitWindow* menusplitwindow;

    void hideEvent(QHideEvent* event);
    void closeEvent(QCloseEvent* event);

    SystemTray* TrayIcon;

private slots:
    void IconActivated(QSystemTrayIcon::ActivationReason reason);

    void updateScreen();
    void resetScreen();
};


#endif
