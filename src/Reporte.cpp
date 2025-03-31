//
// Created by ronyrojas on 30/03/25.
//
#include "../include/Reporte.h"

Reporte::Reporte() {
    this->partidas = new LinkedList<Partida>();
    this->jugadores = new LinkedList<Jugador>();
}

Reporte::~Reporte() {
    delete partidas;
    delete jugadores;
}
