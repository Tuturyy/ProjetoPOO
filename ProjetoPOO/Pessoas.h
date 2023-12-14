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
public:
	std::list<std::string>* historico;
	int Lucro;
	int Wins;
	int Losses;
	int MaiorGanho;
	Pessoa(int _ID, std::string _Nome, std::string _Localidade, int _Idade);
	virtual ~Pessoa();
	int getID();
	std::string getNome();
	std::string getLocalidade();
	int getIdade();
	int getSaldo();
	void setSaldo(int novoSaldo);
	Maquina* getMaquina();
	int getHoraEntradaCasino();
	void setHoraEntradaCasino(int novaHoraEntradaCasino);
	int getHoraSaidaCasino();
	int getTempoAJogar();
	void setTempoAJogar(int novoTempoNoCasino);
	void SetMaquina(Maquina* novaMaquina);
	void SetHoraSaidaCasino(int novaHora);
	void adicionaSaldo(int novoSaldo);
	void MostrarPessoa();
	void PessoaParaCasino(Casino* Pc) {Ptr_Casino = Pc;}
	void PessoaParaForaCasino() { Ptr_Casino = nullptr;}
	void PessoaParaForaMaquina() { Ptr_Maquina = nullptr;}
	void MostrarHistoricoApostas();
};