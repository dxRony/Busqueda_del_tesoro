//
// Created by ronyrojas on 20/03/25.
//

#ifndef PISTA_H
#define PISTA_H
#include "Casilla.h"
#include <string>
using namespace std;

class Pista : public Casilla {
private:
    int distanciaTesoro;
    string mensaje;

public:
    Pista();

    int getDistanciaTesoro();

    void setDistanciaTesoro(int distanciaTesoro);

    string getMensaje();

    void setMensaje(string mensaje);
};

#endif //PISTA_H
