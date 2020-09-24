#include "splitpreset.h"

SplitPreset::SplitPreset(QObject *parent)
	: QObject(parent)
{
	/*

	QString fileurl = "../SplitPreset.xml";
	xmlfile = new QFile(fileurl);

    if (!xmlfile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return;
    }*/

}

SplitPreset::~SplitPreset()
{
    if (xmlfile->isOpen()) {
        xmlfile->close();
    }
}
 

void SplitPreset::LoadXmlFile() 
{
    QString fileurl = "SplitPreset.xml";
    xmlfile = new QFile(fileurl);

    QXmlStreamReader xml(xmlfile);


    if (!xmlfile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "notopen";
        return;
    }

    //buttongroup = new QButtonGroup();

    if (xml.readNextStartElement()) {
        if (xml.name() == "presettree") {

            int row = 0;

            while (xml.readNextStartElement()) {
                if (xml.name() == "preset_type") {

                    row++;

                    QString preset_type = xml.attributes().value("name").toString();
                    
                    /*QLabel* label = new QLabel(this);
                    label->setText(preset_type);
                    label->setGeometry(0, 0, 100, 20);
                    ui.gridLayout->addWidget(label, row, 0, 1, 1);*/
                    row++;

                    qDebug() << preset_type;

                    int col = 0;
                    while (xml.readNextStartElement()) {
                        if (xml.name() == "preset")
                        {
                            SplitTree* tree = new SplitTree();

                            tree->setPresetTypeName(preset_type.toStdString().c_str(), preset_type.length());

                            QString presetname = xml.attributes().value("name").toString();
                            tree->setName(presetname.toStdString().c_str(), presetname.length());

                            TreeList.push_back(tree);
                            getValue(tree, tree->getRoot(), xml, ROOT);
                            /*SplitButton* button = new SplitButton(parent);
                            button->setTree(tree);
                            buttongroup->addButton(button);
                            ui.gridLayout->addWidget(button, row, col, 1, 1);
                            */
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



void SplitPreset::getValue(SplitTree* tree, SplitTreeNode* node, QXmlStreamReader& xml, int side)
{
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
}

QVector<SplitTree*> SplitPreset::getTreeList() {
    return TreeList;
}


void paintRect(QRect rect, QPainter* painter, SplitTreeNode* node)
{
    static int mg = 3;
    static QMargins margin(mg, mg, mg, mg);

    float width = (float)rect.width() / (float)100;
    float height = (float)rect.height() / (float)100;
    
    if (node != nullptr) {
        if (node->bottomleft == nullptr || node->topright == nullptr) {
            QPoint topl(*node->topleft->x * width, *node->topleft->y * height);
            QPoint btmr(*node->bottomright->x * width, *node->bottomright->y * height);
            QRect splitrect(topl, btmr);
            painter->drawRect(splitrect.marginsRemoved(margin));

        }
        else {
            paintRect(rect, painter, node->pleft);
            paintRect(rect, painter, node->pright);
        }
    }
}