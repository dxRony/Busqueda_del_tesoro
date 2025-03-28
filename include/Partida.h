//
// Created by ronyrojas on 27/03/25.
//

#ifndef PARTIDA_H
#define PARTIDA_H
#include "Enemigo.h"
#include "Jugador.h"
#include "Trampa.h"
#include "edd/BST.h"
#include "edd/LinkedList.h"
#include "edd/ThreeDimensionalMatrix.h"
using namespace std;

class Partida {
private:
    Jugador jugador;
    bool jugadorEliminado = false;
    bool tesoroEncontrado = false;
    ThreeDimensionalMatrix<Casilla> *tableroDeJuego;
    int ancho, alto, profundidad;
    BST<Enemigo> *enemigosPartida;
    BST<Trampa> *trampasPartida;
    LinkedList<string> *registroTrayectoria;
    LinkedList<string> *registroEnemigosYTrampas;
    LinkedList<string> *registroPistas;
    LinkedList<string> *registroPocimas;

public:
    Partida(string nombreJugador, int ancho, int alto, int profundidad);

    void iniciarPartida();

    void generarTablero();

    void moverJugador(int direccion);

    void mostrarEstadoPartida();

    void guardarReporte();
};
#endif //PARTIDA_H
