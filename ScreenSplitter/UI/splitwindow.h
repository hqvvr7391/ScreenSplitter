#pragma once

#ifndef _SPLITWINDOW_H_
#define _SPLITWINDOW_H_

#include <QWidget>
#include <QFrame>
#include <QPainter>
#include <QScreen>
#include <QThread>
#include <QDebug>
#include <QMouseEvent>


#include "ui_splitwindow.h"
#include "tree.hpp"
#include "splitpreset.h"

class SplitWindow : public QWidget
{
	Q_OBJECT

public:
	SplitWindow(QWidget *parent = Q_NULLPTR, QScreen* screen = Q_NULLPTR);
	~SplitWindow();

	virtual void showEvent(QShowEvent* event);
	virtual void hideEvent(QHideEvent* event);

	virtual void paintEvent(QPaintEvent* event);
	//virtual void mouseMoveEvent(QMouseEvent* event);
	void paintRect(QPainter* painter, SplitTreeNode* node);

	SplitTree* splittree;
	QRect innerrect;
	void setPreset(SplitTree* tree);

signals:
	void settedPreset();

private:
	Ui::splitwindow ui;
	QScreen* p_monitor;
	QTimer* timer;
	

	bool status = false;
};


#endif

