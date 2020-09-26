#include "screen.h"

QPlatformScreen::QPlatformScreen(QObject* parent)
	: QObject(parent)

{	
	
}

QPlatformScreen::~QPlatformScreen()
{	
	delete window;
	delete button;
}

void QPlatformScreen::setScreen(QScreen* ins)
{
	if (ins != instance)
	{
		instance = ins;

		window = new SplitWindow(nullptr, instance);
		button = new MonitorButton(nullptr, instance);

		connect(button, SIGNAL(sendTree(SplitButton*)),
			window, SLOT(setPreset(SplitButton*)));
		connect(button, SIGNAL(clicked(bool)),
			window, SIGNAL(settedPreset()));
		qDebug() << "ss " << thread();
	}
	
}

QScreen* QPlatformScreen::getScreen()
{	return instance;	}


SplitWindow* QPlatformScreen::getSplitWindow()
{	return window;	}

MonitorButton* QPlatformScreen::getMonitorButton()
{	return button;	}