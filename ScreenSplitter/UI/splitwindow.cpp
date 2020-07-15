#include "splitwindow.h"

SplitWindow::SplitWindow(QWidget *parent, QScreen* screen)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlag(Qt::SubWindow);

	p_monitor = screen;
	setGeometry(screen->geometry());

	QWidget::paintEvent((QPaintEvent*) QEvent::None);
}

SplitWindow::~SplitWindow()
{
}

void SplitWindow::showEvent(QShowEvent* event) {
	//QWidget::paintEvent((QPaintEvent*) event);
	qDebug() << "paint";
}

void SplitWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen;

	pen.setColor("red");
	pen.setWidth(10);
	painter.setPen(pen);
	painter.drawRect(QRect(0,0, p_monitor->geometry().width(), p_monitor->geometry().height()));

}
