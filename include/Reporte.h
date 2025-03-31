//
// Created by ronyrojas on 30/03/25.
//

#ifndef REPORTE_H
#define REPORTE_H
#include "Partida.h"
#include "edd/LinkedList.h"

class Reporte {
private:
    LinkedList<Partida> *partidas;
    LinkedList<Jugador> *jugadores;
public:
    Reporte();

    ~Reporte();
};
#endif //REPORTE_H
