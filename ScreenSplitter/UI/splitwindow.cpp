#include "splitwindow.h"

SplitWindow::SplitWindow(QWidget *parent, QScreen* screen)
	: QWidget(parent)
{
	ui.setupUi(this);

	this->setEnabled(false);

	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlag(Qt::SubWindow);

	p_monitor = screen;
	setGeometry(screen->geometry());

	timer = new QTimer(this);
	timer->setInterval(750);
	timer->setSingleShot(true);


	
	connect(this, SIGNAL(settedPreset()), 
		timer, SLOT(start()));
	connect(this, SIGNAL(settedPreset()),
		this, SLOT(show()));
	connect(timer, SIGNAL(timeout()), 
		this, SLOT(hide()));

	connect(this, SIGNAL(setVisibility(bool)),
		this, SLOT(setVisible(bool)));

	QWidget::paintEvent((QPaintEvent*) QEvent::None);
}

SplitWindow::~SplitWindow()
{
}

void SplitWindow::setPreset(SplitButton* pbtn)
{
	splittree = pbtn->getTree();
	this->setEnabled((splittree != nullptr) ? true : false);
	this->update();
	emit settedPreset();
}

void SplitWindow::asdf() {
	qDebug() << "asdfasdf";
}


void SplitWindow::setVisibleState(bool toggle)
{
	if (toggle) {
		if (!isVisible()) {
			isMoving = true;
			emit setVisibility(true);
		}
	}
	else {
		if (isVisible()) {
			isMoving = false;
			emit setVisibility(false);
		}
	}
}

QRect SplitWindow::getRect()
{
	return innerrect;
}

void SplitWindow::paintEvent(QPaintEvent* event)
{

	QPainter painter(this);
	QPen pen;

	pen.setColor("red");
	pen.setWidth(8);
	painter.setPen(pen);
	//painter.drawRect(QRect(0, 0, p_monitor->geometry().width(), p_monitor->geometry().height()));

	this->paintRect(&painter, this->splittree->getRoot());

	pen.setColor("green");
	painter.setPen(pen);
	static int mg = 3;
	static QMargins margin(mg, mg, mg, mg);
	if(isMoving)	painter.drawRect(innerrect.marginsRemoved(margin));

}

void SplitWindow::paintRect(QPainter* painter, SplitTreeNode* node)
{
	static int mg = 3;
	static QMargins margin(mg, mg, mg, mg);

	float width = (float)this->geometry().width() / (float)100;
	float height = (float)this->geometry().height() / (float)100;

	if (node != nullptr) {
		if (node->bottomleft == nullptr || node->topright == nullptr) {
			QPoint pos = QCursor::pos(p_monitor) - this->pos();
			QPoint topl(*node->topleft->x * width, *node->topleft->y * height);
			QPoint btmr(*node->bottomright->x * width, *node->bottomright->y * height);
			QRect splitrect(topl, btmr);

			if (splitrect.contains(pos)) innerrect = splitrect;
			
			painter->drawRect(splitrect.marginsRemoved(margin));

		}
		else {
			paintRect(painter, node->pleft);
			paintRect(painter, node->pright);
		}
	}
}

