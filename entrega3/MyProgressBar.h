

#ifndef MYPROGRESS_BAR_H
#define MYPROGRESS_BAR_H

#include <QProgressBar>
#include <QObject>  // Importante para usar Q_OBJECT

class MyProgressBar:public QProgressBar
{
	Q_OBJECT
	public:
		MyProgressBar(QWidget *parent);
		
    public slots:

    signals:
};

#endif

