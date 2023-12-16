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
#define PESSOAS_MAX_CASINO 50

class Casino
{
	string nomeC;
	int HoraEncerrar;
	int TempoAtualCasino;
	list<Maquina*> LM;
	list<Maquina*> LMvizinhas;
	list<Pessoa*> LP;
	list<Pessoa*> LPT;
	list<Pessoa*> LPJ;
	int numeroMaquinas;
	string horarioAbertura;
	string horarioFecho;
	int Jogadas;
public:

	//Variaveis
	int DinheiroRecebido;
	int DinheiroPerdido;

	//Construtor e destrutor
	Casino(string nome, int numMaquinas, string horarioAbertura, string horarioFecho);
	virtual ~Casino();

	//Funções de Pessoas
	void LerFicheiro();
	void MostrarListaPessoas(list<Pessoa*> lista);
	void MostrarPessoasFora();
	void MostrarPessoasCasino();
	Pessoa* GetPessoa();
	Pessoa* PesquisarPessoaID(int id_pessoa);
	void AddPessoa(Pessoa *pessoa);
	void RmvPessoa(Pessoa* pessoa);
	list<Pessoa*> Jogadores_Mais_Ganhos();
	list<Pessoa*> getListaJogadores();
	list<Pessoa*> getListaPessoasCasino();
	list<Pessoa*> Jogadores_Mais_Frequentes();
	list<Maquina*> getListaLMvizinhas();
	int getJogadas();
	void setJogadas(int novoJogadas);


	//Funções de Maquinas
	bool AddMaquina(Maquina* m);
	Maquina* PesquisarMaquinaID(int id_maq);
	void MostrarMaquinas();
	void MostrarListaMaquinas(list<Maquina*> lista);
	void Desligar(int id_maq);
	ESTADO_MAQUINA Get_Estado(int id_maq);
	void AtribuirMaquinaPessoa(Pessoa* pessoa);
	void GerarMaquinas(int numMaquinas);
	Maquina* MaisPrejuizo();
	list<Maquina*> Listar_TipoMaquina(string Tipo, ostream& f = std::cout);
	list<Maquina*> Maquinas_Mais_Avarias();
	list<Maquina*> Ranking_Das_Mais_Trabalhadores();
	void SubirProbabilidadeVizinhas(Maquina* M_ganhou, float R, list<Maquina*>& lmvizinhas);
	float CalcularDistanciaEntreMaquinas(Maquina* M1, Maquina* M2);
	void ListarMaquinasProbabilidadeMaiorQueX(float X, ostream& f = std::cout);
	

	//Programa
	int Memoria_Total();
	void ListarEstadoCasino(ostream& f = std::cout);
	void Relatorio(string fich_xml);
	void EstatisticasCasino();
	void PessoasVaoParaMaquinas();
	void PessoasJogam();
	void ControlarGanhosMaquinas();
	void VerificarSaidaPessoas();
	void Run(bool Debug = true);

	bool LoadCasino(const std::string& fileName);
	int getNumeroMaquinas() const;
	string getHorarioAbertura() const;
	string getHorarioFecho() const;
};