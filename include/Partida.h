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

    ~Partida();

    void iniciarPartida();

    void generarTablero();

    void generarTesoro();

    void generarJugador();

    void generarObjetosTablero();

    void generarEnemigo(int x, int y, int z);

    void generarTrampa(int x, int y, int z);

    void generarPocima(int x, int y, int z);

    void generarPista(int x, int y, int z);

    void realizarTurno(int opcionTurno);

    void moverJugador(int tipoMovimiento);

    void calcularPosicionMovimiento(int tipoMovimiento, int& nuevoX, int& nuevoY, int& nuevoZ, string& direccion);

    void procesarEfectoCasilla(Casilla &casilla, const string& direccion);

    void procesarEnemigo(Casilla& casilla);

    void procesarTrampa(Casilla& casilla);

    void procesarPocima(Casilla& casilla);

    void procesarPista(Casilla& casilla);

    void procesarTesoro(Casilla& casilla, const string& direccion);

    void registrarMovimiento(const Casilla& casilla, const string& direccion);

    void actualizarPosicionJugador(int nuevoX, int nuevoY, int nuevoZ);

    void reemplazarCasillaVacia(int nuevoX, int nuevoY, int nuevoZ);

    int calcularDistanciaPista(int nuevoX, int nuevoY, int nuevoZ);

    void procesarPista1(int distancia);

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
