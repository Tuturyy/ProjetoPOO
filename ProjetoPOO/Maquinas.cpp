#include"Maquinas.h"
#include"Casino.h"
#include"Uteis.h"


Maquina::Maquina(int _id, TIPO_MAQUINA _tipo, int _x, int _y)
{
	id = _id;
	tipo = _tipo;
	if (tipo == TIPO_MAQUINA::Poker)
	{
		porcentWin = WIN_PORC_POKER;
		TempoCadaJogada = TEMPO_JOGADA_POKER;
	}
	if (tipo == TIPO_MAQUINA::ClassicSlots)
	{
		porcentWin = WIN_PORC_SLOT;
		TempoCadaJogada = TEMPO_JOGADA_SLOT;
	}
	if (tipo == TIPO_MAQUINA::BlackJack)
	{
		porcentWin = WIN_PORC_BLACKJACK;
		TempoCadaJogada = TEMPO_JOGADA_BLACKJACK;
	}
	if (tipo == TIPO_MAQUINA::Roleta)
	{
		porcentWin = (18.0 / 37)*100;
		TempoCadaJogada = TEMPO_JOGADA_ROLETA;
	}
	estado = ESTADO_MAQUINA::OFF;
	temperatura = 20;
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

double Maquina::getPorcentWin()
{
	return porcentWin;
}

int Maquina::getTempoCadaJogada()
{
	return TempoCadaJogada;
}

void Maquina::setPorcentWin(double novaPorcentW)
{
	porcentWin = novaPorcentW;
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
	temperatura = 20;
	if (jogador != nullptr)
	{
		RemoverJogadorMaquina();
	}
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

void Maquina::AtualizarDadosAposAposta(int bet, bool ganhou, Casino* casino,  int multiplicadorBet , string MensagemEspecial = "")
{
	if (ganhou)
	{
		jogador->setSaldo(jogador->getSaldo() + (bet*multiplicadorBet)-bet);
		jogador->Lucro += ((bet * multiplicadorBet) - bet);
		Lucro -= ((bet * multiplicadorBet) - bet);
		casino->DinheiroPerdido += ((bet * multiplicadorBet) - bet);
		string msg = MensagemEspecial + "O jogador ganhou " + to_string(bet) + "EUR ("+ to_string(multiplicadorBet)+"x) em " + TipoMaquinaString() + ".\n";
		jogador->historico->push_back(msg);
	}
	else
	{
		jogador->setSaldo(jogador->getSaldo() - bet);
		jogador->Lucro -= bet;
		Lucro += bet;
		casino->DinheiroRecebido += bet;
		string msg = "O jogador perdeu " + to_string(bet) + "EUR em " + TipoMaquinaString() + ".\n";
		jogador->historico->push_back(msg);
	}
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
				apostaRoleta = jogador->getSaldo() * porcentagemSaldo;
				if (apostaRoleta < 1) {
					apostaRoleta = 1; // valor minimo da aposta e 1
				}
				return apostaRoleta;
			}
			else{
				porcentagemSaldo = Util::RandNumDouble(0.7, 1);// 10% de apostar 70 a 100% do saldo
				apostaRoleta = jogador->getSaldo() * porcentagemSaldo;
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
			if(jogador->getSaldo() >= 10)
			{
				apostaSlot = Util::RandNumInt(1, 10);
				return apostaSlot;
			}
			else
			{
				apostaSlot = Util::RandNumInt(1, jogador->getSaldo());
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
				apostaRoleta = jogador->getSaldo() * porcentagemSaldo;
				if (apostaRoleta < 1) {
					apostaRoleta = 1; // valor minimo da aposta e 1
				}
				return apostaRoleta;
			}
			else {
				porcentagemSaldo = Util::RandNumDouble(0.7, 1);// 10% de apostar 70 a 100% do saldo
				apostaRoleta = jogador->getSaldo() * porcentagemSaldo;
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
			jogador->setSaldo(jogador->getSaldo() + bet); //roleta acaba no ver/pret. 2x Aposta
			jogador->Lucro += bet;
			casino->DinheiroPerdido += bet;
			cout << "O jogador " << jogador->getNome() << " ganhou " << (bet * 2) << "EUR na roleta.\n";
			string msg = "O jogador ganhou " + to_string(bet*2) + "EUR na roleta.\n";
			jogador->historico->push_back(msg);
			return true;
		}
		else //jogador perde
		{
			jogador->setSaldo(jogador->getSaldo() - bet);
			jogador->Lucro -= bet;
			casino->DinheiroRecebido += bet;
			Lucro += bet;
			cout << "O jogador " << jogador->getNome() << " perdeu " << bet << "EUR na roleta.\n";
			string msg = "O jogador perdeu " + to_string(bet) + "EUR na roleta.\n";
			jogador->historico->push_back(msg);
			return false;
		}
	}
	else //o jogador aposta no verde
	{
		if (resultado <= (1.0 / 37))
		{
			jogador->setSaldo(jogador->getSaldo() + (bet * 14)-bet); //roleta acaba no verde. 14x Aposta
			jogador->Lucro += (bet * 14) - bet;
			casino->DinheiroPerdido += (bet * 14) - bet;
			cout << "Incrivel verde na roleta. O jogador " << jogador->getNome() << " ganhou " << (bet * 14) << "EUR.\n";
			string msg = "Verde! O jogador ganhou " + to_string(bet*14) + "EUR na roleta.\n";
			jogador->historico->push_back(msg);
			return true;
		}
		else
		{
			jogador->setSaldo(jogador->getSaldo() - bet);
			jogador->Lucro -= bet;
			casino->DinheiroRecebido += bet;
			Lucro += bet;
			cout << "O jogador " << jogador->getNome() << " perdeu " << bet << "EUR na roleta.\n";
			string msg = "O jogador perdeu " + to_string(bet) + "EUR na roleta.\n";
			jogador->historico->push_back(msg);
			return false;
		}
	}
}

bool Maquina::Slot(int bet, Casino* casino)
{
	double resultado = Util::RandNumDouble(0, 1);
	if (resultado <= 0.000001)// 0.0001%! :O   (10000, 1000000)xAposta
	{
		int multiplicador = Util::RandNumInt(10000, 1000000);
		AtualizarDadosAposAposta(bet, true, casino, multiplicador, "MEGA JACKPOT!!!");
		return true;
	}
	if (resultado <= 0.00005)//0.005%    (1000-3000)xAposta
	{
		int multiplicador2 = Util::RandNumInt(1000, 3000);
		AtualizarDadosAposAposta(bet, true, casino, multiplicador2, "FENOMENAL!");
		return true;
	}
	if (resultado <= 0.001)//0.1%  100xAposta
	{
		AtualizarDadosAposAposta(bet, true, casino, 100, "Vitoria Epica!");
		return true;
	}
	if (resultado <= 0.05)//5%  3xAposta
	{
		AtualizarDadosAposAposta(bet, true, casino, 3, "Triplo.");
		return true;
	}
	if (resultado <= 0.35)  //Probabilidade variada (35% predefinicao)  2xAposta
	{
		AtualizarDadosAposAposta(bet, true, casino,2);
		return true;
	}
	else//65% (normalmente)  jogador perde
	{
		AtualizarDadosAposAposta(bet, false, casino, 0);
		return false;
	}
}

bool Maquina::BlackJack(int bet, Casino* casino)
{
	double probabilidade = Util::RandNumDouble(0, 1);
	if (probabilidade<=0.0475)// 4% de chance de blackjack 2.5x aposta
	{
		jogador->setSaldo(jogador->getSaldo() + (bet*2.5)-bet);
		jogador->Lucro += (bet * 2.5) - bet;
		casino->DinheiroPerdido += bet;
		cout << "BlackJack! O jogador " << jogador->getNome() << " ganhou " << bet * 2.5 << "EUR no blackjack.\n";
		string msg = "BlackJack! O jogador ganhou " + to_string(bet * 2.5) + "EUR no blackjack.\n";
		jogador->historico->push_back(msg);
		return true;
	}
	if (probabilidade <= 0.4222)// 42% chance de o jogar 2x aposta
	{
		jogador->setSaldo(jogador->getSaldo() + bet);
		jogador->Lucro += bet;
		casino->DinheiroPerdido += bet;
		cout << "O jogador " << jogador->getNome() << " ganhou " << bet * 2 << "EUR no blackjack.\n";
		string msg = "O jogador ganhou " + to_string(bet*2) + "EUR no blackjack.\n";
		jogador->historico->push_back(msg);
		return true;
	}
	else //o jogador perde
	{
		jogador->setSaldo(jogador->getSaldo() - bet);
		jogador->Lucro -= bet;
		Lucro += bet;
		casino->DinheiroRecebido += bet;
		cout << "O jogador " << jogador->getNome() << " perdeu " << bet << "EUR no blackjack.\n";
		string msg = "O jogador perdeu " + to_string(bet) + "EUR no blackjack.\n";
		jogador->historico->push_back(msg);
		return false;
	}
}

bool Maquina::JogadorJoga(int bet, Casino* casino)
{
	if (jogador->getSaldo() >0)
	{
		if (tipo == TIPO_MAQUINA::Roleta)
		{
			Utilizacoes++;
			jogador->setTempoAJogar(jogador->getTempoAJogar() + getTempoJogadaMaquina());
			return (Roulette(bet, casino));
		}

		if (tipo == TIPO_MAQUINA::Poker)
		{
			//pa fazer
			jogador->setTempoAJogar(jogador->getTempoAJogar() + getTempoJogadaMaquina());
			Utilizacoes++;
		}

		if (tipo == TIPO_MAQUINA::ClassicSlots)
		{
			Utilizacoes++;
			jogador->setTempoAJogar(jogador->getTempoAJogar() + getTempoJogadaMaquina());
			return Slot(bet, casino);
		}

		if (tipo == TIPO_MAQUINA::BlackJack)
		{
			Utilizacoes++;
			jogador->setTempoAJogar(jogador->getTempoAJogar() + getTempoJogadaMaquina());
			return BlackJack(bet, casino);

		}

		//chance de avariar
		int prob = Util::RandNumInt(1, 10000);
		if (prob == 1) {
			cout << "Maquina " << getID() << " a avariou";
			estado = ESTADO_MAQUINA::AVARIADA;
			Avarias++;
		}
		else {
			//controlo de temperatura
			if (temperatura <= 20)
			{
				temperatura += Util::RandNumInt(0, 3);
			}
			if (temperatura >= 70)
			{
				cout << "Maquina " << getID() << " a sobreaquecer, desligue rapidamente";

				temperatura += Util::RandNumInt(0, 3);
				temperatura -= Util::RandNumInt(0, 2);
				if (temperatura > 85) {
					cout << "Maquina " << getID() << " a avariou";
					estado = ESTADO_MAQUINA::AVARIADA;
					Avarias++;
				}
			}
			else
			{
				temperatura += Util::RandNumInt(0, 3);
				temperatura -= Util::RandNumInt(0, 2);
			}
		}

	}
	else
	{
		cout << "Saldo Insuficiente\n";
		return 0;
	}
}
