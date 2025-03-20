//
// Created by ronyrojas on 20/03/25.
//

#ifndef JUGADOR_H
#define JUGADOR_H
#include "Casilla.h"
#include <string>
using namespace std;

class Jugador : public Casilla {
private:
    string nombre;
    int vida;
    int puntos;
    int movimientos;
    int tiempoJugado;
    //listaEnlazada registroMovimientos
    int enemigosEncontrados;
    int trampasActivadas;
    int pocimasEncontradas;
    int pistasEncontradas;

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

    int getEnemigosEncontrados() const;

    void setEnemigosEncontrados(int enemigosEncontrado);

    int getTrampasActivadas() const;

    void setTrampasActivadas(int trampasActivadas);

    int getPocimasEncontrados() const;

    void setPocimasEncontrados(int pocimasEncontrado);

    int getPistasEncontrados() const;

    void setPistasEncontrados(int pistasEncontrado);
};
#endif //JUGADOR_H
