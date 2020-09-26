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
#include "splitbutton.h"

class SplitWindow : public QWidget
{
	Q_OBJECT

public:
	SplitWindow(QWidget *parent = Q_NULLPTR, QScreen* screen = Q_NULLPTR);
	~SplitWindow();

	virtual void paintEvent(QPaintEvent* event);



	void paintRect(QPainter* painter, SplitTreeNode* node);

	SplitTree* splittree;
	QRect innerrect;
	

	void asdf();

	void setVisibleState(bool toggle);
	QRect getRect();

signals:
	void settedPreset();
	void setVisibility(bool toggle);

private:
	Ui::splitwindow ui;
	QScreen* p_monitor;
	QTimer* timer;
	
	bool isMoving = false;

	bool status = false;

private slots:
	void setPreset(SplitButton* pbtn);
};



#endif

