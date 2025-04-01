//
// Created by ronyrojas on 27/03/25.
//
#include "../include/Partida.h"
#include "../include/Pista.h"
#include "../include/Pocima.h"
#include "../include/Tesoro.h"
#include "../include/Reporte.h"

Partida::Partida() : jugador("jugador en partida sin parametros") {
    ancho = alto = profundidad = 0;
    jugadorEliminado = false;
    tesoroEncontrado = false;
    partidaAbandonada = false;
    tiempoPartida = time(nullptr);

    tableroDeJuego = nullptr;
    enemigosPartida = new BST<Enemigo>();
    trampasPartida = new BST<Trampa>();
    registroTrayectoria = new LinkedList<string>();
    registroEnemigosYTrampas = new LinkedList<string>();
    registroPistas = new LinkedList<string>();
}

Partida::Partida(string nombreJugador, int ancho, int alto, int profundidad): jugador(nombreJugador) {
    this->ancho = ancho;
    this->alto = alto;
    this->profundidad = profundidad;

    jugadorEliminado = false;
    tesoroEncontrado = false;
    partidaAbandonada = false;
    tiempoPartida = time(nullptr);

    tableroDeJuego = new ThreeDimensionalMatrix<Casilla>(ancho, alto, profundidad);
    enemigosPartida = new BST<Enemigo>();
    trampasPartida = new BST<Trampa>();
    registroTrayectoria = new LinkedList<string>();
    registroEnemigosYTrampas = new LinkedList<string>();
    registroPistas = new LinkedList<string>();
    cout << "Generando tablero..." << endl;
    this->generarTablero();
    cout << "Tablero generado." << endl;
}

void Partida::iniciarPartida() {
    tiempoPartida = time(nullptr);
    while (!jugadorEliminado && !tesoroEncontrado && !partidaAbandonada) {
        tableroDeJuego->imprimir();
        realizarTurno(jugador.mostrarOpcionesTurno());
    }
    jugador.setTiempoJugado(time(nullptr) - tiempoPartida);
    cout << jugador.getNombre() << ", tus estadisticas finales fueron: " << endl;
    mostrarEstadisticas();
    cout << "Actualizando reportes..." << endl;
}

