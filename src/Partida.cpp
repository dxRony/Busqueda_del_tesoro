//
// Created by ronyrojas on 27/03/25.
//
#include "../include/Partida.h"
#include "../include/Pista.h"
#include "../include/Pocima.h"
#include "../include/Tesoro.h"

Partida::Partida() : jugador("constructor de partida sin parametros") {
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
    enemigosPartida = new BST<int>();
    trampasPartida = new BST<int>();
    registroTrayectoria = new LinkedList<string>();
    registroEnemigosYTrampas = new LinkedList<string>();
    registroPistas = new LinkedList<string>();
    cout << "Generando tablero..." << endl;
    this->generarTablero();
    cout << "Tablero generado." << endl;
}

void Partida::iniciarPartida() {
    tiempoPartida = time(nullptr);                                                     //1
    while (!jugadorEliminado && !tesoroEncontrado && !partidaAbandonada) {                  //n
        tableroDeJuego->imprimir();                                                         //n
        realizarTurno(jugador.mostrarOpcionesTurno());                           //n
    }
    jugador.setTiempoJugado(time(nullptr) - tiempoPartida);                            //1
    cout << jugador.getNombre() << ", tus estadisticas finales fueron: " << endl;           //1
    mostrarEstadisticas();                                                                  //1
    cout << "Actualizando reportes..." << endl;                                             //1
}

void Partida::generarTablero() {
    tesoroX = rand() % ancho;                                                                                           //1
    tesoroY = rand() % alto;                                                                                            //1
    tesoroZ = rand() % profundidad;                                                                                     //1
    Tesoro tesoro;                                                                                                      //1
    tesoro.setPosicionX(tesoroX);                                                                              //1
    tesoro.setPosicionY(tesoroY);                                                                              //1
    tesoro.setPosicionZ(tesoroZ);                                                                              //1
    string ubicacionTesoro = "Tesoro ubicado en: (" + to_string(tesoroX) + ", " + to_string(tesoroY) + ", " +
                             to_string(tesoroZ) + ")";                                                              //1
    registroTrayectoria->insertarFinal(ubicacionTesoro);                                                           //1
    tableroDeJuego->insertar(tesoroX, tesoroY, tesoroZ, tesoro);                                          //1

    int jugadorX, jugadorY, jugadorZ;                                                                                   //1
    do {
        //evitando que se coloque al jugador en el mismo lugar que el tesoro
        jugadorX = rand() % ancho;                                                                                      //n
        jugadorY = rand() % alto;                                                                                       //n
        jugadorZ = rand() % profundidad;                                                                                //n
    } while (jugadorX == tesoroX && jugadorY == tesoroY && jugadorZ == tesoroZ);                                        //n
    jugador.setPosicionX(jugadorX);                                                                            //1
    jugador.setPosicionY(jugadorY);                                                                            //1
    jugador.setPosicionZ(jugadorZ);                                                                            //1
    tableroDeJuego->insertar(jugadorX, jugadorY, jugadorZ, jugador);                                      //1

    for (int z = 0; z < profundidad; z++) {                                                                             //n
        for (int y = 0; y < alto; y++) {                                                                                //n^2
            for (int x = 0; x < ancho; x++) {                                                                           //n^3
                if ((x == tesoroX && y == tesoroY && z == tesoroZ)
                    || x == jugadorX && y == jugadorY && z == jugadorZ) {                                               //n^3
                    //ignorando la posicion del tesoro y jugador
                    continue;                                                                                           //n^3
                }
                int random = rand() % 100;                                                                              //n^3
                if (random < 15) {                                                                                      //n^3
                    //15% de generacion para enemigos
                    Enemigo enemigoGenerado;                                                                            //n^3
                    enemigoGenerado.setPosicionX(x);                                                           //n^3
                    enemigoGenerado.setPosicionY(y);                                                           //n^3
                    enemigoGenerado.setPosicionZ(z);                                                          //n^3
                    string ubicacionEnemigo = to_string(x)+ to_string(y) + to_string(z);                   //n^3
                    enemigoGenerado.setUbicacion(stoi(ubicacionEnemigo));                                           //n^3
                    enemigoGenerado.setEfecto(enemigoGenerado.getVida());                                               //n^3
                    tableroDeJuego->insertar(x, y, z, enemigoGenerado);                                           //n^3
                    //enemigosPartida->insertar(enemigoGenerado.getUbicacion());                                     //n^3
                } else if (random < 35) {                                                                               //n^3
                    //20% de generacion para trampas
                    Trampa trampaGenerada;                                                                              //n^3
                    trampaGenerada.setPosicionX(x);                                                            //n^3
                    trampaGenerada.setPosicionY(y);                                                            //n^3
                    trampaGenerada.setPosicionZ(z);                                                            //n^3
                    string ubicacionTrampa = to_string(z) + to_string(y) + to_string(x);                   //n^3
                    trampaGenerada.setUbicacion(stoi(ubicacionTrampa));                                             //n^3
                    trampaGenerada.setEfecto(trampaGenerada.getDano());                                                 //n^3
                    tableroDeJuego->insertar(x, y, z, trampaGenerada);                                            //n^3
                    //trampasPartida->insertar(trampaGenerada.getUbicacion());                                       //n^3
                } else if (random < 60) {                                                                               //n^3
                    //25% de generacion para pocimas
                    Pocima pocimaGenerada;                                                                              //n^3
                    pocimaGenerada.setPosicionX(x);                                                            //n^3
                    pocimaGenerada.setPosicionY(y);                                                            //n^3
                    pocimaGenerada.setPosicionZ(z);                                                            //n^3
                    pocimaGenerada.setEfecto(pocimaGenerada.getCuracion());                                             //n^3
                    tableroDeJuego->insertar(x, y, z, pocimaGenerada);                                             //n^3
                } else {
                    //40% de generacion para pistas
                    Pista pistaGenerada;                                                                                //n^3
                    pistaGenerada.setPosicionX(x);                                                             //n^3
                    pistaGenerada.setPosicionY(y);                                                             //n^3
                    pistaGenerada.setPosicionZ(z);                                                             //n^3
                    tableroDeJuego->insertar(x, y, z, pistaGenerada);                                              //n^3
                }
            }
        }
    }
}

