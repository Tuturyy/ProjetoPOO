#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include"Pessoas.h"

using namespace std;

#define WIN_PORC_POKER 10.0
#define WIN_PORC_BLACKJACK 20.0
#define WIN_PORC_ROLETA 48.0
#define WIN_PORC_SLOT 8.0

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
	float porcentWin;
	Maquina(int _id, TIPO_MAQUINA _tipo, int _x, int _y);
	virtual ~Maquina();
	int getID();
	int getX();
	int getY();
	ESTADO_MAQUINA getEstado();
	void MostrarMaquina();
	void DesligarMaquina();
	void AddJogadorMaquina(Pessoa* player);
	bool JogadorJoga(int bet);
};