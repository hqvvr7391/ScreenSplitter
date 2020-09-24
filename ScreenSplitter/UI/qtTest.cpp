#include "qtTest.h"

qtTest::qtTest(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    QString fileurl = "XMLFile.xml";
    xmlfile = new QFile(fileurl);

    QXmlStreamReader xml(xmlfile);


    if (!xmlfile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "open";
        return;
    }

    /*if (!document->setContent(xmlfile))
    {
        qDebug() << "setcontext";
        return;
    }*/
    buttongroup = new QButtonGroup();
    
    if (xml.readNextStartElement()) {
        if (xml.name() == "presettree") {
            int row = 0;
            while (xml.readNextStartElement()) {
                if (xml.name() == "preset_type") {
                    row++;
                    QString preset_type = xml.attributes().value("name").toString();
                    QLabel* label = new QLabel(this);
                    label->setText(preset_type);
                    label->setGeometry(0, 0, 100, 20);
                    ui.gridLayout->addWidget(label, row, 0, 1, 1);
                    row++;

                    qDebug() << preset_type;

                    int col = 0;
                    while (xml.readNextStartElement()) {
                        if (xml.name() == "preset")
                        {
                            SplitTree* tree = new SplitTree();
                            //TreeList.push_back(tree);
                            getValue(tree, tree->getRoot(), xml, ROOT);
                            SplitButton* button = new SplitButton(parent);
                            button->setTree(tree);
                            buttongroup->addButton(button);
                            ui.gridLayout->addWidget(button, row, col, 1, 1);

                            col++;
                        }
                        else    xml.skipCurrentElement();
                    }
                }
                else    xml.skipCurrentElement();
            }
        }
        else    xml.raiseError(QObject::tr("incorrect File"));
    }
}


void qtTest::getValue(SplitTree* tree, SplitTreeNode* node,  QXmlStreamReader &xml, int side)
{

#ifndef TEST
    while (xml.readNextStartElement()) {
        if (xml.name() == "value")
        {
            SplitData data = { 0, 0 };
            while (xml.readNextStartElement()) {
                qDebug() << xml.name();
                if (xml.name() == "type") {
                    QString s = xml.readElementText();
                    qDebug() << s;
                    data.type = s.toInt();
                }
                else if (xml.name() == "ratio") {
                    QString s = xml.readElementText();
                    qDebug() << s;
                    data.ratio = s.toInt();
                }
                else    xml.skipCurrentElement();
            }

             tree->setNode(node, &data, side);
        }
        else if (xml.name() == "subtree")
        {
            QString side = xml.attributes().value("side").toString();
            qDebug() << side;
            int treeside = (side == "left") ? LEFT : RIGHT;
           
            if (treeside == LEFT) {
                getValue(tree, node->pleft, xml, treeside);
            }
            else if (treeside == RIGHT) {
                getValue(tree, node->pright, xml, treeside);
            }
            

        }
        else    xml.skipCurrentElement();
    }

#else

    while (xml.readNextStartElement()) {
        if (xml.name() == "value")
        {
            bool type = 0;
            int ratio = 0;
            while (xml.readNextStartElement()) {
                qDebug() << xml.name();
                if (xml.name() == "type") {
                    QString s = xml.readElementText();
                    qDebug() << s;
                    type = s.toInt();
                }
                else if (xml.name() == "ratio") {
                    QString s = xml.readElementText();
                    qDebug() << s;
                    ratio = s.toInt();
                }
                else    xml.skipCurrentElement();
            }
            
             tree->setNode(ratio, type);

        }
        else if (xml.name() == "subtree")
        {
            if (xml.attributes().value("idref") != "NULL")
                getValue(tree, xml);
            else
                xml.skipCurrentElement();
        }
        else    xml.skipCurrentElement();
    }

#endif
}
qtTest::~qtTest()
{
    if (xmlfile->isOpen()) {
        xmlfile->close();
    }
}

void qtTest::LoadXmlFile()
{

}
