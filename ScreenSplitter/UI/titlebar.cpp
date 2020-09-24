#include "titlebar.h"

TitleBar::TitleBar(QWidget *parent) : QWidget(parent),
    mousePressed(false),
    mousePosition(QPoint())

{
	ui.setupUi(this);
    ui.closeButton ->setStyleSheet("color: white;");
   

    connect(ui.closeButton, &QPushButton::released, parent, &QWidget::close);
    connect(ui.hideButton, &QPushButton::released, parent, &QWidget::hide);

    
}

void TitleBar::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePosition = e->pos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent* e)
{
    if (mousePressed) {
       parentWidget()->move(parentWidget()->mapToParent(e->pos() - mousePosition));
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = false;
        mousePosition = QPoint();
    }
}

void TitleBar::paintEvent(QPaintEvent* e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(e);
}