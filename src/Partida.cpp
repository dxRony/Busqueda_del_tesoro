//
// Created by ronyrojas on 27/03/25.
//
#include "../include/Partida.h"
#include "../include/Pista.h"
#include "../include/Pocima.h"
#include "../include/Tesoro.h"


Partida::Partida(string nombreJugador, int ancho, int alto, int profundidad): jugador(nombreJugador) {
    this->ancho = ancho;
    this->alto = alto;
    this->profundidad = profundidad;

    jugadorEliminado = false;
    tesoroEncontrado = false;
    partidaAbandonada = false;

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
    tableroDeJuego->imprimir();
}

Partida::~Partida() {
    delete tableroDeJuego;
    delete enemigosPartida;
    delete trampasPartida;
    delete registroTrayectoria;
    delete registroEnemigosYTrampas;
    delete registroPistas;
    delete registroPocimas;
}


void Partida::iniciarPartida() {
    while (!jugadorEliminado && !tesoroEncontrado && !partidaAbandonada) {
        realizarTurno(jugador.mostrarOpcionesTurno());
        tableroDeJuego->imprimir();
    }
}

void Partida::generarTablero() {
    tesoroX = rand() % ancho;
    tesoroY = rand() % alto;
    tesoroZ = rand() % profundidad;
    Tesoro tesoro;
    tesoro.setPosicionX(tesoroX);
    tesoro.setPosicionY(tesoroY);
    tesoro.setPosicionZ(tesoroZ);
    //posicionando aleatoriamente el tesoro
    tableroDeJuego->insertar(tesoroX, tesoroY, tesoroZ, tesoro);

    int jugadorX, jugadorY, jugadorZ;
    do {
        //evitando que se coloque al jugador en el mismo lugar que el tesoro
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

void Partida::realizarTurno(int opcionTurno) {
    switch (opcionTurno) {
        case 1: {
            cout << "Ingresa la direccion del movimiento:" << endl;
            cout << "1. Arriba" << endl;
            cout << "2. Abajo" << endl;
            cout << "3. Derecha" << endl;
            cout << "4. Izquierda" << endl;
            cout << "5. Adelante" << endl;
            cout << "6. Atras" << endl;
            int direccion;
            cin >> direccion;
            moverJugador(direccion);
            break;
        }
        case 2: {
            cout << "Tus estadisticas son:" << endl;
            break;
        }
        case 3: {
            cout << "Abandonando la partida..." << endl;
            partidaAbandonada = true;
            break;
        }
        default: {
            cout << "Ingresa una opcion valida";
            break;
        }
    }
}

void Partida::moverJugador(int direccion) {
    int nuevaX = jugador.getPosicionX();
    int nuevaY = jugador.getPosicionY();
    int nuevaZ = jugador.getPosicionZ();

    switch (direccion) {
        case 1: nuevaY += 1;
            break; // Arriba
        case 2: nuevaY -= 1;
            break; // Abajo
        case 3: nuevaX += 1;
            break; // Derecha
        case 4: nuevaX -= 1;
            break; // Izquierda
        case 5: nuevaZ += 1;
            break; // Adelante
        case 6: nuevaZ -= 1;
            break; // Atrás
        default: cout << "Dirección no válida." << endl;
            return;
    }

    if (nuevaX < 0 || nuevaX >= ancho || nuevaY < 0 || nuevaY >= alto || nuevaZ < 0 || nuevaZ >= profundidad) {
        cout << "Movimiento fuera de los limites del tablero" << endl;
        return;
    }

    Node<Casilla> *nodoDestino = tableroDeJuego->obtenerNodo(nuevaX, nuevaY, nuevaZ);
    if (!nodoDestino) {
        cout << "Nodo no encontrado" << endl;
        return;
    }
    Casilla &casillaDestino = nodoDestino->getData();
    char tipoCasilla = casillaDestino.getRepresentacion();

    switch (tipoCasilla) {
        case 'E': { // Enemigo
            Enemigo& enemigo = static_cast<Enemigo&>(casillaDestino);
            jugador.setVida(jugador.getVida() - enemigo.getVida());
            cout << "¡Has encontrado un enemigo! Pierdes " << enemigo.getVida() << " puntos de vida." << endl;
            break;
        }
        case 'T': { // Trampa
            Trampa& trampa = static_cast<Trampa&>(casillaDestino);
            jugador.setVida(jugador.getVida() - trampa.getDano());
            cout << "¡Has caído en una trampa! Pierdes " << trampa.getDano() << " puntos de vida." << endl;
            break;
        }
        case 'P': { // Pócima
            Pocima& pocima = static_cast<Pocima&>(casillaDestino);
            jugador.setVida(jugador.getVida() + pocima.getCuracion());
            cout << "¡Has encontrado una pócima! Recuperas " << pocima.getCuracion() << " puntos de vida." << endl;
            break;
        }
        case 'C': { // Pista
            int distancia = abs(nuevaX - tesoroX) + abs(nuevaY - tesoroY) + abs(nuevaZ - tesoroZ);
            if (distancia > 3) cout << "Frío." << endl;
            else if (distancia == 2 || distancia == 3) cout << "Tibio." << endl;
            else cout << "Caliente." << endl;
            break;
        }
        case '$': { // Tesoro
            tesoroEncontrado = true;
            cout << "¡Has encontrado el tesoro! ¡Felicidades!" << endl;
            return;
        }
        case '~': { // Casilla vacía
            cout << "No hay nada en esta casilla." << endl;
            break;
        }
        default: {
            cout << "¡Error! Tipo de casilla desconocido: " << tipoCasilla << endl;
            break;
        }
    }
    Casilla casillaVacia;
    tableroDeJuego->insertar(jugador.getPosicionX(), jugador.getPosicionY(), jugador.getPosicionZ(), casillaVacia);
    jugador.setPosicionX(nuevaX);
    jugador.setPosicionY(nuevaY);
    jugador.setPosicionZ(nuevaZ);
    tableroDeJuego->insertar(nuevaX, nuevaY, nuevaZ, jugador);

    if (jugador.getVida() <= 0) {
        jugadorEliminado = true;
        cout << "Tu vida ha llegado a 0. Has perdido la partida." << endl;
    }
}
