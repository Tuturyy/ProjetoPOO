#include <iostream>
using namespace std;

#include "Casino.h"
#include "Pessoas.h"



int main()
{
    srand(time(NULL));
    int i = 0;
    Casino casino = Casino("solverde",4);
    //casino.LerFicheiro();
    //casino.AddPessoa();
    //casino.MostrarPessoasCasino();
    casino.MostrarMaquinas();

    return 0;
}