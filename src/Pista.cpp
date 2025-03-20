//
// Created by ronyrojas on 20/03/25.
//
#include "../include/Pista.h"

Pista::Pista() {
    distanciaTesoro = 0;
    mensaje = "";
}

int Pista::getDistanciaTesoro() {
    return distanciaTesoro;
}

void Pista::setDistanciaTesoro(int distanciaTesoro) {
    this->distanciaTesoro = distanciaTesoro;
}

string Pista::getMensaje() {
    return mensaje;
}

void Pista::setMensaje(string mensaje) {
    this->mensaje = mensaje;
}
