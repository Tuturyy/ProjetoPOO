#include"Maquinas.h"


Maquina::Maquina(int _id, TIPO_MAQUINA _tipo, int _x, int _y)
{
	id = _id;
	tipo = _tipo;
	if (tipo == TIPO_MAQUINA::Roleta)
	{
		//porcentWin = WIN_PORC_ROLETA;
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

int Maquina::JogadorJoga(int bet)
{
	if (jogador->Saldo >0)
	{
		double resultado = Util::RandNumDouble(0, 1); //numero random entre 0 e 1
		if (tipo == TIPO_MAQUINA::Roleta)
		{
			double jogadorJogaOnde = Util::RandNumDouble(0, 1);
			if (jogadorJogaOnde <= 0.95)//95% de chance de o jogador apostar no vermelho/preto
			{
				if (resultado <= (18.0 / 37))//18 de 37 chances de ganhar
				{
					jogador->Saldo += (bet * 2)-bet;//roleta acaba no ver/pret. 2x Aposta
					cout << "O jogador " << jogador->getNome() << " ganhou " << (bet * 2) << "EUR.\n";
					return ((-bet * 2) + bet);
				}
				else
				{
					jogador->Saldo -= bet;
					cout << "O jogador " << jogador->getNome() << " perdeu " << bet << "EUR na roleta.\n";
					return bet;
				}
			}
			else //o jogador aposta no verde
			{
				if (resultado <= (1.0 / 37))
				{
					jogador->Saldo += (bet * 14)-bet;//roleta acaba no verde. 14x Aposta
					cout << "Incrivel verde na roleta. O jogador " << jogador->getNome() << " ganhou " << (bet * 14) << "EUR.\n";
					return ((-bet * 14) + bet);
				}
				else
				{
					jogador->Saldo -= bet;
					cout << "O jogador " << jogador->getNome() << " perdeu no verde " << bet << "EUR na roleta.\n";
					return bet;
				}
			}
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
	cout << "Saldo Insuficiente\n";
	return 0;
}
