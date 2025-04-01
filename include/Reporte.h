//
// Created by ronyrojas on 30/03/25.
//

#ifndef REPORTE_H
#define REPORTE_H
#include "Partida.h"
#include "edd/LinkedList.h"

class Reporte {
private:
    LinkedList<Partida> partidas;
    LinkedList<Jugador> tablaJugadores;

public:
    void agregarPartida(const Partida &partida);

    void agregarJugador(const Jugador &jugador);

    void mostrarReportesPartidas();

    void mostrarTablaJugadores();

    void mostrarMenuReportesPartidas(int indiceJugador);

    LinkedList<Partida> &getPartidas();

    void ordenarTablaJugadores();
};
#endif //REPORTE_H
