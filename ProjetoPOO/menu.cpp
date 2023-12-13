#include <iostream>
#include "menu.h"
#include "Casino.h"
#include "Pessoas.h"
#include <conio.h>

using namespace std;

void menu() {
	cout << "MENU GESTAO DO CASINO" << endl;
	cout << "\n1 - Maquinas" << endl;
	cout << "\n2 - Jogadores" << endl;
	cout << "\n3 - Casino" << endl;
	cout << "\n0 - Sair" << endl;
}

void subMenuMaquinas() {
	cout << "\n1 - Ligar Maquina" << endl;
	cout << "\n2 - Desligar Maquina" << endl;
	cout << "\n3 - Ver estado da maquina" << endl;
	cout << "\n4 - Listar as maquinas com a probabilidade de ganhar superior a..." << endl;
	cout << "\n5 - Maquinas mais usadas" << endl;
	cout << "\n6 - Maquinas que mais avariam" << endl;
	cout << "\n7 - Listar maquinas de um dado jogo" << endl;
	cout << "\n0 - Voltar atras" << endl;

    int opcao;

    do
    {
        cout << "Escolhe uma opcao:" << endl;
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (opcao != 0);
}

void subMenuJogadores() {
	cout << "\n1 - Jogadores que mais ganharam no casino" << endl;
	cout << "\n2 - Jogadores que mais tempo passaram no casino" << endl;
	cout << "\n0 - Voltar atras" << endl;

    int opcao;

    do
    {
        cout << "Escolhe uma opcao:" << endl;
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            break;
        case 2:
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (opcao != 0);
}

void subMenuCasino() {
	cout << "\n1 - Listar estado do casino" << endl;
	cout << "\n2 - Listar estado do casino XML" << endl;
	cout << "\n3 - Configuracoes do casino" << endl;
	cout << "\n0 - Voltar atras" << endl;

    int opcao;

    do
    {
        cout << "Escolhe uma opcao:" << endl;
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (opcao != 0);
}

void menuGeral(Relogio& relogio) {
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do {
        menu();
        cout << "Escolhe uma opcao:" << endl;
        cin >> opcao;

        switch (opcao) {
        case 1:
            subMenuMaquinas();
            break;
        case 2:
            subMenuJogadores();
            break;
        case 3:
            subMenuCasino();
            break;
        case 0:
            relogio.RetomarRelogio();
            break;
        default:
            cout << "\nOpcao invalida! Escolha outra opcao.";
            break;
        }
    } while (opcao != 0);
}