//
// Created by ronyrojas on 20/03/25.
//
#include <ctime>
#include "../include/Trampa.h"

Trampa::Trampa() {
    srand(time(0));
    dano = 15 + rand() % 21;
}

int Trampa::getDano() const {
    return dano;
}

void Trampa::setDano(int dano) {
    this->dano = dano;
}
