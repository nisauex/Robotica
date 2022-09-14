#include "ejemplo1.h"

ejemplo1::ejemplo1(): Ui_Counter()
{
	setupUi(this);
	show();
	connect(startButton, SIGNAL(clicked()), this, SLOT(doButton()) );
	connect(button, SIGNAL(clicked()), this, SLOT(doStop()) );
	connect(RestarUnSegundo, SIGNAL(clicked()), this, SLOT(restarUnSegundo()) );
	connect(tiempoGlobal, SIGNAL(clicked()), this, SLOT(mostrarGlobal()) );
	mytimer.connect(std::bind(&ejemplo1::cuenta, this));
	mytimer.connect(std::bind(&ejemplo1::cuentaGlobal, this));
	
	//while(true){cuentaGlobal();}
}

void ejemplo1::doButton()
{
	mytimer.start(500);
	qDebug() << "click on button";
}

void ejemplo1::doStop()
{
	mytimer.stop();
	qDebug() << "click on button";
}

void ejemplo1::restarUnSegundo()
{
	cont--;
	qDebug() << "click on button";
}

void ejemplo1::cuenta()
{
    lcdNumber->display(++cont);
	trick++;
}

void ejemplo1::cuentaGlobal()
{
	
    ++contGlobal;
}

void ejemplo1::mostrarGlobal()
{
	lcdNumber->display(contGlobal);
}


