#include<iostream>
using namespace std;

#include"Casino.h"
#include "Pessoas.h"

int main()
{
    Casino casino = Casino("solverde");
    casino.LerFicheiro();
    return 0;
}