#pragma once

#include <QObject>
#include <QPointer>
#include <QScreen>

#include "splitwindow.h"
#include "monitorbutton.h"






class QPlatformScreen : public QObject
{
	Q_OBJECT

private:
	QScreen* instance;
	SplitWindow* window;
	MonitorButton* button;


public:
	QPlatformScreen(QObject* parent = Q_NULLPTR);
	~QPlatformScreen();

	void setScreen(QScreen* ins);
	QScreen* getScreen();

	SplitWindow* getSplitWindow();
	MonitorButton* getMonitorButton();


private slots:



};
