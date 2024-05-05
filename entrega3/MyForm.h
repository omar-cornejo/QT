#include "ui_MyForm.h"
class MyForm:public QWidget
{
	Q_OBJECT
public:
	MyForm(QWidget *parent=0);
	void mostrar();
	void sumar();
	void restar();
	void fase();
	void tempo();
	void aumentar();
private:
	Ui::Form ui;
	float amplitud;
	float fase_id;
	bool inicio;
	bool tiempo;
	int time;
	QTimer* timer; // Crear un temporizador
};
