#pragma once

#ifndef _SPLITWINDOW_H_
#define _SPLITWINDOW_H_

#include <QWidget>
#include <QPainter>
#include <QScreen>
#include <QThread>
#include <QDebug>
#include "ui_splitwindow.h"

class SplitWindow : public QWidget
{
	Q_OBJECT

public:
	SplitWindow(QWidget *parent = Q_NULLPTR, QScreen* screen = Q_NULLPTR);
	~SplitWindow();

	virtual void showEvent(QShowEvent* event);
	virtual void paintEvent(QPaintEvent* event);

private:
	Ui::splitwindow ui;
	QScreen* p_monitor;
};

#endif
