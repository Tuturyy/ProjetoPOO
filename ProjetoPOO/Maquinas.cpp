#include"Maquinas.h"

ESTADO_MAQUINA Maquina::getEstado()
{
	return estado;
}

Maquina::Maquina(int _id, int _tipo)
{
	id = _id;
	tipo = _tipo;
	estado = ESTADO_MAQUINA::ON;
	temperat = 0;
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
	cout << "Tipo:" << tipo << endl << endl;
}

void Maquina::DesligarMaquina()
{
	estado = ESTADO_MAQUINA::OFF;
	cout << "Desligada a maquina ID=" << id << "\n\n";
}
