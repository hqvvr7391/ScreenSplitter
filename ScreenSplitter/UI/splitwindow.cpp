#include "splitwindow.h"

SplitWindow::SplitWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlag(Qt::SubWindow);
}

SplitWindow::~SplitWindow()
{
}
