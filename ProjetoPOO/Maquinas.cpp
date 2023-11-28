#include"Maquinas.h"


Maquina::Maquina(int _id, int _tipo, int _x, int _y)
{
	id = _id;
	tipo = _tipo;
	estado = ESTADO_MAQUINA::ON;
	temperat = 0;
	x = _x;
	y = _y;
}

ESTADO_MAQUINA Maquina::getEstado()
{
	return estado;
}

int Maquina::getX()
{
	return x;
}

int Maquina::getY()
{
	return y;
}

Maquina::~Maquina()
{

}

int Maquina::getID()
{
	return id;
}

void Maquina::MostrarMaquina()
{
	cout << "Maquina ID=" << id << endl;
	if (estado == ESTADO_MAQUINA::ON)
		cout << "Estado - Ligada" << endl;
	if (estado == ESTADO_MAQUINA::OFF)
	{
		cout << "Estado - Desligada" << endl;
	}
	cout << "Tipo:" << tipo << endl;
	cout << "Posicao: X=" << x << " Y=" << y << endl << endl;
}

void Maquina::DesligarMaquina()
{
	estado = ESTADO_MAQUINA::OFF;
	cout << "Desligada a maquina ID=" << id << "\n\n";
}
