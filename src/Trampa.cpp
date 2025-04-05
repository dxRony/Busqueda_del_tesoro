//
// Created by ronyrojas on 20/03/25.
//
#include "../include/Trampa.h"

Trampa::Trampa() {
    this->setRepresentacion('*');
    this->setTipoCasilla("Trampa");
    dano = 15 + rand() % 21;
}

int Trampa::getDano() const {
    return dano;
}

void Trampa::setDano(int dano) {
    this->dano = dano;
}
