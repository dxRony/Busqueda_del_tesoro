//
// Created by ronyrojas on 20/03/25.
//
#include "../include/Jugador.h"

Jugador::Jugador() : Casilla() {
    nombre = "";
    vida = 200;
    puntos = 0;
    movimientos = 0;
    tiempoJugado = 0;
    enemigosEncontrados = 0;
    trampasActivadas = 0;
    pocimasEncontradas = 0;
    pistasEncontradas = 0;
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

int Jugador::getEnemigosEncontrados() const {
    return enemigosEncontrados;
}

void Jugador::setEnemigosEncontrados(int enemigosEncontrado) {
    this->enemigosEncontrados = enemigosEncontrado;
}

int Jugador::getTrampasActivadas() const {
    return trampasActivadas;
}

void Jugador::setTrampasActivadas(int trampas) {
    this->trampasActivadas = trampas;
}

int Jugador::getPocimasEncontrados() const {
    return pocimasEncontradas;
}

void Jugador::setPocimasEncontrados(int pocimasEncontrado) {
    this->pocimasEncontradas = pocimasEncontrado;
}

int Jugador::getPistasEncontrados() const {
    return pistasEncontradas;
}

void Jugador::setPistasEncontrados(int pistas) {
    this->pistasEncontradas = pistas;
}
