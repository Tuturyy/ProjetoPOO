#include <iostream>
using namespace std;

#include "Casino.h"
#include "Pessoas.h"
#include "menu.h"
#include "Uteis.h"
#include "relogio.h"


int main()
{
    //menuGeral();
    srand(time(NULL));
    Casino* solverde = new Casino("solverde",40);
    solverde->LerFicheiro();
    /*Pessoa* pessoa = solverde->GetPessoa();
    Pessoa* pessoa2 = solverde->GetPessoa();
    Pessoa* pessoa3 = solverde->GetPessoa();
    solverde->AddPessoa(pessoa);
    solverde->AddPessoa(pessoa2);
    solverde->AddPessoa(pessoa3);

    //casino.MostrarMaquinas();
    //casino.MostrarPessoasCasino();
    //casino.MostrarMaquinas();

    Maquina maq = Maquina::Maquina(77, TIPO_MAQUINA::BlackJack, 9, 9);
    Maquina maq2 = Maquina::Maquina(9, TIPO_MAQUINA::ClassicSlots, 19, 9);
    Maquina maq3 = Maquina::Maquina(10, TIPO_MAQUINA::Roleta, 0, 9);
    maq.AddJogadorMaquina(pessoa);
    maq2.AddJogadorMaquina(pessoa2);
    maq3.AddJogadorMaquina(pessoa3);

    for (int i = 0; i < 5; i++)
    {
        maq.JogadorJoga(maq.CalcularBet(), solverde);
        maq2.JogadorJoga(maq2.CalcularBet(), solverde);
        maq3.JogadorJoga(maq3.CalcularBet(), solverde);
    }

    cout << "\n\n";
    solverde->MostrarListaPessoas(solverde->Jogadores_Mais_Ganhos());
    cout << "\n\n";
    solverde->Listar(40);
    cout << "\n";
    //solverde->MostrarListaMaquinas(solverde->Ranking_Das_Mais_Trabalhadores());
    maq.MostrarMaquina();*/

    //solverde->MostrarMaquinas();
    //solverde->Relatorio("relatorio.txt");
    
    solverde->Run();

    solverde->MostrarListaPessoas(solverde->Jogadores_Mais_Ganhos());
    cout << "Dinheiro Recebido= " << solverde->DinheiroRecebido;
    cout << "Dinheiro Perdido= " << solverde->DinheiroPerdido;
    cout << "\n\nLucro= " << solverde->DinheiroRecebido - solverde->DinheiroPerdido;

    //cout <<"\n\nMemoria Ocupada: " << solverde->Memoria_Total();
    return 7;//CR7 GOAT
}