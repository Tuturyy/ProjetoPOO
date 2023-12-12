#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include "Pessoas.h"
#include "Casino.h"

Pessoa::Pessoa(int _ID, std::string _Nome, std::string _Localidade, int _Idade)
{
	ID = _ID;
	Nome = _Nome;
	Localidade = _Localidade;
	Idade = _Idade;
	Ptr_Maquina = nullptr;
	Saldo = 0;
	SaldoInicial = 0;
	Lucro = 0;
	VitoriasConsecutivas = 0;
	HoraSaidaCasino = 0;
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

int Pessoa::getSaldo(){
	return Saldo;
}

void Pessoa::setSaldo(int novoSaldo)
{
	Saldo = novoSaldo;
}

Maquina* Pessoa::getMaquina()
{
	return Ptr_Maquina;
}

int Pessoa::getHoraSaidaCasino()
{
	return HoraSaidaCasino;
}

void Pessoa::SetMaquina(Maquina* novaMaquina)
{
	Ptr_Maquina = novaMaquina;
}

void Pessoa::adicionaSaldo(int novoSaldo) {
	Saldo = novoSaldo;
	SaldoInicial = novoSaldo;
}

void Pessoa::MostrarPessoa()
{
	cout << "ID: " << ID << endl;
	cout << "Nome: " << Nome << endl;
	cout << "Local: " << Localidade << endl;
	cout << "Idade: " << Idade << endl;
	cout << "Saldo:" << Saldo << endl;
	cout << "Lucro: " << Lucro << endl;
	cout << "\n";
}