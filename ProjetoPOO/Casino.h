#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
using namespace std;

#include "Maquinas.h"
#include "Pessoas.h"

class Casino
{
	string nomeC;
	list<Maquina*> LM;
	list<Pessoa*> LP;
	list<Pessoa*> LPT;
public:
	Casino(string nome, int numMaquinas);
	virtual ~Casino();
	void LerFicheiro();
	bool AddPessoa(Pessoa* pessoa);
	bool AddMaquina(Maquina* m);
	Maquina* PesquisarMaquinaID(int id_maq);
	void MostrarMaquinas();
	void Listar(ostream& f = std::cout);
	void Desligar(int id_maq);
	ESTADO_MAQUINA Get_Estado(int id_maq);
	int Memoria_Total();
	list<Maquina*>* GerarMaquinas(int numMaquinas);
	list<Maquina*>* Listar_Tipo(string Tipo, ostream& f = std::cout);
	list<string>* Ranking_Dos_Fracos();
	list<Maquina*>* Ranking_Das_Mais_Trabalhadores();
	//list<User*>* Jogadores_Mais_Frequentes();
	//list<User*>* Jogadores_Mais_Ganhos();
	void Relatorio(string fich_xml);
	void SubirProbabilidadeVizinhas(Maquina* M_ganhou, float R, list<Maquina*>& lmvizinhas);
	void Listar(float X, ostream& f = std::cout);
	void Run(bool Debug = true);
};