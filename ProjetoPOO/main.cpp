#include <iostream>
using namespace std;

#include "Casino.h"
#include "Pessoas.h"
#include "menu.h"
#include "Uteis.h"
#include "relogio.h"


int main()
{
    //menuGeral();
    srand(time(NULL));
    Casino* solverde = new Casino("solverde",40);
    solverde->LerFicheiro();
    /*Pessoa* pessoa = solverde->GetPessoa();
    Pessoa* pessoa2 = solverde->GetPessoa();
    Pessoa* pessoa3 = solverde->GetPessoa();
    solverde->AddPessoa(pessoa);
    solverde->AddPessoa(pessoa2);
    solverde->AddPessoa(pessoa3);

    //casino.MostrarMaquinas();
    //casino.MostrarPessoasCasino();
    //casino.MostrarMaquinas();

    Maquina maq = Maquina::Maquina(77, TIPO_MAQUINA::BlackJack, 9, 9);
    Maquina maq2 = Maquina::Maquina(9, TIPO_MAQUINA::ClassicSlots, 19, 9);
    Maquina maq3 = Maquina::Maquina(10, TIPO_MAQUINA::Roleta, 0, 9);
    maq.AddJogadorMaquina(pessoa);
    maq2.AddJogadorMaquina(pessoa2);
    maq3.AddJogadorMaquina(pessoa3);

    for (int i = 0; i < 5; i++)
    {
        maq.JogadorJoga(maq.CalcularBet(), solverde);
        maq2.JogadorJoga(maq2.CalcularBet(), solverde);
        maq3.JogadorJoga(maq3.CalcularBet(), solverde);
    }

    cout << "\n\n";
    solverde->MostrarListaPessoas(solverde->Jogadores_Mais_Ganhos());
    cout << "\n\n";
    solverde->Listar(40);
    cout << "\n";
    //solverde->MostrarListaMaquinas(solverde->Ranking_Das_Mais_Trabalhadores());
    maq.MostrarMaquina();*/

    //solverde->MostrarMaquinas();
    //solverde->Relatorio("relatorio.txt");
    
    //solverde->ListarEstadoCasino();

    /*solverde->Run();
    solverde->MostrarListaPessoas(solverde->Jogadores_Mais_Ganhos());
    cout << "Dinheiro Recebido= " << solverde->DinheiroRecebido;
    cout << "Dinheiro Perdido= " << solverde->DinheiroPerdido;
    cout << "\n\nLucro= " << solverde->DinheiroRecebido - solverde->DinheiroPerdido;*/

    Relogio relogio;

    // Iniciando o relógio
    StartRelogio(&relogio, 1, "12:00:00");

    // Verificando o tempo após 10 segundos
    std::cout << "Tempo Inicial: " << VerTimeRelogio(&relogio) << std::endl;
    Wait(10);
    std::cout << "Tempo após 10 segundos: " << VerTimeRelogio(&relogio) << std::endl;

    // Alterando a velocidade do relógio para 2
    MudarVelocidadeRelogio(&relogio, 2);
    std::cout << "Velocidade alterada para 2. Tempo atual: " << VerTimeRelogio(&relogio) << std::endl;

    // Verificando o tempo após mais 5 segundos (velocidade 2)
    Wait(5);
    std::cout << "Tempo após mais 5 segundos na velocidade 2: " << VerTimeRelogio(&relogio) << std::endl;

    // Pausando o relógio
    MudarVelocidadeRelogio(&relogio, 0);
    std::cout << "Relógio pausado. Tempo atual: " << VerTimeRelogio(&relogio) << std::endl;

    // Retomando o relógio com velocidade 2
    MudarVelocidadeRelogio(&relogio, 2);
    std::cout << "Relógio retomado com velocidade 2. Tempo atual: " << VerTimeRelogio(&relogio) << std::endl;


    //cout <<"\n\nMemoria Ocupada: " << solverde->Memoria_Total();
    return 7;//CR7 GOAT
}