#pragma once
#include <iostream>
#include <ctime>

class Relogio {
    time_t START;
    int VELOCIDADE;
    time_t Hora_Inicio;
    bool pausado;
    time_t tempoPausado;

public:
    Relogio();
    void StartRelogio(int Vel, const char* H_Inicio);
    void MudarVelocidadeRelogio(int Vel);
    time_t VerTimeRelogio();
    void WaitSegundos(int s);
    void Wait(int s);
    tm StringParaTM(const char* H_Inicio);
};