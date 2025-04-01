//
// Created by ronyrojas on 30/03/25.
//
#include "../include/Reporte.h"

void Reporte::agregarPartida(const Partida &partida) {
    partidas.insertarFinal(partida);
}

void Reporte::agregarJugador(const Jugador &jugador) {
    tablaJugadores.insertarFinal(jugador);
}

void Reporte::mostrarReportesPartidas() {
    Node<Partida>* actual = partidas.getCabeza();
    if (!actual) {
        cout << "no hay partidas guardadas" << endl;
        return;
    }
    cout << "\n--- Reporte de Partidas Jugadas ---\n";
    while (actual) {
        cout << "Jugador: " << actual->getData().getJugador().getNombre() << endl;
        cout << "Dimensiones del Tablero: " << actual->getData().getAncho() << "x"
             << actual->getData().getAlto() << "x" << actual->getData().getProfundidad() << endl;
        cout << "-----------------------------------\n";
        actual = actual->getNext();
    }
}

void Reporte::mostrarTablaJugadores() {
    Node<Jugador>* actual = tablaJugadores.getCabeza();
    if (!actual) {
        cout << "No hay jugadores registrados." << endl;
        return;
    }
    cout << "\n--- Tabla de Jugadores ---\n";
    while (actual) {
        cout << "Nombre: " << actual->getData().getNombre() << endl;
        cout << "Puntos Totales: " << actual->getData().getPuntos() << endl;
        cout << "-------------------------\n";
        actual = actual->getNext();
    }
}
