#include"Maquinas.h"
#include"Casino.h"


Maquina::Maquina(int _id, TIPO_MAQUINA _tipo, int _x, int _y)
{
	id = _id;
	tipo = _tipo;
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

bool Maquina::Roulette(int bet, Casino* casino)
{
	double resultado = Util::RandNumDouble(0, 1);
	double jogadorJogaOnde = Util::RandNumDouble(0, 1);
	if (jogadorJogaOnde <= 0.95)//95% de chance de o jogador apostar no vermelho/preto
	{
		if (resultado <= (18.0 / 37))//18 de 37 chances de ganhar
		{
			jogador->Saldo += (bet * 2) - bet;//roleta acaba no ver/pret. 2x Aposta
			casino->DinheiroPerdido += bet;
			cout << "O jogador " << jogador->getNome() << " ganhou " << (bet * 2) << "EUR.\n";
			return true;
		}
		else
		{
			jogador->Saldo -= bet;
			casino->DinheiroRecebido += bet;
			cout << "O jogador " << jogador->getNome() << " perdeu " << bet << "EUR na roleta.\n";
			return false;
		}
	}
	else //o jogador aposta no verde
	{
		if (resultado <= (1.0 / 37))
		{
			jogador->Saldo += (bet * 14) - bet;//roleta acaba no verde. 14x Aposta
			casino->DinheiroPerdido += (bet * 14) - bet;
			cout << "Incrivel verde na roleta. O jogador " << jogador->getNome() << " ganhou " << (bet * 14) << "EUR.\n";
			return true;
		}
		else
		{
			jogador->Saldo -= bet;
			casino->DinheiroRecebido += bet;
			cout << "O jogador " << jogador->getNome() << " perdeu " << bet << "EUR na roleta.\n";
			return false;
		}
	}
}

bool Maquina::Slot(int bet, Casino* casino)
{
	double resultado = Util::RandNumDouble(0, 1);
	if (resultado <= 0.000001)// 0.0001%! :O
	{
		int multiplicador = Util::RandNumInt(10000, 1000000);
		jogador->Saldo += (bet * multiplicador) - bet;
		casino->DinheiroPerdido += (bet * multiplicador) - bet;
		cout << "MEGA JACKPOT!! O JOGADOR " << jogador->getNome() << " GANHOU " << bet * multiplicador << "EUR (x" <<multiplicador<<") NA SLOT.\n";
		return true;
	}
	if (resultado <= 0.001)//0.1%
	{
		jogador->Saldo += (bet * 1000) - bet;
		casino->DinheiroPerdido += (bet * 1000) - bet;
		cout << "FENOMENAL! O jogador " << jogador->getNome() << " ganhou " << bet * 1000 << "EUR (x1000) na slot.\n";
		return true;
	}
	if (resultado <= 0.01)//1%
	{
		jogador->Saldo += (bet * 100) - bet;
		casino->DinheiroPerdido += (bet * 100) - bet;
		cout << "Vitoria epica! O jogador " << jogador->getNome() << " ganhou " << bet * 100 << "EUR (x100) na slot.\n";
		return true;
	}
	if (resultado <= 0.10)//10%
	{
		jogador->Saldo += (bet * 3) - bet;
		casino->DinheiroPerdido += (bet * 3) - bet;
		cout << "O jogador " << jogador->getNome() << " triplicou a sua aposta e ganhou " << bet * 3 << "EUR na slot.\n";
		return true;
	}
	if (resultado <= 0.40)//40%
	{
		jogador->Saldo += (bet * 2) - bet;
		casino->DinheiroPerdido += (bet * 2) - bet;
		cout << "O jogador " << jogador->getNome() << " ganhou " << bet * 2 << "EUR na slot.\n";
		return true;
	}
	else//60%
	{
		jogador->Saldo -= bet;
		casino->DinheiroRecebido += bet;
		cout << "O jogador " << jogador->getNome() << " perdeu " << bet  << "EUR na slot.\n";
		return false;
	}
}

bool Maquina::JogadorJoga(int bet, Casino* casino)
{
	if (jogador->Saldo >0)
	{
		if (tipo == TIPO_MAQUINA::Roleta)
		{
			Roulette(bet, casino);
			return 0;
		}

		if (tipo == TIPO_MAQUINA::Poker)
		{

		}

		if (tipo == TIPO_MAQUINA::ClassicSlots)
		{
			Slot(bet, casino);
			return 0;
		}

		if (tipo == TIPO_MAQUINA::BlackJack)
		{

		}
	}
	else
	{
		cout << "Saldo Insuficiente\n";
		return 0;
	}
}
