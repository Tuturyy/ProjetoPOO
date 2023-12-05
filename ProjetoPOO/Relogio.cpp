#include "Relogio.h"
#include <sstream>

Relogio::Relogio() : START(0), VELOCIDADE(0), Hora_Inicio(0), pausado(false), tempoPausado(0) {}

void Relogio::StartRelogio(int Vel, const char* H_Inicio) {
    START = time(0);
    VELOCIDADE = Vel;

    std::tm tmp = StringParaTM(H_Inicio);

    int result = sscanf_s(H_Inicio, "%d:%d:%d", &tmp.tm_hour, &tmp.tm_min, &tmp.tm_sec);
    if (result != 3) {
        // Tratar erro na conversão
    }
    else {
        time_t temp = std::mktime(&tmp);
        if (temp == -1) {
            // Erro ao converter para tempo
            // Lida com o erro de conversão de tempo, se necessário
        }
        else {
            Hora_Inicio = temp;
            pausado = false;
            tempoPausado = 0;
        }
    }
}

std::tm Relogio::StringParaTM(const char* H_Inicio) {
    std::tm tm = {};
    std::stringstream ss(H_Inicio);
    ss >> tm.tm_hour;
    ss.ignore(); // ignore o separador (no caso, ":")
    ss >> tm.tm_min;
    ss.ignore();
    ss >> tm.tm_sec;
    return tm;
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
    clock_t T1 = T0 + s;
    while (clock() < T1);
}

void Relogio::Wait(int s) {
    WaitSegundos(s * CLOCKS_PER_SEC);
}