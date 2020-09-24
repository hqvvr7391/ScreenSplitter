#pragma once


#include <QPushButton>
#include <QPainter>
#include <QScreen>
#include <QEvent>
#include <QDebug>

#include "splitwindow.h"
#include "splitbutton.h"

class MonitorButton : public QPushButton
{
	Q_OBJECT
private:
	void paintEvent(QPaintEvent* event);
	SplitWindow* splitwindow;
	QScreen* monitor;
	QPixmap map;

	bool capture = false;

public:
	MonitorButton(QWidget *parent, QScreen* screen);
	~MonitorButton();

	void setMonitor(QScreen* screen);
	void updateCapture();

	void showSplitWindow();
	void updateSplitWindow();
	void hideSplitWindow();

	void setPreset(QAbstractButton* btn);

	QRect getRect();

signals:
	void sendTree(QAbstractButton* pbtn);

private slots:

	void setChecked(bool toggle);
	
	
};
