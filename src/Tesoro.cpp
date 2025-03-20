//
// Created by ronyrojas on 20/03/25.
//
#include "../include/Tesoro.h"

Tesoro::Tesoro() {
    valor = 1000;
}

int Tesoro::getValor() {
    return valor;
}

void Tesoro::setValor(int valor) {
    this->valor = valor;
}
