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
    Casino casino = Casino("solverde",4);
    casino.LerFicheiro();
    Pessoa* pessoa = casino.GetPessoa();
    casino.AddPessoa(pessoa);
    
    //casino.MostrarMaquinas();
    //casino.MostrarPessoasCasino();
    //casino.MostrarMaquinas();

    Maquina maq = Maquina::Maquina(77, TIPO_MAQUINA::Roleta, 9, 9);
    maq.AddJogadorMaquina(pessoa);
    for (int i=0;i<300;i++)
    {
        maq.JogadorJoga(5);
    }

    return 7;//CR7 GOAT
}