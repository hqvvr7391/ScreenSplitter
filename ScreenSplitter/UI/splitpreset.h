#pragma once

#include <QObject>
#include <QtXml>
#include <QFile>

#include <QButtonGroup>
#include <QLabel>
#include <QPainter>

#include <iostream>

#include "tree.hpp"

class SplitPreset : public QObject
{
	Q_OBJECT

public:
	SplitPreset(QObject *parent);
	~SplitPreset();

	
	void LoadXmlFile();
	void getValue(SplitTree* tree, SplitTreeNode* node, QXmlStreamReader& xml, int side);

	QVector<SplitTree*> getTreeList();
	

private:
	QFile *xmlfile;
	QVector<SplitTree*> TreeList;

};


void paintRect(QRect rect, QPainter* painter, SplitTreeNode* node);