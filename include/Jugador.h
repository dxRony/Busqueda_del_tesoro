//
// Created by ronyrojas on 20/03/25.
//

#ifndef JUGADOR_H
#define JUGADOR_H
#include "Casilla.h"
#include <string>
#include "edd/LinkedList.h"
using namespace std;

class Jugador : public Casilla {
private:
    string nombre;
    int vida;
    int puntos;
    int movimientos;
    int tiempoJugado;

public:
    Jugador();

    //getters y setters
    string getNombre() const;

    void setNombre(string nombre);

    int getVida() const;

    void setVida(int vida);

    int getPuntos() const;

    void setPuntos(int puntos);

    int getMovimientos() const;

    void setMovimientos(int movimientos);

    int getTiempoJugado() const;

    void setTiempoJugado(int tiempoJugado);
};
#endif //JUGADOR_H
