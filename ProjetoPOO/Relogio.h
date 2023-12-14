#pragma once
#include <iomanip>
#include <ctime>

#define PARADO 1
#define NAO_PARADO 0

class Relogio {
public:
    Relogio();

    void StartRelogio(int Vel, const char* H_Inicio);
    time_t VerTimeRelogio();
    void WaitSegundos(int s);
    void Wait(int s);
    void PararRelogio();
    void RetomarRelogio();
    void MostrarTempo(time_t tempo);

private:
    time_t START;
    int VELOCIDADE;
    time_t Hora_Inicio;
    time_t TempoParado;
    int pausa; //1-PARADO   0-NAO PARADO
};
