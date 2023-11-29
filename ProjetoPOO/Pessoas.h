#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include"Uteis.h"

class Casino;

class Pessoa {
	int ID;
	std::string Nome;
	std::string Localidade;
	int Idade;
	Casino* Ptr_Casino;

public:
	int Saldo;
	Pessoa(int _ID, std::string _Nome, std::string _Localidade, int _Idade);
	virtual ~Pessoa();
	int getID();
	std::string getNome();
	std::string getLocalidade();
	int getIdade();
	int getSaldo();
	void adicionaSaldo(int novoSaldo);
	void MostrarPessoa();
	void PessoaParaCasino(Casino* Pc) {Ptr_Casino = Pc;}
};