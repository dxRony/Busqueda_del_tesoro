//
// Created by ronyrojas on 27/03/25.
//
#include "../include/Partida.h"
#include "../include/Pista.h"
#include "../include/Pocima.h"
#include "../include/Tesoro.h"


Partida::Partida(string nombreJugador, int ancho, int alto, int profundidad): jugador(nombreJugador) {
    cout << "recibiendo parametros en constructor de partia:" << endl;
    cout << "ancho: " << ancho << endl;
    cout << "alto: " << alto << endl;
    cout << "profundidad: " << profundidad << endl;
    cout << "nombreJugador: " << nombreJugador << endl;

    this->ancho = ancho;
    this->alto = alto;
    this->profundidad = profundidad;

    jugadorEliminado = false;
    tesoroEncontrado = false;

    tableroDeJuego = new ThreeDimensionalMatrix<Casilla>(ancho, alto, profundidad);
    enemigosPartida = new BST<Enemigo>();
    trampasPartida = new BST<Trampa>();
    registroTrayectoria = new LinkedList<string>();
    registroEnemigosYTrampas = new LinkedList<string>();
    registroPistas = new LinkedList<string>();
    registroPocimas = new LinkedList<string>();

    cout << "Generando tablero..." << endl;
    this->generarTablero();
    cout << "Tablero generado" << endl;
}

void Partida::iniciarPartida() {
    while (!jugadorEliminado || !tesoroEncontrado) {
    }
}

void Partida::generarTablero() {
    int tesoroX = rand() % ancho;
    int tesoroY = rand() % alto;
    int tesoroZ = rand() % profundidad;
    Tesoro tesoro;
    tesoro.setPosicionX(tesoroX);
    tesoro.setPosicionY(tesoroY);
    tesoro.setPosicionZ(tesoroZ);
    //posicionando aleatoriamente el tesoro
    tableroDeJuego->insertar(tesoroX, tesoroY, tesoroZ, tesoro);

    int jugadorX, jugadorY, jugadorZ;
    do {
        jugadorX = rand() % ancho;
        jugadorY = rand() % alto;
        jugadorZ = rand() % profundidad;
    } while (jugadorX == tesoroX && jugadorY == tesoroY && jugadorZ == tesoroZ);
    jugador.setPosicionX(jugadorX);
    jugador.setPosicionY(jugadorY);
    jugador.setPosicionZ(jugadorZ);
    tableroDeJuego->insertar(jugadorX, jugadorY, jugadorZ, jugador);

    for (int z = 0; z < profundidad; z++) {
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                if ((x == tesoroX && y == tesoroY && z == tesoroZ)
                    || x == jugadorX && y == jugadorY && z == jugadorZ) {
                    //ignorando la posicion del tesoro y jugador
                    continue;
                }
                int random = rand() % 100;
                if (random < 15) {
                    //15% de generacion para enemigos
                    Enemigo enemigoGenerado;
                    enemigoGenerado.setPosicionX(x);
                    enemigoGenerado.setPosicionY(y);
                    enemigoGenerado.setPosicionZ(z);
                    tableroDeJuego->insertar(x, y, z, enemigoGenerado);
                    enemigosPartida->insertar(enemigoGenerado);
                } else if (random < 35) {
                    //20% de generacion para trampas
                    Trampa trampaGenerada;
                    trampaGenerada.setPosicionX(x);
                    trampaGenerada.setPosicionY(y);
                    trampaGenerada.setPosicionZ(z);
                    tableroDeJuego->insertar(x, y, z, trampaGenerada);
                    trampasPartida->insertar(trampaGenerada);
                } else if (random < 60) {
                    //25% de generacion para pocimas
                    Pocima pocimaGenerada;
                    pocimaGenerada.setPosicionX(x);
                    pocimaGenerada.setPosicionY(y);
                    pocimaGenerada.setPosicionZ(z);
                    tableroDeJuego->insertar(x, y, z, pocimaGenerada);
                } else {
                    //40% de generacion para pistas
                    Pista pistaGenerada;
                    pistaGenerada.setPosicionX(x);
                    pistaGenerada.setPosicionY(y);
                    pistaGenerada.setPosicionZ(z);
                    tableroDeJuego->insertar(x, y, z, pistaGenerada);
                }
            }
        }
    }
}

void Partida::moverJugador(int direccion) {
}
