#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include"Pessoas.h"

using namespace std;

#define WIN_PORC_POKER 40 //em %
#define WIN_PORC_BLACKJACK 42.22
#define WIN_PORC_ROLETA ((18.0/37) *100)
#define WIN_PORC_SLOT 35

#define	TEMPO_JOGADA_POKER 300 //em segundos
#define	TEMPO_JOGADA_BLACKJACK 120
#define	TEMPO_JOGADA_ROLETA 60
#define	TEMPO_JOGADA_SLOT 10

class Casino;

enum class ESTADO_MAQUINA {
	OFF, ON, AVARIADA
};

enum class TIPO_MAQUINA {
	Poker =1, BlackJack, ClassicSlots, Roleta
};

class Maquina
{
	Pessoa* jogador;
	int id;
	int temperatura;
	TIPO_MAQUINA tipo;
	int x, y;
	ESTADO_MAQUINA estado;
	double porcentWin;
	int TempoCadaJogada;
public:

	//Variaveis
	int Lucro;
	int Utilizacoes;
	int Avarias;
	int TempoJogadaTerminada;

	//Construtor e destrutor
	Maquina(int _id, TIPO_MAQUINA _tipo, int _x, int _y);
	virtual ~Maquina();

	//Obter informacao
	int getID();
	int getX();
	int getY();
	ESTADO_MAQUINA getEstado();
	TIPO_MAQUINA getTipo();
	Pessoa* getJogador();
	string TipoMaquinaString(); // transformar TIPO_MAQUINA em string
	int getTempoJogadaMaquina();
	double getPorcentWin();
	int getTempoCadaJogada();
	void setPorcentWin(double novaPorcentW);


	//Importantes
	void MostrarMaquina();
	void DesligarMaquina(); //Desliga e arrefece maquina.retira o jogador da maquina
	void AddJogadorMaquina(Pessoa* player);
	void RemoverJogadorMaquina();
	

	//Jogos
	bool Roulette(int bet, Casino* casino);
	bool Slot(int bet, Casino* casino);
	bool BlackJack(int bet, Casino* casino);

	void AtualizarDadosAposAposta(int bet, bool ganhou, Casino* casino, int multiplicadorBet, string MensagemEspecial);
	int CalcularBet(); //calcular a aposta dos jogadores
	bool JogadorJoga(int bet, Casino* casino);
};