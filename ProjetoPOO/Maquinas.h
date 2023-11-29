#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include"Pessoas.h"
using namespace std;

class Casino;

enum class ESTADO_MAQUINA {
	OFF, ON, AVARIADA
};

class Maquina
{
	Pessoa* jogador;
	int id;
	int temperat;
	int tipo;
	int x, y;
	ESTADO_MAQUINA estado;
public:
	float porcentWin;
	Maquina(int _id, int _tipo, int _x, int _y);
	virtual ~Maquina();
	int getID();
	int getX();
	int getY();
	ESTADO_MAQUINA getEstado();
	void MostrarMaquina();
	void DesligarMaquina();
	void AddJogadorMaquina(Pessoa* player);
};