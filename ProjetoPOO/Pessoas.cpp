#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include "Pessoas.h"
#include"Casino.h"

Pessoa::Pessoa(int _ID, std::string _Nome, std::string _Localidade, int _Idade)
{
	ID = _ID;
	Nome = _Nome;
	Localidade = _Localidade;
	Idade = _Idade;
	Ptr_Casino = nullptr;
}

Pessoa::~Pessoa()
{

}

int Pessoa::getID() {
	return ID;
}

std::string Pessoa::getNome() {
	return Nome;
}

std::string Pessoa::getLocalidade() {
	return Localidade;
}

int Pessoa::getIdade() {
	return Idade;
}

void Pessoa::MostrarPessoa()
{
	cout << "\tNome: " << Nome << endl;
	cout << "\tID: " << ID << endl;
	cout << "\tLocal: " << Localidade << endl;
	cout << "\tIdade: " << Idade << endl;
}