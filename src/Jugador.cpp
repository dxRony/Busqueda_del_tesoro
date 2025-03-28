//
// Created by ronyrojas on 20/03/25.
//
#include "../include/Jugador.h"

Jugador::Jugador(string nombre) {
    this->nombre = nombre;
    this->setRepresentacion('J');
    vida = 200;
    puntos = 0;
    movimientos = 0;
    tiempoJugado = 0;
}

int Jugador::opcionesTurno() const {
    int opcion;
    cout << "*********** Selecciona Una Opcion ***********" << endl;
    cout << "1. Moverme" << endl;
    cout << "2. Ver estadisticas" << endl;
    cout << "3. Terminar Partida" << endl;
    cout << "Selecciona Una Opcion" << endl;
    cin >> opcion;
    return opcion;
}

string Jugador::getNombre() const {
    return nombre;
}

void Jugador::setNombre(string nombre) {
    this->nombre = nombre;
}

int Jugador::getVida() const {
    return vida;
}

void Jugador::setVida(int vida) {
    this->vida = vida;
}

int Jugador::getPuntos() const {
    return puntos;
}

void Jugador::setPuntos(int puntos) {
    this->puntos = puntos;
}

int Jugador::getMovimientos() const {
    return movimientos;
}

void Jugador::setMovimientos(int movimientos) {
    this->movimientos = movimientos;
}

int Jugador::getTiempoJugado() const {
    return tiempoJugado;
}

void Jugador::setTiempoJugado(int tiempo) {
    this->tiempoJugado = tiempo;
}
