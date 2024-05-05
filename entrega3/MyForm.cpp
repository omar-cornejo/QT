#include "MyForm.h"
#include <QShortcut>  // Para QShortcut
#include <QKeySequence>  // Para QKeySequence
#include <QString>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <QTimer>
#include <QDebug>

MyForm::MyForm(QWidget* parent) : QWidget(parent) {
    ui.setupUi(this);

	// Conectar el botón a la ranura mostrar()
    connect(ui.inici, &QPushButton::clicked, this, &MyForm::mostrar);

	connect(ui.restar, &QPushButton::clicked, this, &MyForm::restar);

	connect(ui.sumar, &QPushButton::clicked, this, &MyForm::sumar);

	connect(ui.Fase, &QSlider::sliderMoved, this, &MyForm::fase);

	connect(ui.timer, &QPushButton::clicked, this, &MyForm::tempo);

	// Crear un atajo para ALT + S
    QShortcut* shortcut2 = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_S), this);
	connect(shortcut2, &QShortcut::activated, this, &MyForm::close);

	
	// Crear un atajo para ALT + I
    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_I), this);

	// Conectar el atajo a la misma función que el botón
    connect(shortcut, &QShortcut::activated, this, &MyForm::mostrar);

	// Crear un atajo para ALT + T
    QShortcut* shortcut1 = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_T), this);

	// Conectar el atajo a la misma función que el botón
    connect(shortcut1, &QShortcut::activated, this, &MyForm::tempo);
	
	amplitud = 0.5;

	fase_id = 0.0;

	inicio = false;

	tiempo = false;

	time = 0;

	// Crear un temporizador
	timer = new QTimer(this);
	// Conectar el temporizador a un método
	connect(timer, &QTimer::timeout, this, &MyForm::aumentar);
}

void MyForm::tempo() {
    if(inicio) {
		qDebug() << "ALT + T ACTIVADO";  // Acción a realizar cuando ALT+T
		if(tiempo == true) {
			timer->stop();
			tiempo = false;
		}
		else if(tiempo == false) {
			// Iniciar el temporizador para que se dispare cada segundo (1000 ms)
			timer->start(1000);  // Se ejecutará cada 1000 ms
			tiempo = true;
		}

	}
}

void MyForm::aumentar() {
	time += 100;
	mostrar();
}

void MyForm::fase() {
	QSlider* a = this->findChild<QSlider*>("Fase");
	//sumar
	if(inicio and ((fase_id < 5.0)) and (a->value() > fase_id)) {
		fase_id += 1;
		mostrar();
	}

	//restar
	else if(inicio and ((fase_id > -5.0)) and (a->value() < fase_id)) {
		fase_id -= 1;
		mostrar();
	}

	if (fase_id > 5.0) {
    fase_id = 5.0;
	} else if (fase_id < -5.0) {
		fase_id = -5.0;
	}

	
}

void MyForm::sumar() {
	if(inicio and (amplitud < 1.0)) {
		amplitud += 0.1;
		mostrar();
	}
	
}

void MyForm::restar() {
	if(inicio and (amplitud > 0.0)) {
		amplitud -= 0.1;
		mostrar();
	}
}

void MyForm::mostrar() {
	inicio = true;

    const float min1 = -1.0f;
    const float max1 = 1.0f;
    const int min2 = -100;
    const int max2 = 100;

    for (int i = 1; i < 11; i++) {
        float funcion = amplitud * std::sin(i + fase_id + time);

        // Escalar el valor a un rango de -100 a 100
        int new_value = (int)(min2 + ((funcion - min1) * (max2 - min2) / (max1 - min1)));

        std::string name = "progressBar" + std::to_string(i);

        // Convertir a QString usando fromStdString
        QString qname = QString::fromStdString(name);

        // Encontrar la barra de progreso por su nombre
        MyProgressBar* myProgressBar = this->findChild<MyProgressBar*>(qname);

        if (myProgressBar) {  // Verificar si se encontró

			myProgressBar->setStyleSheet(
                "QProgressBar::chunk {"
                "background-color: red;"  // Color del chunk
                "}"
                "QProgressBar {"
                "background-color: lightgray;"  // Color del fondo
                "border: 2px solid gray;"      // Opcional: borde
                "border-radius: 5px;"          // Opcional: radio del borde
                "}"
            );

            // Establecer el valor escalado
            myProgressBar->setValue(new_value);
        }
    }
}