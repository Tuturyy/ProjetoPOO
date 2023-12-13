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

void subMenu1() {
	cout << "\n1 - Ligar Maquina" << endl;
	cout << "\n2 - Desligar Maquina" << endl;
	cout << "\n3 - Ver estado da maquina" << endl;
	cout << "\n4 - Listar as maquinas com a probabilidade de ganhar superior a..." << endl;
	cout << "\n5 - Maquinas mais usadas" << endl;
	cout << "\n6 - Maquinas que mais avariam" << endl;
	cout << "\n7 - Listar maquinas de um dado jogo" << endl;
	cout << "\n0 - Voltar atras" << endl;
}

void subMenu2() {
	cout << "\n1 - Jogadores que mais ganharam no casino" << endl;
	cout << "\n2 - Jogadores que mais tempo passaram no casino" << endl;
	cout << "\n0 - Voltar atras" << endl;
}

void subMenu3() {
	cout << "\n1 - Listar estado do casino" << endl;
	cout << "\n2 - Listar estado do casino XML" << endl;
	cout << "\n3 - Configuracoes do casino" << endl;
	cout << "\n0 - Voltar atras" << endl;
}

/*void menuGeral(Relogio& relogio) {
    setlocale(LC_ALL, "Portuguese");
    char tecla;
    int opcao;
    bool pausadoAntes = false;
    time_t horaInicioPausa = 0;
    time_t tempoPausado = 0;

    do {
        pausadoAntes = relogio.EstaPausado();
        if (!pausadoAntes) {
            relogio.MudarVelocidadeRelogio(0);
            horaInicioPausa = relogio.VerTimeRelogio();
        }
        relogio.MudarVelocidadeRelogio(0);
        menu();
        cout << "Escolhe uma opcao:" << endl;
        cin >> opcao;

        switch (opcao) {
        case 1:
            do {
                subMenu1();
                cout << "\nDigite uma opcao: " << endl;
                cin >> opcao;
                switch (opcao) {
                case 1:
                    break;
                default:
                    break;
                }
            } while (opcao != 0);
            break;
        case 2:
            do {
                subMenu2();
                cout << "\nDigite uma opcao: " << endl;
                cin >> opcao;
                switch (opcao) {
                case 1:
                    break;
                default:
                    break;
                }
            } while (opcao != 0);
            break;
        case 3:
            do {
                subMenu3();
                cout << "\nDigite uma opcao: " << endl;
                cin >> opcao;
                switch (opcao) {
                case 1:
                    break;
                default:
                    break;
                }
            } while (opcao != 0);
            break;
        case 0:
            if (pausadoAntes) {
                tempoPausado = difftime(relogio.VerTimeRelogio(), horaInicioPausa);
                relogio.MudarVelocidadeRelogio(360);
                if (!relogio.EstaPausado()) {
                    relogio.AjustarTempoInicio(tempoPausado);
                }
            }
            break;
        default:
            cout << "\nOpcao invalida! Escolha outra opcao.";
            break;
        }
    } while (opcao != 0);
}*/