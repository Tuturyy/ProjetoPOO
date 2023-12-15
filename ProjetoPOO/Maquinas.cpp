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
	AvisoTemperatura = false;
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

string Maquina::EstadoMaquinaString()
{
	if (estado==ESTADO_MAQUINA::OFF)
	{
		return "Maquina [" + to_string(id) + "] esta OFF.\n";
	}

	if (estado == ESTADO_MAQUINA::ON)
	{
		return "Maquina [" + to_string(id) + "] esta ON.\n";
	}

	if (estado == ESTADO_MAQUINA::AVARIADA)
	{
		return "Maquina [" + to_string(id) + "] esta AVARIADA.\nDesligue a maquina para consertar.";
	}
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
	cout << "Temperatura: " << temperatura << endl;
	cout << "Utilizacoes: " << Utilizacoes << endl;
	cout << "Lucro: " << Lucro << endl;
}

void Maquina::DesligarMaquina()
{
	estado = ESTADO_MAQUINA::OFF;
	temperatura = 20;
	AvisoTemperatura = false;
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
		if (estado != ESTADO_MAQUINA::AVARIADA)
		{
			estado = ESTADO_MAQUINA::OFF;
		}
		return;
	}
	else
		cout << "Impossivel remover jogador da Maquina (" << id << "). Nao existe jogador.\n";
}

int Maquina::MemoriaClass()
{
	int TamanhoTotal = sizeof(*this);
	//TamanhoTotal += jogador->MemoriadaClass();

	return TamanhoTotal;
}

void Maquina::AumentarProbabilidade()
{
	if (getPorcentWin() >= 39) //Limite Maximo probabilidade de vencer
	{
		cout << "Probabilidade muito alta. Impossivel aumentar";
		return;
	}
	else
	{
		setPorcentWin(getPorcentWin() + 1);
		return;
	}
}

void Maquina::DiminuirProbabilidade()
{
	if (getPorcentWin() <= 28) //Limite Minimo probabilidade de vencer
	{
		cout << "Probabilidade muito baixa. Impossivel diminuir";
		return;
	}
	else
	{
		setPorcentWin(getPorcentWin() - 1);
		return;
	}
}

void Maquina::MaquinaAvaria(bool forcarAvaria=false)
{
	int probabilidade = Util::RandNumInt(1, 1000);
	if (forcarAvaria || probabilidade == 1)
	{
		cout << "MAQUINA [" << id << "] AVARIOU.\n";
		Avarias++;
		estado = ESTADO_MAQUINA::AVARIADA;
	}
}

void Maquina::SobeTemperatura()
{
	if(estado == ESTADO_MAQUINA::ON)
	{

		if (temperatura >= 85)
		{
			cout << "Maquina [" << getID() << "] sobreaqueceu!\n";
			MaquinaAvaria(true);
			return;
		}

		if (temperatura >= 70)
		{
			temperatura += 1;
			if (AvisoTemperatura == false)
			{
				cout << "Aviso! Maquina [" << getID() << "] a sobreaquecer, desligue rapidamente\n";
				AvisoTemperatura = true;
			}
			return;
		}

		else
		{
			temperatura += 1;
		}
	}
}