void Partida::realizarTurno(int opcionTurno) {
    switch (opcionTurno) {                                                  //1
        case 1: {                                                           //1
            cout << "Ingresa la direccion del movimiento:" << endl;         //1
            cout << "1. Arriba" << endl;                                    //1
            cout << "2. Abajo" << endl;                                     //1
            cout << "3. Derecha" << endl;                                   //1
            cout << "4. Izquierda" << endl;                                 //1
            cout << "5. Adelante" << endl;                                  //1
            cout << "6. Atras" << endl;                                     //1
            int direccion;                                                  //1
            cin >> direccion;                                               //1
            moverJugador(direccion);                                        //1
            break;                                                          //1
        }
        case 2: {                                                           //1
            cout << "Tus estadisticas son:" << endl;                        //1
            mostrarEstadisticas();                                          //1
            break;                                                          //1
        }
        case 3: {                                                           //1
            cout << "Abandonando la partida..." << endl;                    //1
            partidaAbandonada = true;                                       //1
            break;                                                          //1
        }
        default: {                                                          //1
            cout << "Ingresa una opcion valida";                            //1
            break;                                                          //1
        }
    }
}

void Partida::moverJugador(int direccion) {
    int nuevoX = jugador.getPosicionX();                                                                                    //1
    int nuevoY = jugador.getPosicionY();                                                                                    //1
    int nuevoZ = jugador.getPosicionZ();                                                                                    //1

    string direccionMovimiento = "";                                                                                        //1
    switch (direccion) {                                                                                                    //1
        case 1:                                                                                                             //1
            //moviendo arriba
            nuevoY++;                                                                                                       //1
            direccionMovimiento = "arriba";                                                                                 //1
            break;                                                                                                          //1
        case 2:                                                                                                             //1
            //moviendo abajo
            nuevoY--;                                                                                                       //1
            direccionMovimiento = "abajo";                                                                                  //1
            break;                                                                                                          //1
        case 3:                                                                                                             //1
            //moviendo derecha
            nuevoX++;                                                                                                       //1
            direccionMovimiento = "derecha";                                                                                //1
            break;                                                                                                          //1
        case 4:                                                                                                             //1
            //moviendo izquierda
            nuevoX--;                                                                                                       //1
            direccionMovimiento = "izquierda";                                                                              //1
            break;                                                                                                          //1
        case 5:                                                                                                             //1
            //moviendo adelante
            nuevoZ++;                                                                                                       //1
            direccionMovimiento = "adelante";                                                                               //1
            break;                                                                                                          //1
        case 6:                                                                                                             //1
            //moviendo atras
            nuevoZ--;                                                                                                       //1
            direccionMovimiento = "atras";                                                                                  //1
            break;                                                                                                          //1
        default: cout << "direccion incorrecta" << endl;                                                                    //1
            return;                                                                                                         //1
    }

    if (nuevoX < 0 || nuevoX >= ancho || nuevoY < 0 || nuevoY >= alto || nuevoZ < 0 || nuevoZ >= profundidad) {             //1
        cout << "Movimiento fuera de los limites del tablero" << endl;                                                      //1
        return;                                                                                                             //1
    }

    Node<Casilla> *nodoDestino = tableroDeJuego->obtenerNodo(nuevoX, nuevoY, nuevoZ);                              //1
    if (!nodoDestino) {                                                                                                     //1
        cout << "Nodo no encontrado" << endl;                                                                               //1
        return;                                                                                                             //1
    }
    Casilla &casillaDestino = nodoDestino->getData();                                                                       //1
    string casillaEncontrada = "";                                                                                          //1

    string tipoCasilla = casillaDestino.getTipoCasilla();                                                                   //1
    int tipoCasillaInt =0;                                                                                                  //1
    if (tipoCasilla == "Enemigo"){                                                                                          //1
        tipoCasillaInt = 1;                                                                                                 //1
    } else if (tipoCasilla== "Trampa"){                                                                                     //1
        tipoCasillaInt = 2;                                                                                                 //1
    } else if (tipoCasilla == "Pocima"){                                                                                    //1
        tipoCasillaInt = 3;                                                                                                 //1
    } else if (tipoCasilla == "Pista"){                                                                                     //1
        tipoCasillaInt = 4;                                                                                                 //1
    } else if (tipoCasilla == "Tesoro"){                                                                                    //1
        tipoCasillaInt = 5;                                                                                                 //1
    } else if (tipoCasilla == "Vacia"){                                                                                     //1
        tipoCasillaInt = 6;                                                                                                 //1
    }
    switch (tipoCasillaInt) {                                                                                               //1
        case 1 :{                                                                                                           //1
            jugador.setVida(jugador.getVida() - casillaDestino.getEfecto());                                                //1
            jugador.setPuntos(jugador.getPuntos() + 15);                                                                    //1
            cout << "Encontraste un enemigo D:!! pierdes " << casillaDestino.getEfecto() << " puntos de vida." << endl;     //1
            cout << "Y ganas 15 puntos!!!" << endl;                                                                         //1
            string mensaje = "Se ha encontrado un enemigo y ha realizado: " + to_string(casillaDestino.getEfecto()) +
                             " de dano al jugador, en la posicion: (" + to_string(casillaDestino.getPosicionX()) + ", "
                             + to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                                 casillaDestino.getPosicionZ()) + ")";                                                  //1
            registroEnemigosYTrampas->insertarFinal(mensaje);                                                          //1
            enemigosPartida->insertar(casillaDestino.getUbicacion());                                                  //1
            break;                                                                                                          //1
        }
        case 2: {                                                                                                           //1
            jugador.setVida(jugador.getVida() - casillaDestino.getEfecto());                                                //1
            jugador.setPuntos(jugador.getPuntos() + 10);                                                                    //1
            cout << "Caiste en una trampa D:!! pierdes " << casillaDestino.getEfecto() << " puntos de vida." << endl;       //1
            cout << "Y ganas 10 puntos!!!" << endl;                                                                         //1
            string mensaje = "Se ha encontrado una trampa y ha realizado: " + to_string(casillaDestino.getEfecto()) +
                             " de dano al jugador, en la posicion: (" + to_string(casillaDestino.getPosicionX()) + ", "
                             + to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                                 casillaDestino.getPosicionZ()) + ")";                                                  //1
            registroEnemigosYTrampas->insertarFinal(mensaje);                                                          //1
            trampasPartida->insertar(casillaDestino.getUbicacion());                                                   //1
            break;                                                                                                          //1
        }
        case 3: {                                                                                                           //1
            jugador.setVida(jugador.getVida() + casillaDestino.getEfecto());                                                //1
            cout << "Encontraste una pocima :D!! recuperas " << casillaDestino.getEfecto() << " puntos de vida." <<
                    endl;                                                                                                   //1
            break;                                                                                                          //1
        }
        case 4: {                                                                                                           //1
            int distanciaX = nuevoX - tesoroX;                                                                              //1
            int distanciaY = nuevoY - tesoroY;                                                                              //1
            int distanciaZ = nuevoZ - tesoroZ;                                                                              //1
            //convirtiendo distancia a valores positivos                                                                    //1
            if (distanciaX < 0) {                                                                                           //1
                distanciaX *= -1;                                                                                           //1
            }
            if (distanciaY < 0) {                                                                                           //1
                distanciaY *= -1;                                                                                           //1
            }
            if (distanciaZ < 0) {                                                                                           //1
                distanciaZ *= -1;                                                                                           //1
            }
            //calculando distancia de posicion actual a la del tesoro
            int distancia = distanciaX + distanciaY + distanciaZ;                                                           //1

            cout << "Encontraste una Pista :D, esta dice:" << endl;
            if (distancia > 3) {                                                                                            //1
                cout << "Frio, sigue buscando." << endl;                                                                    //1
            } else if (distancia >= 2) {                                                                                    //1
                // >= 2 cubre 2 y 3
                cout << "Tibio, estas a las afueras del tesoro." << endl;                                                   //1
            } else {                                                                                                        //1
                cout << "Caliente, da un paso mas y encontraras al tesoro." << endl;                                        //1
            }
            string mensaje = "Se ha encontrado una pista y ha indicado que el tesoro esta a: " + to_string(distancia) +
                             " pasos de distancia del jugador, en la posicion: (" +
                             to_string(casillaDestino.getPosicionX()) + ", " + to_string(casillaDestino.getPosicionY())
                             + ", " + to_string(casillaDestino.getPosicionZ()) + ")";                                   //1
            registroPistas->insertarFinal(mensaje);                                                                    //1
            break;                                                                                                          //1
        }
        case 5: {                                                                                                           //1
            tesoroEncontrado = true;                                                                                        //1
            jugador.setEncontroTesoro(true);
            jugador.setPuntos(jugador.getPuntos() + 100);                                                                   //1
            cout << "Has encontrado el tesoro, felicidades!!!" << endl;                                                     //1
            jugador.setMovimientos(jugador.getMovimientos() + 1);                                                           //1
            casillaEncontrada = " (" + to_string(casillaDestino.getPosicionX()) + ", " +
                                to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                                    casillaDestino.getPosicionZ()) + ")";                                               //1
            string movimientoFinal = "El tesoro fue encontrado con un movimiento hacia: " + direccionMovimiento +
                                     ", en la posicion" +
                                     casillaEncontrada + ", otorgandole al jugador: 100 pts!!!";                            //1
            registroTrayectoria->insertarFinal(movimientoFinal);                                                       //1
            return;                                                                                                         //1
        }
        case 6: {                                                                                                           //1
            cout << "Estas a salvo en esta casilla, no hay nada." << endl;                                                  //1
            break;                                                                                                          //1
        }
        default: {                                                                                                          //1
            cout << "errorrrrrrr .-." << endl;                                                                              //1
            break;                                                                                                          //1
        }
    }
    Casilla casillaVacia;                                                                                                   //1
    casillaVacia.setTipoCasilla("Vacia");
    tableroDeJuego->insertar(jugador.getPosicionX(), jugador.getPosicionY(), jugador.getPosicionZ(), casillaVacia); //1
    jugador.setPosicionX(nuevoX);                                                                                  //1
    jugador.setPosicionY(nuevoY);                                                                                  //1
    jugador.setPosicionZ(nuevoZ);                                                                                  //1
    tableroDeJuego->insertar(nuevoX, nuevoY, nuevoZ, jugador);                                                //1
    if (jugador.getVida() <= 0) {                                                                                           //1
        jugador.setVida(0);                                                                                                 //1
        jugadorEliminado = true;                                                                                            //1
        cout << "Tu vida ha llegado a 0, has perdido la partida :(" << endl;                                                //1
    } else {                                                                                                                //1
        cout << "Aun sigues con vida, continua explorando..." << endl;                                                      //1
    }
    jugador.setMovimientos(jugador.getMovimientos() + 1);                                                                   //1

    string trayectoria = "Movimiento en direccion hacia: " + direccionMovimiento + ", a la posicion: " + "(" +
                         to_string(casillaDestino.getPosicionX()) + ", " +
                         to_string(casillaDestino.getPosicionY()) + ", " + to_string(
                             casillaDestino.getPosicionZ()) + ")";                                                      //1
    registroTrayectoria->insertarFinal(trayectoria);                                                                   //1
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

bool Partida::isTesoroEncontrado() {
    return tesoroEncontrado;
}

ostream &operator<<(ostream &os, Partida &partida) {
    os << "Jugador de la partida: " << partida.getJugador().getNombre();
    return os;
}

BST<int> *Partida::getTrampasPartida() const {
    return trampasPartida;
}

void Partida::setTrampasPartida(BST<int> *trampasPartida) {
    Partida::trampasPartida = trampasPartida;
}

BST<int> *Partida::getEnemigosPartida() const {
    return enemigosPartida;
}

void Partida::setEnemigosPartida(BST<int> *enemigosPartida) {
    Partida::enemigosPartida = enemigosPartida;
}


