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

	timer = new QTimer(this);
	timer->setInterval(500);
	timer->setSingleShot(true);
	this->setEnabled(false);

	connect(this, SIGNAL(settedPreset()), timer, SLOT(start()));
	connect(this, SIGNAL(settedPreset()), this, SLOT(show()));
	connect(timer, SIGNAL(timeout()), this, SLOT(hide()));
	QWidget::paintEvent((QPaintEvent*) QEvent::None);

	this->setEnabled(false);
}

SplitWindow::~SplitWindow()
{
}

void SplitWindow::setPreset(SplitTree* tree)
{
	splittree = tree;
	this->setEnabled((tree->getRoot() != nullptr) ? true : false);
	this->repaint();
	emit settedPreset();
}

void SplitWindow::showEvent(QShowEvent* event) 
{
	
	//qDebug() << "show" << isVisible();
}

void SplitWindow::hideEvent(QHideEvent* event) 
{
	
	//qDebug() << "hide" << isVisible();
}


void SplitWindow::paintEvent(QPaintEvent* event)
{
	if (isEnabled()) {

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
		painter.drawRect(innerrect.marginsRemoved(margin));
		
	}
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

