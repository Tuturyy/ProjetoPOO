#include <iostream>
using namespace std;

#include "Casino.h"
#include "Pessoas.h"
#include"Uteis.h"


int main()
{

    srand(time(NULL));
    Casino casino = Casino("solverde",4);
    casino.LerFicheiro();
    Pessoa* pessoa = casino.GetPessoa();
    casino.AddPessoa(pessoa);
    
    //casino.MostrarMaquinas();
    //casino.MostrarPessoasCasino();
    //casino.MostrarMaquinas();

    Maquina maq = Maquina::Maquina(77, TIPO_MAQUINA::Roleta, 9, 9);
    maq.AddJogadorMaquina(pessoa);
    int lucro=0;
    cout << "saldo inic=" << pessoa->Saldo << "\n";
    for (int i=0;i<3;i++)
    {
        if(pessoa->Saldo > 0)
        {
            int randombet = Util::RandNumInt(1, pessoa->Saldo);
            lucro += maq.JogadorJoga(randombet);
        }
    }
    cout << "Lucro =" << lucro << endl << "Saldo=" << pessoa->Saldo;

    return 7;//CR7 GOAT
}