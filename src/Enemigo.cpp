//
// Created by ronyrojas on 20/03/25.
//
#include "../include/Enemigo.h"
using namespace std;


Enemigo::Enemigo() {
    nivelAlto = (rand() % 2) == 0;
    this->setRepresentacion('E');
    if (nivelAlto) {
        vida = 26 + (rand() % 25);
    } else {
        vida = 15 + (rand() % 11);
    }
}

bool Enemigo::isNivelAlto() const {
    return nivelAlto;
}

void Enemigo::setIsNivelAlto(bool nivelAlto) {
    this->nivelAlto = nivelAlto;
}

int Enemigo::getVida() const {
    return vida;
}

void Enemigo::setVida(int vida) {
    this->vida = vida;
}
