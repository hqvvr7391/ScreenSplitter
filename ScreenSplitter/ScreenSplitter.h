#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScreenSplitter.h"

class ScreenSplitter : public QMainWindow
{
    Q_OBJECT

public:
    ScreenSplitter(QWidget *parent = Q_NULLPTR);

private:
    Ui::ScreenSplitterClass ui;
};
