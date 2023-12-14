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
    return 7;//CR7 GOAT
}