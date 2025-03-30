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
    cout << "Tablero generado." << endl;
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
        tableroDeJuego->imprimir();
        realizarTurno(jugador.mostrarOpcionesTurno());
    }
    cout << jugador.getNombre() << ", tus estadisticas finales fueron: " << endl;
    mostrarEstadisticas();
    cout << "Actualizando reportes de la partida..." << endl;
}

void Partida::generarTablero() {
    tesoroX = rand() % ancho;
    tesoroY = rand() % alto;
    tesoroZ = rand() % profundidad;
    Tesoro tesoro;
    tesoro.setPosicionX(tesoroX);
    tesoro.setPosicionY(tesoroY);
    tesoro.setPosicionZ(tesoroZ);
    //colocando aleatoriamente al tesoro
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
                    enemigoGenerado.setEfecto(enemigoGenerado.getVida());
                    tableroDeJuego->insertar(x, y, z, enemigoGenerado);
                    enemigosPartida->insertar(enemigoGenerado);
                } else if (random < 35) {
                    //20% de generacion para trampas
                    Trampa trampaGenerada;
                    trampaGenerada.setPosicionX(x);
                    trampaGenerada.setPosicionY(y);
                    trampaGenerada.setPosicionZ(z);
                    trampaGenerada.setEfecto(trampaGenerada.getDano());
                    tableroDeJuego->insertar(x, y, z, trampaGenerada);
                    trampasPartida->insertar(trampaGenerada);
                } else if (random < 60) {
                    //25% de generacion para pocimas
                    Pocima pocimaGenerada;
                    pocimaGenerada.setPosicionX(x);
                    pocimaGenerada.setPosicionY(y);
                    pocimaGenerada.setPosicionZ(z);
                    pocimaGenerada.setEfecto(pocimaGenerada.getCuracion());
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
            mostrarEstadisticas();
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
    int nuevoX = jugador.getPosicionX();
    int nuevoY = jugador.getPosicionY();
    int nuevoZ = jugador.getPosicionZ();

    switch (direccion) {
        case 1:
            //moviendo arriba
            nuevoY++;
            break;
        case 2:
            //moviendo abajo
            nuevoY--;
            break;
        case 3:
            //moviendo derecha
            nuevoX++;
            break;
        case 4:
            //moviendo izquierda
            nuevoX--;
            break;
        case 5:
            //moviendo adelante
            nuevoZ++;
            break;
        case 6:
            //moviendo atras
            nuevoZ--;
            break;
        default: cout << "Dirección no válida." << endl;
            return;
    }

    if (nuevoX < 0 || nuevoX >= ancho || nuevoY < 0 || nuevoY >= alto || nuevoZ < 0 || nuevoZ >= profundidad) {
        cout << "Movimiento fuera de los limites del tablero" << endl;
        return;
    }

    Node<Casilla> *nodoDestino = tableroDeJuego->obtenerNodo(nuevoX, nuevoY, nuevoZ);
    if (!nodoDestino) {
        cout << "Nodo no encontrado" << endl;
        return;
    }
    Casilla &casillaDestino = nodoDestino->getData();

    switch (casillaDestino.getRepresentacion()) {
        case 'E': {
            jugador.setVida(jugador.getVida() - casillaDestino.getEfecto());
            jugador.setPuntos(jugador.getPuntos() + 15);
            cout << "Has encontrado un enemigo D:!! pierdes " << casillaDestino.getEfecto() << " puntos de vida." <<
                    endl;
            break;
        }
        case 'T': {
            jugador.setVida(jugador.getVida() - casillaDestino.getEfecto());
            jugador.setPuntos(jugador.getPuntos() + 10);
            cout << "Has caido en una trampa D:!! pierdes " << casillaDestino.getEfecto() << " puntos de vida." << endl;
            break;
        }
        case 'P': {
            jugador.setVida(jugador.getVida() + casillaDestino.getEfecto());
            cout << "has encontrado una pocima :D!! recuperas " << casillaDestino.getEfecto() << " puntos de vida." <<
                    endl;
            break;
        }
        case 'C': {
            int diffX = nuevoX - tesoroX;
            int diffY = nuevoY - tesoroY;
            int diffZ = nuevoZ - tesoroZ;

            if (diffX < 0) {
                diffX *= -1;
            }
            if (diffY < 0) {
                diffY *= -1;
            }
            if (diffZ < 0) {
                diffZ *= -1;
            }
            //calculando distancia de poscion actual a la del tesoro
            int distancia = diffX + diffY + diffZ;

            if (distancia > 3) {
                cout << "Frio, sigue buscando." << endl;
            } else if (distancia >= 2) {
                // >= 2 cubre 2 y 3
                cout << "Tibio, estas a las afueras del tesoro." << endl;
            } else {
                cout << "Caliente, da un paso mas y encontraras al tesoro." << endl;
            }
            break;
        }
        case '$': {
            tesoroEncontrado = true;
            jugador.setPuntos(jugador.getPuntos() + 100);
            cout << "Has encontrado el tesoro, felicidades!!!" << endl;
            jugador.setMovimientos(jugador.getMovimientos() + 1);
            return;
        }
        case '~': {
            cout << "Estas a salvo en esta casilla, no hay nada." << endl;
            break;
        }
        default: {
            cout << "errorrrrrrr .-." << endl;
            break;
        }
    }
    Casilla casillaVacia;
    tableroDeJuego->insertar(jugador.getPosicionX(), jugador.getPosicionY(), jugador.getPosicionZ(), casillaVacia);
    jugador.setPosicionX(nuevoX);
    jugador.setPosicionY(nuevoY);
    jugador.setPosicionZ(nuevoZ);
    tableroDeJuego->insertar(nuevoX, nuevoY, nuevoZ, jugador);
    if (jugador.getVida() <= 0) {
        jugadorEliminado = true;
        cout << "Tu vida ha llegado a 0, has perdido la partida :(" << endl;
    } else {
        cout << "Aun sigues con vida, continua explorando..." << endl;
    }
    jugador.setMovimientos(jugador.getMovimientos() + 1);
}

void Partida::mostrarEstadisticas() {
    cout << "Vida: " << jugador.getVida() << endl;
    cout << "Puntos: " << jugador.getPuntos() << endl;
    cout << "Movimientos: " << jugador.getMovimientos() << endl;
    cout << "Tiempo Jugado: " << jugador.getTiempoJugado() << endl;
    cout << "Ubicacion: (" << jugador.getPosicionX() << ", " << jugador.getPosicionY() << ", " << jugador.getPosicionZ()
            << ")" << endl;
}
