#include <iostream>
using namespace std;

#include "Casino.h"
#include "Pessoas.h"
#include "menu.h"
#include "Uteis.h"


int main()
{
   

    //menuGeral();
    srand(time(NULL));
    Casino* solverde = new Casino("solverde", 4);
    solverde->LerFicheiro();
    Pessoa* pessoa = solverde->GetPessoa();
    solverde->AddPessoa(pessoa);
    
    //casino.MostrarMaquinas();
    //casino.MostrarPessoasCasino();
    //casino.MostrarMaquinas();

    Maquina maq = Maquina::Maquina(77, TIPO_MAQUINA::ClassicSlots, 9, 9);
    maq.AddJogadorMaquina(pessoa);

    cout << "saldo inic=" << pessoa->Saldo << "\n";
    for (int i=0;i<50;i++)
    {
        if(pessoa->Saldo > 0)
        {
            int randombet = Util::RandNumInt(1, pessoa->Saldo);
            maq.JogadorJoga(randombet,solverde);
        }
    }
    cout << "Recebido = " << solverde->DinheiroRecebido << endl<<"Perdido = "<< solverde->DinheiroPerdido <<endl << "Saldo=" << pessoa->Saldo;

    return 7;//CR7 GOAT
}