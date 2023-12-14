#include <iostream>

#include <iomanip>
using namespace std;

#include "Casino.h"
#include "Pessoas.h"
#include "menu.h"
#include "Uteis.h"
#include "relogio.h"


int main()
{
    srand(time(NULL));
    Casino* solverde = new Casino("solverde",40);
    solverde->LerFicheiro();
    solverde->Run();
    solverde->MostrarListaPessoas(solverde->Jogadores_Mais_Ganhos());
    solverde->MostrarListaMaquinas(solverde->Ranking_Das_Mais_Trabalhadores());
    cout << "Dinheiro Recebido= " << solverde->DinheiroRecebido << "\n";
    cout << "Dinheiro Perdido= " << solverde->DinheiroPerdido<< "\n";
    cout << "\n\nLucro= " << solverde->DinheiroRecebido - solverde->DinheiroPerdido;
    cout << "\n\n";

    list<Pessoa*> MaisGanhos = solverde->Jogadores_Mais_Ganhos();
    auto it = MaisGanhos.begin();
    Pessoa* ballin = (*it);

    for (auto it = ballin->historico->begin(); it != ballin->historico->end(); it++)
    {
        cout << (*it) << "\n";
    }


    //cout <<"\n\nMemoria Ocupada: " << solverde->Memoria_Total();
    return 7;//CR7 GOAT
}