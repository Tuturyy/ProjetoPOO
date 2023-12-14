#pragma once
#include <iostream>
#include "Maquinas.h"
#include "Pessoas.h"
#include <conio.h>
#include "Uteis.h"
#include "Relogio.h"

using namespace std;

void menu();
void subMenuMaquinas(Casino* casino);
void subMenuJogadores(Casino* casino);
void subMenuCasino(Casino* casino);
void menuGeral(Relogio& relogio, Casino* casino);