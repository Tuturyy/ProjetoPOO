#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include "Maquinas.h"
#include "Pessoas.h"

using namespace std;



#define X_MAX_CASINO 50
#define Y_MAX_CASINO 50

class Casino
{
	string nomeC;
	list<Maquina*> LM;
	list<Pessoa*> LP;

	list<Pessoa*> LPT;

	list<Pessoa*> LPJ;
public:

	//Variaveis
	int DinheiroRecebido;
	int DinheiroPerdido;
	int TempoAtualCasino;

	//Construtor e destrutor
	Casino(string nome, int numMaquinas);
	virtual ~Casino();

	//Fun��es de Pessoas
	void LerFicheiro();
	void MostrarListaPessoas(list<Pessoa*> lista);
	void MostrarPessoasFora();
	void MostrarPessoasCasino();
	Pessoa* GetPessoa();
	void AddPessoa(Pessoa *pessoa);
	void RmvPessoa(Pessoa* pessoa);

	//Fun��es de Maquinas
	bool AddMaquina(Maquina* m);
	Maquina* PesquisarMaquinaID(int id_maq);
	void MostrarMaquinas();
	void MostrarListaMaquinas(list<Maquina*> lista);
	void Listar(ostream& f = std::cout);
	void Desligar(int id_maq);
	ESTADO_MAQUINA Get_Estado(int id_maq);
	int Memoria_Total();
	list<Maquina*>* GerarMaquinas(int numMaquinas);
	list<Maquina*> Listar_Tipo(string Tipo, ostream& f = std::cout);
	list<string>* Ranking_Dos_Fracos();
	list<Maquina*> Ranking_Das_Mais_Trabalhadores();
	//list<User*>* Jogadores_Mais_Frequentes();
	list<Pessoa*> Jogadores_Mais_Ganhos();
	void Relatorio(string fich_xml);
	void SubirProbabilidadeVizinhas(Maquina* M_ganhou, float R, list<Maquina*>& lmvizinhas);
	void Listar(float X, ostream& f = std::cout);
	void Run(bool Debug = true);
};