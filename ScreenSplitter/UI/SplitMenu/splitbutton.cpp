#include "splitbutton.h"

SplitButton::SplitButton(QWidget* parent)
	: QPushButton(parent)
{
	setCheckable(true);	
	
	this->setFixedSize(QSize(160, 90));
	int margin = 5;
	setContentsMargins(margin, margin, margin, margin);
}

SplitButton::~SplitButton()
{}


void SplitButton::setTree(SplitTree* data)
{
	if (data != nullptr) {
		this->tree = data;
	}
}

SplitTree* SplitButton::getTree()
{
	return this->tree;
}


/*void SplitButton::mousePressEvent(QMouseEvent* event)
{
	
	if (event->button() != Qt::LeftButton) {
		event->ignore();
		return;
	}
	
	setChecked(true);
	event->accept();
	repaint(); //flush paint event before invoking potentially expensive operation
	//QApplication::flush();
}*/


void SplitButton::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen;

	
	int penwidth = 5;
	pen.setWidth(penwidth);

	pen.setColor(QColor(200, 0, 0, 200));
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(Qt::gray));
	paintRect(this->geometry(), &painter, tree->getRoot());

	if(isChecked()) pen.setColor("red");
	else pen.setColor(QColor(200,200,200,50));
	
	painter.setPen(pen);
	painter.setBrush(QColor(255, 255, 255, 0));
	
	painter.drawRect(contentsRect());
}





/*
void SplitButton::paintRect(QPainter* painter, SplitTreeNode* node)
{
	static int mg = 3;
	static QMargins margin(mg, mg, mg, mg);

	static float width = (float)this->size().width() / (float)100;
	static float height = (float)this->size().height() / (float)100;

	if (node != nullptr) {
		if (node->bottomleft == nullptr || node->topright == nullptr) {
			QPoint topl(*node->topleft->x * width, *node->topleft->y * height);
			QPoint btmr(*node->bottomright->x * width, *node->bottomright->y * height);
			QRect rect_b(topl, btmr);
			painter->drawRect(rect_b.marginsRemoved(margin));
		}
		else {
			paintRect(painter, node->pleft);
			paintRect(painter, node->pright);
		}
	}

}
/*
void SplitButton::paintRect(QPainter* painter, SplitTreeNode* node)
{
	static int mg = 3;
	static QMargins margin(mg, mg, mg, mg);

	static float width = (float)this->size().width() / (float)100;
	static float height = (float)this->size().height() / (float)100;
	if (node != nullptr) {
		if (node->data.type == FULL) {
			QPoint topl(*node->topleft->x * width, *node->topleft->y * height);
			QPoint btmr(*node->bottomright->x  * width, *node->bottomright->y* height);

			QRect rect_a(topl, btmr);

			painter->drawRect(rect_a.marginsRemoved(margin));
		}
		else {

			if (node->pleft == nullptr) {
				QPoint topl(*node->topleft->x * width, *node->topleft->y * height);
				QPoint topr(*node->topright->x * width, *node->topright->y * height);
				QRect rect_a(topl, topr);
				painter->drawRect(rect_a.msarginsRemoved(margin));
			}
			if (node->pright == nullptr) {
				QPoint btml(*node->bottomleft->x * width, *node->bottomleft->y * height);
				QPoint btmr(*node->bottomright->x * width, *node->bottomright->y * height);
				QRect rect_b(btml, btmr);
				painter->drawRect(rect_b.marginsRemoved(margin));
			}
		}
		paintRect(painter, node->pleft);
		paintRect(painter, node->pright);
	}

	if (node != nullptr) {
		if (node->bottomleft == nullptr || node->topright == nullptr) {
			QPoint topl(*node->topleft->x * width, *node->topleft->y * height);
			QPoint topr(*node->topright->x * width, *node->topright->y * height);
			QRect rect_a(topl, topr);
			painter->drawRect(rect_a.marginsRemoved(margin));
			QPoint btml(*node->bottomleft->x * width, *node->bottomleft->y * height);
			QPoint btmr(*node->bottomright->x * width, *node->bottomright->y * height);
			QRect rect_b(topl, btmr);
			painter->drawRect(rect_b.marginsRemoved(margin));
		}
		else {
			paintRect(painter, node->pleft);
			paintRect(painter, node->pright);
		}
	}
}
*/