void Partida::generarTablero() {
    tesoroX = rand() % ancho;
    tesoroY = rand() % alto;
    tesoroZ = rand() % profundidad;
    Tesoro tesoro;
    tesoro.setPosicionX(tesoroX);
    tesoro.setPosicionY(tesoroY);
    tesoro.setPosicionZ(tesoroZ);
    string ubicacionTesoro = "Tesoro ubicado en: (" + to_string(tesoroX) + ", " + to_string(tesoroY) + ", " +
                             to_string(tesoroZ) + ")";
    registroTrayectoria->insertarFinal(ubicacionTesoro);
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

    string direccionMovimiento = "";
    switch (direccion) {
        case 1:
            //moviendo arriba
            nuevoY++;
            direccionMovimiento = "arriba";
            break;
        case 2:
            //moviendo abajo
            nuevoY--;
            direccionMovimiento = "abajo";
            break;
        case 3:
            //moviendo derecha
            nuevoX++;
            direccionMovimiento = "derecha";
            break;
        case 4:
            //moviendo izquierda
            nuevoX--;
            direccionMovimiento = "izquierda";
            break;
        case 5:
            //moviendo adelante
            nuevoZ++;
            direccionMovimiento = "adelante";
            break;
        case 6:
            //moviendo atras
            nuevoZ--;
            direccionMovimiento = "atras";
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
    string casillaEncontrada = "";

    switch (casillaDestino.getRepresentacion()) {
        case 'E': {
            jugador.setVida(jugador.getVida() - casillaDestino.getEfecto());
            jugador.setPuntos(jugador.getPuntos() + 15);
            cout << "Has encontrado un enemigo D:!! pierdes " << casillaDestino.getEfecto() << " puntos de vida." <<
                    endl;
            string mensaje = "Se ha encontrado un enemigo y ha realizado: " + to_string(casillaDestino.getEfecto()) +
                             " de dano al jugador, en la posicion: (" + to_string(casillaDestino.getPosicionX()) + ", "
                             +
                             to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                                 casillaDestino.getPosicionZ()) + ")";
            registroEnemigosYTrampas->insertarFinal(mensaje);
            break;
        }
        case 'T': {
            jugador.setVida(jugador.getVida() - casillaDestino.getEfecto());
            jugador.setPuntos(jugador.getPuntos() + 10);
            cout << "Has caido en una trampa D:!! pierdes " << casillaDestino.getEfecto() << " puntos de vida." << endl;
            string mensaje = "Se ha encontrado una trampa y ha realizado: " + to_string(casillaDestino.getEfecto()) +
                             " de dano al jugador, en la posicion: (" + to_string(casillaDestino.getPosicionX()) + ", "
                             +
                             to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                                 casillaDestino.getPosicionZ()) + ")";
            registroEnemigosYTrampas->insertarFinal(mensaje);
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
            string mensaje = "Se ha encontrado una pista y ha indicado que el tesoro esta a: " + to_string(distancia) +
                             " pasos de distancia del jugador, en la posicion: (" + to_string(
                                 casillaDestino.getPosicionX()) +
                             ", "
                             +
                             to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                                 casillaDestino.getPosicionZ()) + ")";
            registroPistas->insertarFinal(mensaje);
            break;
        }
        case '$': {
            tesoroEncontrado = true;
            jugador.setPuntos(jugador.getPuntos() + 100);
            cout << "Has encontrado el tesoro, felicidades!!!" << endl;
            jugador.setMovimientos(jugador.getMovimientos() + 1);
            casillaEncontrada = " (" + to_string(casillaDestino.getPosicionX()) + ", " +
                                to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                                    casillaDestino.getPosicionZ()) + ")";
            string movimientoFinal = "El tesoro fue encontrado con un movimiento hacia: " + direccionMovimiento +
                                     ", en la posicion" +
                                     casillaEncontrada + ", otorgandole al jugador: 100 pts!!!";
            registroTrayectoria->insertarFinal(movimientoFinal);
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
    /*
    casillaEncontrada += "(" + to_string(casillaDestino.getPosicionX()) + ", " +
            to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                casillaDestino.getPosicionZ()) + ")";*/
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

    string trayectoria = "Movimiento en direccion hacia: " + direccionMovimiento + ", a la posicion: " + "(" +
                         to_string(casillaDestino.getPosicionX()) + ", " +
                         to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                             casillaDestino.getPosicionZ()) + ")";
    registroTrayectoria->insertarFinal(trayectoria);
}

void Partida::mostrarEstadisticas() {
    cout << "Vida: " << jugador.getVida() << endl;
    cout << "Puntos: " << jugador.getPuntos() << endl;
    cout << "Movimientos: " << jugador.getMovimientos() << endl;
    cout << "Tiempo Jugado: " << jugador.getTiempoJugado() << " s" << endl;
    cout << "Ubicacion: (" << jugador.getPosicionX() << ", " << jugador.getPosicionY() << ", " << jugador.getPosicionZ()
            << ")" << endl;
}

int Partida::getAncho() {
    return ancho;
}

int Partida::getAlto() {
    return alto;
}

int Partida::getProfundidad() {
    return profundidad;
}

Jugador Partida::getJugador() {
    return jugador;
}

Partida *Partida::getPartida() {
    return this;
}

LinkedList<string> *Partida::getRegistroTrayectoria() {
    return registroTrayectoria;
}

LinkedList<string> *Partida::getRegistroEnemigosYTrampas() {
    return registroEnemigosYTrampas;
}

LinkedList<string> *Partida::getRegistroPistas() {
    return registroPistas;
}

ostream &operator<<(ostream &os, Partida &partida) {
    os << "Jugador de la partida: " << partida.getJugador().getNombre();
    return os;
}
