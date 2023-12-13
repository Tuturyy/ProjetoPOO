#include "relogio.h"
#include <iostream>
#include <iomanip>

void StartRelogio(Relogio* R, int Vel, const char* H_Inicio) {
    R->START = time(0);
    R->VELOCIDADE = Vel;
    struct tm timeInfo;
    localtime_s(&timeInfo, &R->START);
    sscanf_s(H_Inicio, "%d:%d:%d", &timeInfo.tm_hour, &timeInfo.tm_min, &timeInfo.tm_sec);
    R->Hora_Inicio = mktime(&timeInfo);
    R->pausado = 0;
    R->tempoPausado = 0;
}

void MudarVelocidadeRelogio(Relogio* R, int Vel) {
    if (R->pausado) {
        R->VELOCIDADE = Vel;
        R->pausado = 0;
        time_t tempoAtual = time(0);
        R->START = tempoAtual - R->tempoPausado;
    }
    else {
        R->VELOCIDADE = 0;
        R->pausado = 1;
        R->tempoPausado = difftime(time(0), R->START);
    }
}

time_t VerTimeRelogio(Relogio* R) {
    if (R->pausado) {
        return R->Hora_Inicio;
    }
    else {
        time_t tempoAtual = time(0);
        time_t Dif = difftime(tempoAtual, R->START);
        if (R->VELOCIDADE == 0) {
            return R->Hora_Inicio + R->tempoPausado;
        }
        else {
            return R->Hora_Inicio + (Dif + R->tempoPausado) * R->VELOCIDADE;
        }
    }
}

void WaitSegundos(int s) {
    clock_t T0 = clock();
    clock_t T1 = T0 + s;
    while (clock() < T1);
}

void Wait(int s) {
    WaitSegundos(s * CLOCKS_PER_SEC);
}