#include "Relogio.h"
#include <cstdio>
#include <iomanip>
#include <iostream>

Relogio::Relogio() : START(0), VELOCIDADE(0), Hora_Inicio(0), TempoParado(0), pausa(NAO_PARADO) {}

void Relogio::StartRelogio(int Vel, const char* H_Inicio) {
    START = time(0);
    VELOCIDADE = Vel;
    struct tm tmp = { 0 }; // Inicializa a estrutura tm
    sscanf_s(H_Inicio, "%d:%d:%d", &tmp.tm_hour, &tmp.tm_min, &tmp.tm_sec);
    tmp.tm_isdst = -1; // Define o horário de verão automaticamente

    // Obter a hora atual para preservar a data e alterar apenas a hora, minuto e segundo
    time_t horaAtual = time(0);
    struct tm horaIntroduzida;
    localtime_s(&horaIntroduzida, &horaAtual);
    horaIntroduzida.tm_hour = tmp.tm_hour;
    horaIntroduzida.tm_min = tmp.tm_min;
    horaIntroduzida.tm_sec = tmp.tm_sec;

    Hora_Inicio = mktime(&horaIntroduzida);
    char buffer[10];
    strftime(buffer, sizeof(buffer), "%T", &horaIntroduzida); // Formata no formato HH:MM:SS
    pausa = NAO_PARADO;
}

time_t Relogio::VerTimeRelogio() {
    time_t Dif = difftime(time(0), START);
    time_t Simulada = Hora_Inicio + Dif * VELOCIDADE;
    return Simulada;
}

void Relogio::WaitSegundos(int s) {
    clock_t T0 = clock();
    clock_t T1 = T0 + s;
    while (clock() < T1);
}

void Relogio::Wait(int s) {
    WaitSegundos(s * CLOCKS_PER_SEC);
}

void Relogio::PararRelogio() {
    if (pausa != PARADO) {
        pausa = PARADO;
        TempoParado = time(0) - START;
    }
}

void Relogio::RetomarRelogio() {
    if (pausa != NAO_PARADO) {
        pausa = NAO_PARADO;
        START = time(0) - TempoParado;
    }
}

void Relogio::MostrarTempo(time_t tempo) {
    time_t tempoAtual = VerTimeRelogio();
    time_t tempoDecorrido = tempoAtual - Hora_Inicio;

    int horas = tempoDecorrido / 3600; // Calcula o número de horas
    int minutos = (tempoDecorrido % 3600) / 60; // Calcula o número de minutos
    int segundos = tempoDecorrido % 60; // Calcula o número de segundos

    int horaInicio = Hora_Inicio % (24 * 3600); // Obtém o número de segundos desde a meia-noite do dia de início
    int horasInicio = horaInicio / 3600; // Calcula as horas do horário de início

    horas = (horas + horasInicio) % 24; // Ajusta as horas para ficarem no intervalo de 0 a 23

    std::cout << "Horario Casino: ";
    std::cout << std::setfill('0') << std::setw(2) << horas << ":";
    std::cout << std::setfill('0') << std::setw(2) << minutos << ":";
    std::cout << std::setfill('0') << std::setw(2) << segundos << std::endl;
}