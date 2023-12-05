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
    Casino* solverde = new Casino("solverde", 4);
    /*solverde->LerFicheiro();
    Pessoa* pessoa = solverde->GetPessoa();
    solverde->AddPessoa(pessoa); 
    
    //casino.MostrarMaquinas();
    //casino.MostrarPessoasCasino();
    //casino.MostrarMaquinas();

    Maquina maq = Maquina::Maquina(77, TIPO_MAQUINA::BlackJack, 9, 9);
    maq.AddJogadorMaquina(pessoa);

    cout << "saldo inic=" << pessoa->Saldo << "\n";
    for (int i=0;i<5;i++)
    { 
        if(pessoa->Saldo > 0)
        {
            
            if (maq.JogadorJoga(maq.CalcularBet(), solverde))
                maq.getJogador()->VitoriasConsecutivas++;
            else
                maq.getJogador()->VitoriasConsecutivas = 0;
        }
    }
    cout << "Recebido Casino = " << solverde->DinheiroRecebido << endl<<"Perdido Casino = "<< solverde->DinheiroPerdido << endl << "Lucro Casino = " << solverde->DinheiroRecebido - solverde->DinheiroPerdido << endl << "Saldo Final = " << pessoa->Saldo;
    cout << "\n\n Vitorias consec: " << maq.getJogador()->VitoriasConsecutivas;
    cout << "\n\nHistorico:\n";
    for (const auto& str : maq.getJogador()->historico)
    {
        cout << str;
    }*/

    solverde->Run();

    return 7;//CR7 GOAT
}