void Maquina::AtualizarDadosAposAposta(int bet, bool ganhou, Casino* casino,  int multiplicadorBet , string MensagemEspecial = "")
{
	if (ganhou)
	{
		jogador->setSaldo(jogador->getSaldo() + (bet*multiplicadorBet)-bet);
		jogador->setLucro(jogador->getLucro() + ((bet * multiplicadorBet) - bet));
		jogador->setWins(jogador->getWins()+1);
		if (jogador->getMaiorGanho() < (bet * multiplicadorBet))
		{
			jogador->setMaiorGanho(bet * multiplicadorBet);
		}
		Lucro -= ((bet * multiplicadorBet) - bet);
		casino->DinheiroPerdido += ((bet * multiplicadorBet) - bet);
		string msg = MensagemEspecial + " O jogador ganhou " + to_string(bet*multiplicadorBet) + "EUR("+ to_string(multiplicadorBet)+"x) em " + TipoMaquinaString() + ".\n";
		jogador->historico->push_back(msg);
	}
	else
	{
		jogador->setSaldo(jogador->getSaldo() - bet);
		jogador->setLucro(jogador->getLucro() - bet);
		jogador->setLosses(jogador->getLosses() + 1);
		Lucro += bet;
		casino->DinheiroRecebido += bet;
		string msg = " O jogador perdeu " + to_string(bet) + "EUR em " + TipoMaquinaString() + ".\n";
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
			int apostaPoker = 0;
			double porcentagemSaldo = 0;
			double probabilidade = Util::RandNumDouble(0, 1);
			if (probabilidade <= 0.95)// 95% de chances de o jogador apostar 5 a 15% do seu saldo
			{
				porcentagemSaldo = Util::RandNumDouble(0.05, 0.15);
				apostaPoker = jogador->getSaldo() * porcentagemSaldo;
				if (apostaPoker < 1) {
					apostaPoker = 1; // valor minimo da aposta e 1
				}
				return apostaPoker;
			}
			else {
				porcentagemSaldo = Util::RandNumDouble(0.7, 1);// 5% de apostar 70 a 100% do saldo
				apostaPoker = jogador->getSaldo() * porcentagemSaldo;
				if (apostaPoker < 1) {
					apostaPoker = 1; // valor minimo da aposta e 1
				}
				return apostaPoker;
			}
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
			AtualizarDadosAposAposta(bet, true, casino, 2);
			return true;
		}
		else //jogador perde
		{
			AtualizarDadosAposAposta(bet, false, casino, 0);
			return false;
		}
	}
	else //o jogador aposta no verde
	{
		if (resultado <= (1.0 / 37))
		{
			AtualizarDadosAposAposta(bet, true, casino, 14, "Verde!");
			return true;
		}
		else
		{
			AtualizarDadosAposAposta(bet, false, casino, 0);
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
	if (resultado <= (getPorcentWin()/100))  //Probabilidade variada (35% predefinicao)  2xAposta
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
	if (probabilidade<=0.0475)// 4% de chance de blackjack 3x aposta
	{
		AtualizarDadosAposAposta(bet, true, casino, 3, "BlackJack!");
		return true;
	}
	if (probabilidade <= 0.4222)// 42% chance de o jogar 2x aposta
	{
		AtualizarDadosAposAposta(bet, true, casino, 2);
		return true;
	}
	else //o jogador perde
	{
		AtualizarDadosAposAposta(bet, false, casino,0);
		return false;
	}
}

bool Maquina::Poker(int bet, Casino* casino)
{
	double probabilidade = Util::RandNumDouble(0, 1);
	if (probabilidade <= (1.0/221))  // 1/221 e a probilidade de sair 2 ases (~0.45%) 30xAposta
	{
		AtualizarDadosAposAposta(bet, true, casino, 30, "Dois Ases!");
		return true;
	}
	if (probabilidade <= (getPorcentWin() / 100)) //Probabilidade variavel (30% predefinicao) 2xAposta
	{
		AtualizarDadosAposAposta(bet, true, casino, 2);
		return true;
	}
	else
	{
		AtualizarDadosAposAposta(bet, false, casino, 0);
		return false;
	}
}

bool Maquina::JogadorJoga(int bet, Casino* casino)
{
	if(estado==ESTADO_MAQUINA::ON)
	{
		MaquinaAvaria();
		SobeTemperatura();
	}
	 if (jogador->getSaldo() > 0 && estado == ESTADO_MAQUINA::ON)
	{
		if (tipo == TIPO_MAQUINA::Roleta)
		{
			Utilizacoes++;
			casino->setJogadas(casino->getJogadas() + 1);
			jogador->setTempoAJogar(jogador->getTempoAJogar() + getTempoJogadaMaquina());
			return (Roulette(bet, casino));
		}

		if (tipo == TIPO_MAQUINA::Poker)
		{
			Utilizacoes++;
			casino->setJogadas(casino->getJogadas() + 1);
			jogador->setTempoAJogar(jogador->getTempoAJogar() + getTempoJogadaMaquina());
			return (Poker(bet, casino));
		}

		if (tipo == TIPO_MAQUINA::ClassicSlots)
		{
			Utilizacoes++;
			casino->setJogadas(casino->getJogadas() + 1);
			jogador->setTempoAJogar(jogador->getTempoAJogar() + getTempoJogadaMaquina());
			return Slot(bet, casino);
		}

		if (tipo == TIPO_MAQUINA::BlackJack)
		{
			Utilizacoes++;
			casino->setJogadas(casino->getJogadas() + 1);
			jogador->setTempoAJogar(jogador->getTempoAJogar() + getTempoJogadaMaquina());
			return BlackJack(bet, casino);

		}
		return false;
	}
}
