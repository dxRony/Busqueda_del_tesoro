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
    bool jugadorEliminado;
    bool tesoroEncontrado;
    bool partidaAbandonada;
    ThreeDimensionalMatrix<Casilla> *tableroDeJuego;
    int ancho, alto, profundidad;
    BST<int> *enemigosPartida;
    BST<int> *trampasPartida;
    LinkedList<string> *registroTrayectoria;
    LinkedList<string> *registroEnemigosYTrampas;
    LinkedList<string> *registroPistas;
    int tesoroX, tesoroY, tesoroZ;
    time_t tiempoPartida;

public:
    Partida();

    Partida(string nombreJugador, int ancho, int alto, int profundidad);

    void iniciarPartida();

    void generarTablero();

    void realizarTurno(int opcionTurno);

    void moverJugador(int tipoMovimiento);

    void reemplazarCasillaVacia(int nuevoX, int nuevoY, int nuevoZ);

    int calcularDistanciaPista(int nuevoX, int nuevoY, int nuevoZ);

    void mostrarEstadisticas();

    //getters
    int getAncho();

    int getAlto();

    int getProfundidad();

    bool isTesoroEncontrado();

    Jugador getJugador();

    Partida *getPartida();

    LinkedList<string> *getRegistroTrayectoria();

    LinkedList<string> *getRegistroEnemigosYTrampas();

    LinkedList<string> *getRegistroPistas();

    BST<int> *getTrampasPartida() const;

    void setTrampasPartida(BST<int> *trampasPartida);

    BST<int> *getEnemigosPartida() const;

    void setEnemigosPartida(BST<int> *enemigosPartida);

    friend ostream &operator<<(ostream &os, Partida &partida);
};
#endif //PARTIDA_H
