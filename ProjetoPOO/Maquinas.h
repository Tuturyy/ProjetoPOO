#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<list>
using namespace std;

class Casino;

enum class ESTADO_MAQUINA {
	OFF, ON, AVARIADA
};

class Maquina
{
	int id;
	int temperat;
	int tipo;
	ESTADO_MAQUINA estado;
public:
	Maquina(int _id, int _tipo);
	virtual ~Maquina();
	int getID();
	ESTADO_MAQUINA getEstado();
	void MostrarMaquina();
	void DesligarMaquina();
};