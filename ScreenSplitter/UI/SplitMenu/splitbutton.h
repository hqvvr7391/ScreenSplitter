#pragma once

#include <QObject>
#include <QApplication>
#include <QDebug>

#include <QPushButton>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

#include "tree.hpp"
#include "splitpreset.h"



class SplitButton : public QPushButton
{
	Q_OBJECT

public:
	SplitButton(QWidget* parent);
	~SplitButton();

	void setTree(SplitTree* data);
	SplitTree* getTree();

private:
	//virtual bool hitButton(const QPoint& pos) const;
	//virtual void mousePressEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
	
	//void paintRect(QPainter* painter, SplitTreeNode* node);

	SplitTree* tree = nullptr;
	QVector<QRect> rectVector;

};
