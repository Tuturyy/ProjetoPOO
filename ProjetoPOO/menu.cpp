#include <iostream>
#include "menu.h"
#include "Casino.h"
#include "Pessoas.h"
#include <conio.h>

using namespace std;

int getSafeInput() {
    int input;
    while (true) {
        cin >> input;

        if (cin.fail()) {
            // Limpar o estado de erro
            cin.clear();

            // Descartar o buffer de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Entrada inválida. Digite um número válido: ";
        }
        else {
            // Limpar o buffer de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    return input;
}

void printLine() {
    cout << "===============================================" << endl;
}

void menu() {
    cout<<"\n\n";
    printLine();
    cout << "           MENU GESTAO DO CASINO             " << endl;
    printLine();
	cout << "\n1 - Maquinas" << endl;
	cout << "\n2 - Jogadores" << endl;
	cout << "\n3 - Casino" << endl;
	cout << "\n0 - Sair\n" << endl;
    printLine();
}

void subMenuMaquinas(Casino* casino) {
    

    int opcao;
    int idmaquinaOff, idmaquinaShow, prob;
    string tipoMaquina;
    Maquina* maquinaOff = nullptr;
    Maquina* maquinaShow = nullptr;

    do {
        cout << "\n";
        printLine();
        cout << "           SUBMENU DE MAQUINAS              " << endl;
        printLine();
        cout << "\n1 - Listar maquinas" << endl;
        cout << "\n2 - Listar maquinas de um dado tipo" << endl;
        cout << "\n3 - Desligar maquina" << endl;
        cout << "\n4 - Ver estado de maquina" << endl;
        cout << "\n5 - Listar as maquinas com a probabilidade de ganhar superior a X" << endl;
        cout << "\n6 - Maquinas mais usadas" << endl;
        cout << "\n7 - Maquinas que mais avariam" << endl;
        cout << "\n0 - Voltar atras" << endl;
        printLine();
        cout << "Escolhe uma opcao:" << endl;
        opcao = getSafeInput();

        switch (opcao) {
        case 1:
            cout << "\nLISTA DE MAQUINAS:\n";
            casino->MostrarMaquinas();
            break;
        case 2:
            cout << "Qual o tipo das maquinas que deseja listar? (Poker, ClassicSlots, BlackJack, Roleta)";
            cin >> tipoMaquina;
            casino->MostrarListaMaquinas(casino->Listar_TipoMaquina(tipoMaquina));
            break;
        case 3:
            cout << "Qual o id da maquina que pretende desligar?\n";
            cin >> idmaquinaOff;
            maquinaOff = casino->PesquisarMaquinaID(idmaquinaOff);
            maquinaOff->DesligarMaquina();
            break;
        case 4:
            cout << "Qual o id da maquina que pretende ver?\n";
            cin >> idmaquinaShow;
            maquinaShow = casino->PesquisarMaquinaID(idmaquinaShow);
            maquinaShow->getEstado();
            break;
        case 5:
            cout << "Qual o valor de X? (em %)\n";
            cin >> prob;
            casino->ListarMaquinasProbabilidadeMaiorQueX(prob);
            break;
        case 6:
            casino->MostrarListaMaquinas(casino->Ranking_Das_Mais_Trabalhadores());
            break;
        case 7:
            casino->MostrarListaMaquinas(casino->Maquinas_Mais_Avarias());
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (opcao != 0);
}

void subMenuJogadores(Casino* casino) {
    

    int opcao;
    int IDjogador = 0;
    Pessoa* jogador = nullptr;

    do
    {
        cout << "\n";
        printLine();
        cout << "           SUBMENU DE JOGADORES              " << endl;
        printLine();
        cout << "\n1 - Listar jogadores" << endl;
        cout << "\n2 - Jogadores que mais ganharam" << endl;
        cout << "\n3 - Jogadores mais frequentes" << endl;
        cout << "\n4 - Mostrar historico de apostas de um jogador" << endl;
        cout << "\n0 - Voltar atras" << endl;
        printLine();
        cout << "Escolhe uma opcao:" << endl;
        opcao = getSafeInput();
        

        switch (opcao)
        {
        case 1:
            casino->MostrarListaPessoas(casino->getListaPessoasCasino());
            break;
        case 2:
            casino->MostrarListaPessoas(casino->Jogadores_Mais_Ganhos());
            break;
        case 3:
            casino->MostrarListaPessoas(casino->Jogadores_Mais_Frequentes());
            break;
        case 4:
            cout << "Qual o ID do jogador?";
            cin >> IDjogador;
            jogador = casino->PesquisarPessoaID(IDjogador);
            jogador->MostrarHistoricoApostas();
        case 0:
            break;
        default:
            break;
        }
    } while (opcao != 0);
}

void subMenuCasino(Casino* casino) {
    

    int opcao;

    do
    {
        cout << "\n";
        printLine();
        cout << "           SUBMENU DE CASINO              " << endl;
        printLine();
        cout << "\n1 - Estado atual do casino" << endl;
        cout << "\n2 - Relatorio do casino" << endl;
        cout << "\n3 - Memoria ocupada" << endl;
        cout << "\n4 - Estatisticas" << endl;
        cout << "\n0 - Voltar atras" << endl;
        printLine();
        cout << "Escolhe uma opcao:" << endl;
        opcao = getSafeInput();

        switch (opcao)
        {
        case 1:
            casino->ListarEstadoCasino();
            break;
        case 2:
            //casino->Relatorio(ficheiro a definir);
            break;
        case 3:
            cout << casino->Memoria_Total();
            break;
        case 4:
            casino->EstatisticasCasino();
            break;
        case 0:
            break;
        default:
            break;
        }
    } while (opcao != 0);
}

void menuGeral(Relogio& relogio, Casino* casino) {
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do {
        menu();
        cout << "Escolhe uma opcao:" << endl;
        opcao = getSafeInput();

        switch (opcao) {
        case 1:
            subMenuMaquinas(casino);
            break;
        case 2:
            subMenuJogadores(casino);
            break;
        case 3:
            subMenuCasino(casino);
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