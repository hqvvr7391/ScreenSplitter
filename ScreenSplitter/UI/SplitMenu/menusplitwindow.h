#pragma once


#include <iostream>
#include <QWidget>
#include <QDebug>

#include <QtXml>
#include <QFile>
#include <QScreen>

#include <QTimer>
#include <QPainter>
#include <QEvent>
#include <QButtonGroup>
#include <QLabel>

#include "ui_menusplitwindow.h"

#include "monitorbutton.h"
#include "splitbutton.h"

class menuSplitWindow : public QWidget
{
	Q_OBJECT

private:
	Ui::menuSplitWindow ui;

	QVector<MonitorButton*> monitorbutton;
	QButtonGroup* grpmonitorbuttons;

	QVector<SplitButton*> presetbutton;
	QButtonGroup* grppresetbuttons;

	QRect virtualsize;
	float ratio;

	QTimer* timer;

	QRect innerrect;

public:
	menuSplitWindow(QWidget *parent = Q_NULLPTR);
	~menuSplitWindow();

	QList<QScreen*> plist_monitor;

	void createPresetButtons(QVector<SplitTree*> treelist);

	virtual void paintEvent(QPaintEvent* event);

signals:
	void SendCapture(QPixmap capture);
	void sendRect(QRect rct);

private slots:
	void updateMonitorBtn();
	void showSplitWindow(int id);
	void updateSplitWindow(int id);
	void hideSplitWindow();


	void setMBtnPreset(int id);
	void asdf();

};
