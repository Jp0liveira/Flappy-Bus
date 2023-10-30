#include "Data.h"
#include <ctime>
#include <iostream>
using std::cout;

Data::Data(int d, int m, int a) {
    if (m > 0 && m <= 12) // validate the month
        mes = m;

    if (a < 0)
        ano = 1900;
    else
        ano = a;

    dia = VerificaDia(d);

    hora = 0;
    minuto = 0;
    segundo = 0;
}

void Data::print() const {
    std::cout << dia << '/' << mes << '/' << ano << " ";
    std::cout << hora << ':' << minuto << ':' << segundo;
}

int Data::VerificaDia(int diaTeste) const {
    static const int diasPorMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (diaTeste > 0 && diaTeste <= diasPorMes[mes])
        return diaTeste;

    if (mes == 2 && diaTeste == 29 && (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)))
        return diaTeste;

    cout << "Dia inválido (" << diaTeste << ") configurado para 1.\n";
    return 1;
}

void Data::setCurrentDate() {
    std::time_t currentTime = std::time(nullptr);
    std::tm *localTime = std::localtime(&currentTime);

    if (localTime) {
        dia = localTime->tm_mday;
        mes = localTime->tm_mon + 1; // tm_mon is 0-based
        ano = localTime->tm_year + 1900;
        hora = localTime->tm_hour;
        minuto = localTime->tm_min;
        segundo = localTime->tm_sec;
    }
}