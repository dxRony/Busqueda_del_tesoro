//
// Created by ronyrojas on 20/03/25.
//
#include "../include/Casilla.h"

Casilla::Casilla() {
    this->setRepresentacion('~');
    posicionX = 0;
    posicionY = 0;
    posicionZ = 0;
    efecto = 0;
}

int Casilla::getPosicionX() const {
    return posicionX;
}

void Casilla::setPosicionX(int posicion_x) {
    this->posicionX = posicion_x;
}

int Casilla::getPosicionY() const {
    return posicionY;
}

void Casilla::setPosicionY(int posicion_y) {
    this->posicionY = posicion_y;
}

int Casilla::getPosicionZ() const {
    return posicionZ;
}

void Casilla::setPosicionZ(int posicion_z) {
    this->posicionZ = posicion_z;
}

string Casilla::getUbicacion() const {
    return ubicacion;
}

void Casilla::setUbicacion(string ubicacion) {
    this->ubicacion = ubicacion;
}

char Casilla::getRepresentacion() const {
    return representacion;
}

void Casilla::setRepresentacion(char representacion) {
    this->representacion = representacion;
}

int Casilla::getEfecto() const {
    return efecto;
}

void Casilla::setEfecto(int efecto) {
    this->efecto = efecto;
}

ostream &operator<<(ostream &os, const Casilla &casilla) {
    os << casilla.getRepresentacion();
    return os;
}
