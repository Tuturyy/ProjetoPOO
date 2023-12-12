#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include"Pessoas.h"

using namespace std;

#define WIN_PORC_POKER 40
#define WIN_PORC_BLACKJACK 42.22
#define WIN_PORC_ROLETA (18.0/37)
#define WIN_PORC_SLOT 35

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
	int temperat;
	TIPO_MAQUINA tipo;
	int x, y;
	ESTADO_MAQUINA estado;
public:

	//Variaveis
	float porcentWin;
	int Lucro;
	int Utilizacoes;

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


	//Importantes
	void MostrarMaquina();
	void DesligarMaquina();
	void AddJogadorMaquina(Pessoa* player);
	

	//Jogos
	int CalcularBet(); //calcular a aposta dos jogadores
	bool Roulette(int bet, Casino* casino);
	bool Slot(int bet, Casino* casino);
	bool BlackJack(int bet, Casino* casino);

	bool JogadorJoga(int bet, Casino* casino);
};