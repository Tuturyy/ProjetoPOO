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
	if (tipo == TIPO_MAQUINA::Roleta)
	{
		porcentWin = (18.0 / 37)*100;
	}
	estado = ESTADO_MAQUINA::OFF;
	temperat = 0;
	x = _x;
	y = _y;
	Lucro = 0;
	Utilizacoes = 0;
	jogador = nullptr;
}

ESTADO_MAQUINA Maquina::getEstado()
{
	return estado;
}

TIPO_MAQUINA Maquina::getTipo()
{
	return tipo;
}

Pessoa* Maquina::getJogador()
{
	return jogador;
}

string Maquina::TipoMaquinaString()
{
	if (tipo == TIPO_MAQUINA::Poker)
	{
		return "Poker";
	}
	if (tipo == TIPO_MAQUINA::ClassicSlots)
	{
		return "ClassicSlots";
	}
	if (tipo == TIPO_MAQUINA::BlackJack)
	{
		return "BlackJack";
	}
	if (tipo == TIPO_MAQUINA::Roleta)
	{
		return "Roleta";
	}
	return "Erro no tipo de maquina.";
}

int Maquina::getTempoJogadaMaquina()
{
	if (tipo == TIPO_MAQUINA::Poker)
	{
		return TEMPO_JOGADA_POKER;
	}
	if (tipo == TIPO_MAQUINA::ClassicSlots)
	{
		return TEMPO_JOGADA_SLOT;
	}
	if (tipo == TIPO_MAQUINA::BlackJack)
	{
		return TEMPO_JOGADA_BLACKJACK;
	}
	if (tipo == TIPO_MAQUINA::Roleta)
	{
		return TEMPO_JOGADA_ROLETA;
	}
	return 0;
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
	cout << "\nMaquina ID-["<< id <<"]"<< endl;
	if (estado == ESTADO_MAQUINA::ON)
	{
		cout << "Estado: ON" << endl;
		cout << "Jogador: " << jogador->getNome() << " (" << jogador->getID() << ")\n";
	}
	if (estado == ESTADO_MAQUINA::OFF)
	{
		cout << "Estado: OFF" << endl;
	}
	cout << "Tipo: " << TipoMaquinaString() << "\n";
	cout << "Posicao: X=" << x << " Y=" << y << endl;
	cout << "Utilizacoes: " << Utilizacoes << endl;
	cout << "Lucro: " << Lucro << endl;
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
	player->SetMaquina(this);
	estado = ESTADO_MAQUINA::ON;
}

void Maquina::RemoverJogadorMaquina()
{
	if (jogador != nullptr)
	{
		jogador->SetMaquina(nullptr);
		jogador = nullptr;
		estado = ESTADO_MAQUINA::OFF;
		return;
	}
	else
		cout << "Impossivel remover jogador da Maquina (" << id << "). Nao existe jogador.\n";
}

