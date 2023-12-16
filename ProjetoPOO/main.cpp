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
    Casino* solverde = new Casino("solverde",100,"00:00:00","24:00:00");
    solverde->LoadCasino("load.xml");
    solverde->LerFicheiro();



    solverde->Run();

    
    delete(solverde);
    return 7;//CR7 GOAT
}