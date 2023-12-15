#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include"Uteis.h"

class Casino;
class Maquina;

class Pessoa {
	int ID;
	std::string Nome;
	std::string Localidade;
	int Idade;
	Casino* Ptr_Casino;
	Maquina* Ptr_Maquina;
	int Saldo;
	int SaldoInicial;
	int HoraEntradaCasino;
	int HoraSaidaCasino;
	int TempoAJogar;
	int Lucro;
	int Wins;
	int Losses;
	int MaiorGanho;
public:

	//Criador/Destrutor
	Pessoa(int _ID, std::string _Nome, std::string _Localidade, int _Idade);
	virtual ~Pessoa();

	//Dados estatisticos
	std::list<std::string>* historico;
	

	//Get
	int getID();
	std::string getNome();
	std::string getLocalidade();
	int getIdade();
	int getSaldo();
	Maquina* getMaquina();
	int getHoraEntradaCasino();
	int getHoraSaidaCasino();
	int getTempoAJogar();
	int getLucro();
	int getWins();
	int getLosses();
	int getMaiorGanho();

	//Set
	void setSaldo(int novoSaldo);
	void setHoraEntradaCasino(int novaHoraEntradaCasino);
	void setTempoAJogar(int novoTempoNoCasino);
	void SetMaquina(Maquina* novaMaquina);
	void SetHoraSaidaCasino(int novaHora);
	void setLucro(int novoLucro);
	void setWins(int novoWins);
	void setLosses(int novoLosses);
	void setMaiorGanho(int novoMaiorGanho);
	
	//Importantes
	void adicionaSaldo(int novoSaldo);
	void MostrarPessoa();
	void PessoaParaCasino(Casino* Pc) {Ptr_Casino = Pc;}
	void PessoaParaForaCasino() { Ptr_Casino = nullptr;}
	void PessoaParaForaMaquina() { Ptr_Maquina = nullptr;}
	void MostrarHistoricoApostas();
	int MemoriadaClass();
};