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

bool Maquina::JogadorJoga(int bet)
{
	double resultado = Util::RandNumDouble(0, 1); //numero random entre 0 e 1
	if (tipo == TIPO_MAQUINA::Roleta)
	{
		if (resultado <= ((WIN_PORC_ROLETA) / 100.0))
		{
			double probabilidade = Util::RandNumDouble(0, 1);
			if (probabilidade<=(1.0/19))
			{
				jogador->Saldo += bet * 14;//roleta acaba verde a aposta é multiplicada por 14
				cout << "Incrivel verde na roleta. O jogador " << jogador->getNome() << " ganhou " << (bet * 14) << "EUR.\n";
				return true;
			}
			else
			{
				jogador->Saldo += bet * 2;// roleta acaba ver/pret a aposta é duplicada
				cout << "O jogador " << jogador->getNome() << " ganhou " << (bet * 2) << "EUR na roleta.\n";
				return true;
			}
		}
		cout << "O jogador " << jogador->getNome() << " perdeu " << bet << "EUR na roleta.\n";
		return false;
	}

	if (tipo == TIPO_MAQUINA::Poker)
	{
		if (resultado <= ((WIN_PORC_POKER) / 100.0))
		{

		}
	}

	if (tipo == TIPO_MAQUINA::ClassicSlots)
	{
		if (resultado <= ((WIN_PORC_SLOT) / 100.0))
		{

		}
	}

	if (tipo == TIPO_MAQUINA::BlackJack)
	{
		if (resultado <= ((WIN_PORC_BLACKJACK) / 100.0))
		{

		}
	}

}
