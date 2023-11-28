#include<iostream>
using namespace std;

#include"Casino.h"
#include "Pessoas.h"

int main()
{
    Casino casino = Casino("solverde",4);
    casino.MostrarMaquinas();
    //casino.LerFicheiro();
    return 0;
}