int Maquina::CalcularBet()
{
	if (jogador->getSaldo() > 0)
	{
		if (tipo == TIPO_MAQUINA::Roleta)
		{
			int apostaRoleta = 0;
			double porcentagemSaldo = 0;
			double probabilidade = Util::RandNumDouble(0, 1);
			if (probabilidade<=0.90)// 90% de chances de o jogador apostar 1 a 5% do seu saldo
			{
				porcentagemSaldo = Util::RandNumDouble(0.01, 0.05);
				apostaRoleta = jogador ->Saldo * porcentagemSaldo;
				if (apostaRoleta < 1) {
					apostaRoleta = 1; // valor minimo da aposta e 1
				}
				return apostaRoleta;
			}
			else{
				porcentagemSaldo = Util::RandNumDouble(0.7, 1);// 10% de apostar 70 a 100% do saldo
				apostaRoleta = jogador->Saldo * porcentagemSaldo;
				if (apostaRoleta < 1) {
					apostaRoleta = 1; // valor minimo da aposta e 1
				}
				return apostaRoleta;
			}
		}

		if (tipo == TIPO_MAQUINA::Poker)
		{

		}

		if (tipo == TIPO_MAQUINA::ClassicSlots)//Valores min 0 , max 10
		{
			int apostaSlot = 0;
			if(jogador->Saldo >=10)
			{
				apostaSlot = Util::RandNumInt(1, 10);
				return apostaSlot;
			}
			else
			{
				apostaSlot = Util::RandNumInt(1, jogador->Saldo);
				return apostaSlot;
			}
		}

		if (tipo == TIPO_MAQUINA::BlackJack)
		{
			int apostaRoleta = 0;
			double porcentagemSaldo = 0;
			double probabilidade = Util::RandNumDouble(0, 1);
			if (probabilidade <= 0.90)// 90% de chances de o jogador apostar 1 a 5% do seu saldo
			{
				porcentagemSaldo = Util::RandNumDouble(0.01, 0.05);
				apostaRoleta = jogador->Saldo * porcentagemSaldo;
				if (apostaRoleta < 1) {
					apostaRoleta = 1; // valor minimo da aposta e 1
				}
				return apostaRoleta;
			}
			else {
				porcentagemSaldo = Util::RandNumDouble(0.7, 1);// 10% de apostar 70 a 100% do saldo
				apostaRoleta = jogador->Saldo * porcentagemSaldo;
				if (apostaRoleta < 1) {
					apostaRoleta = 1; // valor minimo da aposta e 1
				}
				return apostaRoleta;
			}
		}
	}
	else return 0;
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
			jogador->Lucro += bet;
			casino->DinheiroPerdido += bet;
			cout << "O jogador " << jogador->getNome() << " ganhou " << (bet * 2) << "EUR.\n";
			return true;
		}
		else
		{
			jogador->Saldo -= bet;
			jogador->Lucro -= bet;
			casino->DinheiroRecebido += bet;
			Lucro += bet;
			cout << "O jogador " << jogador->getNome() << " perdeu " << bet << "EUR na roleta.\n";
			return false;
		}
	}
	else //o jogador aposta no verde
	{
		if (resultado <= (1.0 / 37))
		{
			jogador->Saldo += (bet * 14) - bet;//roleta acaba no verde. 14x Aposta
			jogador->Lucro += (bet * 14) - bet;
			casino->DinheiroPerdido += (bet * 14) - bet;
			cout << "Incrivel verde na roleta. O jogador " << jogador->getNome() << " ganhou " << (bet * 14) << "EUR.\n";
			return true;
		}
		else
		{
			jogador->Saldo -= bet;
			jogador->Lucro -= bet;
			casino->DinheiroRecebido += bet;
			Lucro += bet;
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
		jogador->Lucro += (bet * multiplicador) - bet;
		casino->DinheiroPerdido += (bet * multiplicador) - bet;
		cout << "MEGA JACKPOT!! O JOGADOR " << jogador->getNome() << " GANHOU " << bet * multiplicador << "EUR (x" <<multiplicador<<") NA SLOT.\n";
		return true;
	}
	if (resultado <= 0.0002)//0.02%
	{
		int multiplicador2 = Util::RandNumInt(1000, 5000);
		jogador->Saldo += (bet * multiplicador2) - bet;
		jogador->Lucro += (bet * multiplicador2) - bet;
		casino->DinheiroPerdido += (bet * multiplicador2) - bet;
		cout << "FENOMENAL! O jogador " << jogador->getNome() << " ganhou " << bet * multiplicador2 << "EUR (x" << multiplicador2 << ") na slot.\n";
		return true;
	}
	if (resultado <= 0.001)//0.1%
	{
		jogador->Saldo += (bet * 100) - bet;
		jogador->Lucro += (bet * 100) - bet;
		casino->DinheiroPerdido += (bet * 100) - bet;
		cout << "Vitoria epica! O jogador " << jogador->getNome() << " ganhou " << bet * 100 << "EUR (x100) na slot.\n";
		return true;
	}
	if (resultado <= 0.05)//5%
	{
		jogador->Saldo += (bet * 3) - bet;
		jogador->Lucro += (bet * 3) - bet;
		casino->DinheiroPerdido += (bet * 3) - bet;
		cout << "O jogador " << jogador->getNome() << " triplicou a sua aposta e ganhou " << bet * 3 << "EUR na slot.\n";
		return true;
	}
	if (resultado <= 0.35)//35%
	{
		jogador->Saldo += (bet * 2) - bet;
		jogador->Lucro += bet;
		casino->DinheiroPerdido += (bet * 2) - bet;
		cout << "O jogador " << jogador->getNome() << " ganhou " << bet * 2 << "EUR na slot.\n";
		return true;
	}
	else//65%
	{
		jogador->Saldo -= bet;
		jogador->Lucro -= bet;
		casino->DinheiroRecebido += bet;
		cout << "O jogador " << jogador->getNome() << " perdeu " << bet  << "EUR na slot.\n";
		return false;
	}
}

bool Maquina::BlackJack(int bet, Casino* casino)
{
	double probabilidade = Util::RandNumDouble(0, 1);
	if (probabilidade<=0.0475)// 4% de chance de blackjack 2.5x aposta
	{
		jogador->Saldo += (bet*2.5)-bet;
		jogador->Lucro += (bet * 2.5) - bet;
		casino->DinheiroPerdido += bet;
		cout << "BlackJack! O jogador " << jogador->getNome() << " ganhou " << bet * 2.5 << "EUR no blackjack.\n";
		return true;
	}
	if (probabilidade <= 0.4222)// 42% chance de o jogar 2x aposta
	{
		jogador->Saldo += bet;
		jogador->Lucro += bet;
		casino->DinheiroPerdido += bet;
		cout << "O jogador " << jogador->getNome() << " ganhou " << bet * 2 << "EUR no blackjack.\n";
		return true;
	}
	else //o jogador perde
	{
		jogador->Saldo -= bet;
		jogador->Lucro -= bet;
		Lucro += bet;
		casino->DinheiroRecebido += bet;
		cout << "O jogador " << jogador->getNome() << " perdeu " << bet << "EUR no blackjack.\n";
		string msg = "O jogador perdeu " + to_string(bet) + "EUR no blackjack.\n";
		jogador->historico.push_back(msg);
		return false;
	}
}

bool Maquina::JogadorJoga(int bet, Casino* casino)
{
	if (jogador->Saldo >0)
	{
		if (tipo == TIPO_MAQUINA::Roleta)
		{
			Utilizacoes++;
			return (Roulette(bet, casino));
		}

		if (tipo == TIPO_MAQUINA::Poker)
		{
			//pa fazer
			Utilizacoes++;
		}

		if (tipo == TIPO_MAQUINA::ClassicSlots)
		{
			Utilizacoes++;
			return Slot(bet, casino);
		}

		if (tipo == TIPO_MAQUINA::BlackJack)
		{
			Utilizacoes++;
			return BlackJack(bet, casino);

		}
	}
	else
	{
		cout << "Saldo Insuficiente\n";
		return 0;
	}
}
