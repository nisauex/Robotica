#ifndef ejemplo1_H
#define ejemplo1_H

#include <QtGui>
#include "ui_counterDlg.h"
#include <QTimer>
#include <chrono>

class ejemplo1 : public QWidget, public Ui_Counter
{
    Q_OBJECT
    public:
        ejemplo1();

    public slots:
        void doButton();
        //void startButton();
        void stopButton();
        void cuenta();
        
    private:
        QTimer *mytimer = new QTimer(this);
        int cont = 0;
        
        //void cuenta();
		
		int trick = 5;
};

#endif // ejemplo1_H
