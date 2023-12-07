#pragma once
#include <iostream>
#include <ctime>

class Relogio {
private:
    time_t START;
    int VELOCIDADE;
    time_t Hora_Inicio;
    bool pausado;
    time_t tempoPausado;

public:
    Relogio();
    void StartRelogio(int Vel, int tempo_segundos);
    void MudarVelocidadeRelogio(int Vel);
    time_t VerTimeRelogio();
    void WaitSegundos(int s);
    void Wait(int s);
    void MostrarTempoSegundos(int TempoAtual, int TempoFinal, int TempoTotal);
};