#include "monitorbutton.h"

MonitorButton::MonitorButton(QWidget*parent, QScreen* screen)
	: QPushButton(parent)
{
	setCheckable(true);
	int margin = 5;
	setContentsMargins(margin, margin, margin, margin);
	this->monitor = screen;
	//splitwindow = new SplitWindow(nullptr, screen);
}

MonitorButton::~MonitorButton()
{
}

void MonitorButton::setMonitor(QScreen* screen)
{
	monitor = screen;
}

QScreen* MonitorButton::getMonitor() {
	return monitor;
}
void MonitorButton::updateCapture()
{
	capture = true;
	QWidget::update();
}

void MonitorButton::showSplitWindow()
{
	splitwindow->show();
}

void MonitorButton::updateSplitWindow()
{
	splitwindow->update();
}

void MonitorButton::hideSplitWindow()
{
	splitwindow->hide();
}

QRect MonitorButton::getRect() {
	return splitwindow->innerrect.translated(splitwindow->pos());
}

void MonitorButton::setChecked(bool toggle)
{
	if (toggle) {
		//emit sendTree(this);
	}
}

void MonitorButton::setPreset(QAbstractButton* btn)
{
	pbtn = (SplitButton*)btn;
	emit sendTree(pbtn);
}

SplitButton* MonitorButton::getPresetBtn()
{	return pbtn;	}

void MonitorButton::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen;

	if (capture)
	{
		map = monitor->grabWindow(0);
		capture = false;
	}

	if(true)
	{
		pen.setColor("red");

	}
	else
	{
		pen.setColor("black");
	}
	pen.setWidth(5);
	painter.setPen(pen);
	painter.drawPixmap(this->contentsRect(), map);


	if (isChecked()) pen.setColor("red");
	else pen.setColor(QColor(200, 200, 200, 50));

	painter.setPen(pen);
	painter.setBrush(QColor(255, 255, 255, 0));

	painter.drawRect(contentsRect());
}