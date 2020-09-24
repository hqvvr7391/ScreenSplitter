#pragma once

#include <QtWidgets/QWidget>
#include "ui_qtTest.h"

#include <QObject>
#include <QtXml>
#include <QFile>

#include <QButtonGroup>
#include <QLabel>

#include <iostream>

#include "tree.hpp"
#include "splitbutton.h"

class qtTest : public QWidget
{
    Q_OBJECT

public:
    qtTest(QWidget *parent = Q_NULLPTR);
    ~qtTest();

    QVector<SplitTree*> TreeList;
    void LoadXmlFile();
    void getValue(SplitTree* tree, SplitTreeNode* node, QXmlStreamReader& xml, int side);
private:
    Ui::qtTestClass ui;

    QAbstractTableModel* windowTable;
    QDomDocument* document;
    QFile* xmlfile;
    QButtonGroup* buttongroup;
};
