#pragma once

#include <QWidget>
#include "ui_splitwindow.h"

class SplitWindow : public QWidget
{
	Q_OBJECT

public:
	SplitWindow(QWidget *parent = Q_NULLPTR);
	~SplitWindow();

private:
	Ui::splitwindow ui;
};
