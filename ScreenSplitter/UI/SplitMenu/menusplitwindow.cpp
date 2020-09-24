#include "menusplitwindow.h"

menuSplitWindow::menuSplitWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	//this->setGeometry(QRect(QPoint(0,0),parent->size()));
	this->adjustSize();
	qDebug() << this->geometry();

	plist_monitor = QGuiApplication::screens();

	virtualsize = plist_monitor[0]->virtualGeometry();
	qDebug() << virtualsize.size();
	qDebug() << ui.monitorframe->size();
	
	float horz_ratio = (float)ui.monitorframe->width() / (float)virtualsize.width();
	float vert_ratio = (float)ui.monitorframe->height() / (float)virtualsize.height();
	
	ratio = (horz_ratio < vert_ratio) ? horz_ratio : vert_ratio;

	
	QSize monitororiginsize = ui.monitorframe->size()/2 - virtualsize.size() * ratio / 2;
	QPoint monitororigin = QPoint(monitororiginsize.width(), monitororiginsize.height());


	grpmonitorbuttons = new QButtonGroup();
	

	for (int i = 0;i < plist_monitor.size();i++) {
		QScreen* monitor = plist_monitor[i];
		MonitorButton* btn = new MonitorButton(ui.monitorframe, monitor);
		monitorbutton.append(btn);
		grpmonitorbuttons->addButton((QAbstractButton*)btn, i);
		//monitorbutton[i]->setMonitor(monitor);
		monitorbutton[i]->setGeometry(
			QRect(monitororigin + monitor->geometry().topLeft() * ratio, monitor->size() * ratio));
	}

	qDebug() << grpmonitorbuttons->buttons();
	grpmonitorbuttons->button(0)->setChecked(true);
	connect(grpmonitorbuttons, SIGNAL(idClicked(int)), this, SLOT(setMBtnPreset(int)));

	grppresetbuttons = new QButtonGroup(this);

	connect(grppresetbuttons, SIGNAL(idClicked(int)), this, SLOT(setMBtnPreset(int)));
	
	

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &menuSplitWindow::updateMonitorBtn);
	timer->setInterval(2000);
	timer->start();
}

menuSplitWindow::~menuSplitWindow()
{
	while (monitorbutton.isEmpty()) delete monitorbutton.takeLast();
	while (plist_monitor.isEmpty()) delete plist_monitor.takeLast();

	delete grpmonitorbuttons;

	delete timer;
}

void menuSplitWindow::updateMonitorBtn()
{
	for (int i = 0; i < plist_monitor.size(); i++)
	{
		monitorbutton[i]->updateCapture();
	}
	
}


void menuSplitWindow::asdf()
{
	qDebug() << "SFDFSDFZXZC";
}

void menuSplitWindow::setMBtnPreset(int id)
{
	SplitButton* pbtn = (SplitButton*) grppresetbuttons->button(id);
	MonitorButton* mbtn = (MonitorButton*) grpmonitorbuttons->checkedButton();
	mbtn->setPreset(pbtn);
	qDebug() << "SdfSDFS";
}

void menuSplitWindow::showSplitWindow(int id)
{
	int i = 0;
	while (grpmonitorbuttons->button(i) != nullptr) {

		MonitorButton* mnbtn = (MonitorButton*)grpmonitorbuttons->button(i);
		if(id == i)	mnbtn->showSplitWindow();
		else mnbtn->hideSplitWindow();
		i++;
	}
}

void menuSplitWindow::updateSplitWindow(int id)
{
	int i = 0;
	while (grpmonitorbuttons->button(i) != nullptr) {

		MonitorButton* mnbtn = (MonitorButton*)grpmonitorbuttons->button(i);
		if (id == i) {
				mnbtn->showSplitWindow();
				mnbtn->updateSplitWindow();

				innerrect = mnbtn->getRect();
		}
		else mnbtn->hideSplitWindow();
		i++;
	}
}

void menuSplitWindow::hideSplitWindow() 
{
	emit sendRect(innerrect);
	QList<QAbstractButton*> mnbtns =grpmonitorbuttons->buttons();
	for (int i = 0; i < mnbtns.size(); i++) {
		MonitorButton* btn = (MonitorButton*)mnbtns.at(i);
		btn->hideSplitWindow();
	}
}

void menuSplitWindow::paintEvent(QPaintEvent* event)
{
	//QPainter painter(this);
	//QPen pen;

}


void menuSplitWindow::createPresetButtons(QVector<SplitTree*> treelist)
{
	QString preset_type("");
	int row = -1;
	int col = 0;

	for (int i = 0; i < treelist.size(); ++i) {
		SplitTree* tree = treelist.at(i);
		
		QString treetypename = QString(tree->getPresetTypeName());
		
		if (treetypename != preset_type) {
			row++;
			col = 0;
			QLabel* label = new QLabel(treetypename);
			label->setText(preset_type);
			label->setGeometry(0, 0, 100, 20);
			ui.gridLayout_2->addWidget(label, row, col, 1, 1);
			row++;
			
			preset_type = treetypename;
		}
		SplitButton* prstbtn = new SplitButton(this);
		ui.gridLayout_2->addWidget(prstbtn, row, col, 1, 1);
		prstbtn->setTree(tree);
		grppresetbuttons->addButton(prstbtn, i);
		
		col++;
	}
	grppresetbuttons->button(0)->setChecked(true);	
}
