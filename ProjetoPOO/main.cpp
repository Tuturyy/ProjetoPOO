#include <iostream>
using namespace std;

#include "Casino.h"
#include "Pessoas.h"



int main()
{
    int i = 0;
    Casino casino = Casino("solverde",4);
    casino.LerFicheiro();
    casino.AddPessoa();
    casino.AddPessoa();
    casino.AddPessoa();
    casino.AddPessoa();
    casino.MostrarPessoasCasino();

    return 0;
}