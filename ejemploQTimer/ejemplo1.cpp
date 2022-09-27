#include "ejemplo1.h"
#include <QTimer>

ejemplo1::ejemplo1(): Ui_Counter()
{
	setupUi(this);
	show();
	connect(startB, SIGNAL(clicked()), this, SLOT(doButton()) );
	connect(stopB, SIGNAL(clicked()), this, SLOT(stopButton()) );
	connect(resetB, SIGNAL(clicked()), this, SLOT(resetButton()) );
	connect(mytimer, SIGNAL(timeout()), this, SLOT(cuenta()));
	connect(horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(cambiarSlider(int)));
	horizontalSlider->setRange(100, 2000);
	
}

void ejemplo1::doButton()
{
	mytimer->start(period);
	qDebug() << period;
}

void ejemplo1::stopButton()
{
	mytimer->stop();
	qDebug() << "click on button";
}

void ejemplo1::resetButton()
{
	mytimer->stop();
	cont = 0;
	lcdNumber->display(cont);
	qDebug() << "click on button";
}

void ejemplo1::cambiarSlider(int valor)
{
	period = valor;
	//qDebug()<<period;
}


void ejemplo1::cuenta()
{
    lcdNumber->display(++cont);
	trick++;
}

