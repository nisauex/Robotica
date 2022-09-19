#ifndef ejemplo1_H
#define ejemplo1_H

#include <QtGui>
#include "ui_counterDlg.h"
#include <chrono>
#include "timer.h"

class ejemplo1 : public QWidget, public Ui_Counter
{
    Q_OBJECT
    public:
        ejemplo1();

    public slots:
        void doButton();
        void doStop();
        void restarUnSegundo();
        void mostrarGlobal();
        
    private:
        Timer mytimer, mytimerLong;
        int cont = 0, contGlobal = 0;
        
        void cuenta();
        
        void cuentaGlobal();
		
		int trick = 5;
};

#endif // ejemplo1_H
