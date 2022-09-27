#include "ejemplo1.h"
#include <bits/stdc++.h>
#include <iostream>

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
	tareasVector();
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


void ejemplo1::tareasVector()
{
	int size = 10;
	std::vector<int> V(size, 0);
	srand(time(0));
	std::generate(V.begin(), V.end(), rand);
	
	std::cout << "Sin ordenar: \n";
	
	for (int i = 0; i < size; i++) {
        	std::cout << V[i] << " ";
   	}
	
	std::sort(V.begin(), V.end());
  
    	std::cout << "Ordenado: \n";
    	
    	for (int i = 0; i < size; i++) {
        	std::cout << V[i] << " ";
   	}
   	
   	std::cout << "Menor elemento: \n";
   	
   	int menor = V[0];
   	
   	for(int i = 0; i < size; i++){
   		if(V[i] < menor){
   			menor = V[i];
   		}
   	}
   	
   	std::cout << menor << "\n";
   	
   	std::cout << "Elementos en un rango entre 0 y 2000000: \n";
   	int principio = 0;
   	int fin = 2000000;
   	for (int i = 0; i < size; i++) {
        	if(V[i] >= principio && V[i] <= fin){
        		std::cout << V[i] << " ";
        	}
   	}
   	
   	std::cout << "Shuffle: \n";
   	int aux;
   	for (int i = 0; i < size; i++) {
        	aux = V[i];
        	V[i] = V[size - 1 - i];
        	V[size - 1 - i] = aux;
   	}
   	
   	
}


