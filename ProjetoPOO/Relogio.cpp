#include "Relogio.h"

Relogio::Relogio() : START(0), VELOCIDADE(0), Hora_Inicio(0), pausado(false), tempoPausado(0) {}

void Relogio::StartRelogio(int Vel, int tempo_segundos) {
    START = time(0);
    VELOCIDADE = Vel;
    Hora_Inicio = START + tempo_segundos;
    pausado = false;
    tempoPausado = 0;
}

void Relogio::MudarVelocidadeRelogio(int Vel) {
    if (pausado) {
        VELOCIDADE = Vel;
        pausado = false;
        time_t tempoAtual = time(0);
        START = tempoAtual - tempoPausado;
    }
    else {
        VELOCIDADE = 0;
        pausado = true;
        tempoPausado = difftime(time(0), START);
    }
}

time_t Relogio::VerTimeRelogio() {
    if (pausado) {
        return Hora_Inicio;
    }
    else {
        time_t Dif = difftime(time(0), START);
        time_t Simulada = Hora_Inicio + Dif * VELOCIDADE;
        return Simulada;
    }
}

void Relogio::WaitSegundos(int s) {
    clock_t T0 = clock();
    clock_t T1 = T0 + s * CLOCKS_PER_SEC;
    while (clock() < T1);
}

void Relogio::Wait(int s) {
    WaitSegundos(s);
}

void Relogio::MostrarTempoSegundos(int TempoAtual, int TempoFinal, int TempoTotal)
{
    std::cout << "Tempo atual: " << TempoAtual - TempoFinal + TempoTotal << std::endl;
    std::cout << "Tempo final: " << TempoFinal - TempoFinal + TempoTotal << std::endl;
}
