#include"Maquinas.h"


Maquina::Maquina(int _id, TIPO_MAQUINA _tipo, int _x, int _y)
{
	id = _id;
	tipo = _tipo;
	if (tipo == TIPO_MAQUINA::Roleta)
	{
		porcentWin = WIN_PORC_ROLETA;
	}
	if (tipo == TIPO_MAQUINA::Poker)
	{
		porcentWin = WIN_PORC_POKER;
	}
	if (tipo == TIPO_MAQUINA::ClassicSlots)
	{
		porcentWin = WIN_PORC_SLOT;
	}
	if (tipo == TIPO_MAQUINA::BlackJack)
	{
		porcentWin = WIN_PORC_BLACKJACK;
	}
	estado = ESTADO_MAQUINA::OFF;
	temperat = 0;
	x = _x;
	y = _y;
	jogador = nullptr;
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
	cout << "Maquina ID-["<< id <<"]"<< endl;
	if (estado == ESTADO_MAQUINA::ON)
	{
		cout << "Estado: ON" << endl;
		jogador->MostrarPessoa();
	}
	if (estado == ESTADO_MAQUINA::OFF)
	{
		cout << "Estado: OFF" << endl;
	}
	cout << "Tipo: ";
	if (tipo==TIPO_MAQUINA::Roleta)
	{
		cout << "Roleta\n";
	}
	if (tipo == TIPO_MAQUINA::Poker)
	{
		cout << "Poker\n";
	}
	if (tipo == TIPO_MAQUINA::ClassicSlots)
	{
		cout << "ClassicSlots\n";
	}
	if (tipo == TIPO_MAQUINA::BlackJack)
	{
		cout << "Blackjack\n";
	}
	cout << "Posicao: X=" << x << " Y=" << y << endl << endl;
}

void Maquina::DesligarMaquina()
{
	estado = ESTADO_MAQUINA::OFF;
	cout << "Desligada a maquina ID=" << id << "\n\n";
}

void Maquina::AddJogadorMaquina(Pessoa* player)
{
	if (estado == ESTADO_MAQUINA::ON)
	{
		cout << "Maquina (" << id << ") ocupada. Impossivel adicionar pessoa.\n\n";
		return;
	}
	jogador = player;
	estado = ESTADO_MAQUINA::ON;
}
