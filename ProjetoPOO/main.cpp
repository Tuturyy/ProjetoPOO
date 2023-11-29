#include <iostream>
using namespace std;

#include "Casino.h"
#include "Pessoas.h"
#include "menu.h"
#include "Uteis.h"


int main()
{
    menuGeral();
    srand(time(NULL));
    Casino casino = Casino("solverde",4);
    casino.LerFicheiro();
    Pessoa* pessoa = casino.GetPessoa();
    casino.AddPessoa(pessoa);
    casino.MostrarPessoasCasino();
    casino.MostrarMaquinas();

    return 0;
}