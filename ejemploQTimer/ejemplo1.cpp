#include "ejemplo1.h"
#include <QTimer>

ejemplo1::ejemplo1(): Ui_Counter()
{
	setupUi(this);
	show();
	connect(startB, SIGNAL(clicked()), this, SLOT(doButton()) );
	connect(stopB, SIGNAL(clicked()), this, SLOT(stopButton()) );
	connect(mytimer, SIGNAL(timeout()), this, SLOT(cuenta()));
	//mytimer->start(10);
}

void ejemplo1::doButton()
{
	mytimer->start(1000);
	qDebug() << "click on button";
}

void ejemplo1::stopButton()
{
	mytimer->stop();
	qDebug() << "click on button";
}


void ejemplo1::cuenta()
{
    lcdNumber->display(++cont);
	trick++;
}

