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

Partida::~Partida() {
    //delete tableroDeJuego;
    //delete enemigosPartida;
    //delete trampasPartida;
    //delete registroTrayectoria;
    //delete registroEnemigosYTrampas;
    //delete registroPistas;
}

void Partida::iniciarPartida() {
    tiempoPartida = time(nullptr);                                                  //1
    while (!jugadorEliminado && !tesoroEncontrado && !partidaAbandonada) {               //1
        tableroDeJuego->imprimir();                                                      //n
        realizarTurno(jugador.mostrarOpcionesTurno());                                   //n
    }
    jugador.setTiempoJugado(time(nullptr) - tiempoPartida);                         //1
    cout << jugador.getNombre() << ", tus estadisticas finales fueron: " << endl;        //1
    mostrarEstadisticas();                                                               //1
    cout << "Actualizando reportes..." << endl;                                          //1
}

void Partida::generarTablero() {
    this->generarTesoro();          //1
    this->generarJugador();         //1
    this->generarObjetosTablero();  //1
}

void Partida::generarTesoro() {
    tesoroX = rand() % ancho;                                                           //1
    tesoroY = rand() % alto;                                                            //1
    tesoroZ = rand() % profundidad;                                                     //1

    Tesoro tesoro;                                                                      //1
    tesoro.setPosicionX(tesoroX);                                                       //1
    tesoro.setPosicionY(tesoroY);                                                       //1
    tesoro.setPosicionZ(tesoroZ);                                                       //1

    string ubicacionTesoro = "Tesoro ubicado en: (" + to_string(tesoroX) + ", " +
                             to_string(tesoroY) + ", " + to_string(tesoroZ) + ")";      //1
    registroTrayectoria->insertar(ubicacionTesoro);                                     //1
    tableroDeJuego->insertar(tesoroX, tesoroY, tesoroZ, tesoro);                     //1
}

void Partida::generarJugador() {
    int jugadorX, jugadorY, jugadorZ;                                               //1
    do {
        jugadorX = rand() % ancho;                                                  //n
        jugadorY = rand() % alto;                                                   //n
        jugadorZ = rand() % profundidad;                                            //n
    } while (jugadorX == tesoroX && jugadorY == tesoroY && jugadorZ == tesoroZ);    //n

    jugador.setPosicionX(jugadorX);                                                 //1
    jugador.setPosicionY(jugadorY);                                                 //1
    jugador.setPosicionZ(jugadorZ);                                                 //1
    tableroDeJuego->insertar(jugadorX, jugadorY, jugadorZ, jugador);             //1
}

void Partida::generarObjetosTablero() {
    for (int z = 0; z < profundidad; z++) {                                                                             //n
        for (int y = 0; y < alto; y++) {                                                                                //n²
            for (int x = 0; x < ancho; x++) {                                                                           //n³
                if ((x == tesoroX && y == tesoroY && z == tesoroZ) ||                                                   //n³
                    (x == jugador.getPosicionX() && y == jugador.getPosicionY() && z == jugador.getPosicionZ())) {      //n³
                    continue;                                                                                           //n³
                }
                int random = rand() % 100;                                                                              //n³
                if (random < 15) {                                                                                      //n³
                    generarEnemigo(x, y, z);                                                                            //n³
                } else if (random < 35) {                                                                               //n³
                    generarTrampa(x, y, z);                                                                             //n³
                } else if (random < 60) {                                                                               //n³
                    generarPocima(x, y, z);                                                                             //n³
                } else {                                                                                                //n³
                    generarPista(x, y, z);                                                                              //n³
                }
            }
        }
    }
}

void Partida::generarEnemigo(int x, int y, int z) {
    Enemigo enemigoGenerado;                                    //1
    enemigoGenerado.setPosicionX(x);                            //1
    enemigoGenerado.setPosicionY(y);                            //1
    enemigoGenerado.setPosicionZ(z);                            //1
    string ubicacionEnemigo = to_string(x)+ to_string(y) + to_string(z);
    enemigoGenerado.setUbicacion(stoi(ubicacionEnemigo));
    enemigoGenerado.setEfecto(enemigoGenerado.getVida());       //1
    tableroDeJuego->insertar(x, y, z, enemigoGenerado);      //1
}

void Partida::generarTrampa(int x, int y, int z) {
    Trampa trampaGenerada;                                      //1
    trampaGenerada.setPosicionX(x);                             //1
    trampaGenerada.setPosicionY(y);                             //1
    trampaGenerada.setPosicionZ(z);                             //1
    string ubicacionTrampa = to_string(z) + to_string(y) + to_string(x);
    trampaGenerada.setUbicacion(stoi(ubicacionTrampa));
    trampaGenerada.setEfecto(trampaGenerada.getDano());         //1
    tableroDeJuego->insertar(x, y, z, trampaGenerada);       //1
}

void Partida::generarPocima(int x, int y, int z) {
    Pocima pocimaGenerada;                                      //1
    pocimaGenerada.setPosicionX(x);                             //1
    pocimaGenerada.setPosicionY(y);                             //1
    pocimaGenerada.setPosicionZ(z);                             //1
    pocimaGenerada.setEfecto(pocimaGenerada.getCuracion());     //1
    tableroDeJuego->insertar(x, y, z, pocimaGenerada);       //1
}

void Partida::generarPista(int x, int y, int z) {
    Pista pistaGenerada;                                    //1
    pistaGenerada.setPosicionX(x);                          //1
    pistaGenerada.setPosicionY(y);                          //1
    pistaGenerada.setPosicionZ(z);                          //1
    tableroDeJuego->insertar(x, y, z, pistaGenerada);    //1
}

void Partida::realizarTurno(int opcionTurno) {
    switch (opcionTurno) {                                              //1
        case 1: {                                                       //1
            cout << "Ingresa la direccion del movimiento:" << endl;     //1
            cout << "1. Arriba" << endl;                                //1
            cout << "2. Abajo" << endl;                                 //1
            cout << "3. Derecha" << endl;                               //1
            cout << "4. Izquierda" << endl;                             //1
            cout << "5. Adelante" << endl;                              //1
            cout << "6. Atras" << endl;                                 //1
            int direccion;                                              //1
            cin >> direccion;                                           //1
            moverJugador(direccion);                                    //1
            break;                                                      //1
        }
        case 2: {                                                       //1
            cout << "Tus estadisticas son:" << endl;                    //1
            mostrarEstadisticas();                                      //1
            break;                                                      //1
        }
        case 3: {                                                       //1
            cout << "Abandonando la partida..." << endl;                //1
            partidaAbandonada = true;                                   //1
            break;                                                      //1
        }
        default: {                                                      //1
            cout << "Ingresa una opcion valida";                        //1
            break;                                                      //1
        }
    }
}

void Partida::moverJugador(int tipoMovimiento) {
    int nuevoX, nuevoY, nuevoZ;                                                                                     //1
    string direccion;                                                                                               //1
    calcularPosicionMovimiento(tipoMovimiento, nuevoX, nuevoY, nuevoZ, direccion);                      //1

    if (direccion == "invalida") {                                                                                  //1
        return;                                                                                                     //1
    }
    if (nuevoX < 0 || nuevoX >= ancho || nuevoY < 0 || nuevoY >= alto || nuevoZ < 0 || nuevoZ >= profundidad) {     //1
        cout << "Movimiento fuera de los limites del tablero" << endl;                                              //1
        return;                                                                                                     //1
    }

    Node<Casilla>* nodoDestino = tableroDeJuego->obtenerNodo(nuevoX, nuevoY, nuevoZ);                               //1
    if (!nodoDestino) {                                                                                             //1
        cout << "Nodo no encontrado" << endl;                                                                       //1
        return;                                                                                                     //1
    }
    Casilla& casillaDestino = nodoDestino->getData();                                                               //1

    procesarEfectoCasilla(casillaDestino, direccion);                                                            //1

    actualizarPosicionJugador(nuevoX, nuevoY, nuevoZ);                                                              //1
}

void Partida::calcularPosicionMovimiento(int tipoMovimiento, int &nuevoX, int &nuevoY, int &nuevoZ, string &direccion) {
    nuevoX = jugador.getPosicionX();                //1
    nuevoY = jugador.getPosicionY();                //1
    nuevoZ = jugador.getPosicionZ();                //1
    direccion = "";                                 //1

    switch (tipoMovimiento) {                       //1
        case 1: // Arriba                           //1
            nuevoY++;                               //1
            direccion = "arriba";                   //1
            break;                                  //1
        case 2: // Abajo                            //1
            nuevoY--;                               //1
            direccion = "abajo";                    //1
            break;                                  //1
        case 3: // Derecha                          //1
            nuevoX++;                               //1
            direccion = "derecha";                  //1
            break;                                  //1
        case 4: // Izquierda                        //1
            nuevoX--;                               //1
            direccion = "izquierda";                //1
            break;                                  //1
        case 5: // Adelante                         //1
            nuevoZ++;                               //1
            direccion = "adelante";                 //1
            break;                                  //1
        case 6: // Atras                            //1
            nuevoZ--;                               //1
            direccion = "atras";                    //1
            break;                                  //1
        default:                                    //1
            cout << "movimiento incorrecto" << endl;//1
            direccion = "no permitida";             //1
    }
}

void Partida::procesarEfectoCasilla(Casilla &casilla, const string &direccion) {
    const string& tipoCasilla = casilla.getTipoCasilla();                   //1

    if (tipoCasilla == "Enemigo") {                                         //1
        procesarEnemigo(casilla);                                        //1
    } else if (tipoCasilla == "Trampa") {                                   //1
        procesarTrampa(casilla);                                         //1
    } else if (tipoCasilla == "Pocima") {                                   //1
        procesarPocima(casilla);                                         //1
    } else if (tipoCasilla == "Pista") {                                    //1
        procesarPista(casilla);                                          //1
    } else if (tipoCasilla == "Tesoro") {                                   //1
        procesarTesoro(casilla, direccion);                              //1
    } else if (tipoCasilla == "Vacia") {                                    //1
        cout << "Estas a salvo en esta casilla, no hay nada." << endl;      //1
    }
    if (tipoCasilla != "Tesoro") {                                          //1
        registrarMovimiento(casilla, direccion);                            //1
    }

}

void Partida::procesarEnemigo(Casilla &casilla) {
    jugador.setVida(jugador.getVida() - casilla.getEfecto());                                           //1
    jugador.setPuntos(jugador.getPuntos() + 15);                                                        //1
    cout << "Encontraste un enemigo D:!! pierdes " << casilla.getEfecto()
         << " puntos de vida." << endl;                                                                 //1
    cout << "Y ganas 15 puntos!!!" << endl;                                                             //1

    string mensaje = "Se ha encontrado un enemigo y ha realizado: " +
                     to_string(casilla.getEfecto()) + " de daño al jugador, en la posicion: (" +
                     to_string(casilla.getPosicionX()) + ", " +
                     to_string(casilla.getPosicionY()) + ", " +
                     to_string(casilla.getPosicionZ()) + ")";                                       //1

    registroEnemigosYTrampas->insertar(mensaje);                                                        //1
    enemigosPartida->insertar(casilla.getUbicacion());                                             //1
}

void Partida::procesarTrampa(Casilla &casilla) {
    jugador.setVida(jugador.getVida() - casilla.getEfecto());                                           //1
    jugador.setPuntos(jugador.getPuntos() + 10);                                                        //1
    cout << "Caiste en una trampa D:!! pierdes " << casilla.getEfecto()
         << " puntos de vida." << endl;                                                                 //1
    cout << "Y ganas 10 puntos!!!" << endl;                                                             //1

    string mensaje = "Se ha encontrado una trampa y ha realizado: " +
                     to_string(casilla.getEfecto()) + " de daño al jugador, en la posicion: (" +
                     to_string(casilla.getPosicionX()) + ", " +
                     to_string(casilla.getPosicionY()) + ", " +
                     to_string(casilla.getPosicionZ()) + ")";                                       //1

    registroEnemigosYTrampas->insertar(mensaje);                                                        //1
    trampasPartida->insertar(casilla.getUbicacion());                                              //1
}

void Partida::procesarPocima(Casilla &casilla) {
    jugador.setVida(jugador.getVida() + casilla.getEfecto());                   //1
    cout << "Encontraste una pocima :D!! recuperas " << casilla.getEfecto()
         << " puntos de vida." << endl;                                         //1
}

void Partida::procesarPista(Casilla &casilla) {
    int distancia = calcularDistanciaPista(casilla.getPosicionX(),
                                           casilla.getPosicionY(),
                                           casilla.getPosicionZ());          //1
    if (distancia == 1) {
        cout << "Caliente, da un paso mas y encontraras al tesoro." << endl; //1
    } else if (distancia == 2) {                                             //1
        cout << "Tibio, estas a las afueras del tesoro." << endl;            //1
    } else if (distancia > 2) {                                              //1
        cout << "Frio, sigue buscando." << endl;                             //1
    }
    string mensaje = "Se ha encontrado una pista y ha indicado que el tesoro está a: " +
                     to_string(distancia) + " pasos de distancia del jugador, en la posición: (" +
                     to_string(casilla.getPosicionX()) + ", " +
                     to_string(casilla.getPosicionY()) + ", " +
                     to_string(casilla.getPosicionZ()) + ")";            //1

    registroPistas->insertar(mensaje);                                       //1
}

void Partida::procesarTesoro(Casilla &casilla, const string& direccion) {
    tesoroEncontrado = true;                                                                        //1
    jugador.setEncontroTesoro(true);                                                      //1
    jugador.setPuntos(jugador.getPuntos() + 100);                                                   //1
    cout << "¡Has encontrado el tesoro, felicidades!!!" << endl;                                    //1

    string casillaEncontrada = " (" + to_string(casilla.getPosicionX()) + ", " +
                              to_string(casilla.getPosicionY()) + ", " +
                              to_string(casilla.getPosicionZ()) + ")";                          //1

    string movimientoFinal = "El tesoro fue encontrado con un movimiento hacia: " + direccion +
                            ", en la posición" + casillaEncontrada +
                            ", otorgándole al jugador: 100 pts!!!";                                 //1

    registroTrayectoria->insertar(movimientoFinal);                                                 //1
}

void Partida::registrarMovimiento(const Casilla &casilla, const string &direccion) {
    string trayectoria = "Movimiento en dirección hacia: " + direccion +
                         ", a la posición: (" + to_string(casilla.getPosicionX()) +
                         ", " + to_string(casilla.getPosicionY()) + ", " +
                         to_string(casilla.getPosicionZ()) + ")";                       //1

    registroTrayectoria->insertar(trayectoria);                                             //1
}

void Partida::actualizarPosicionJugador(int nuevoX, int nuevoY, int nuevoZ) {
    Casilla casillaVacia;                                               //1
    casillaVacia.setTipoCasilla("Vacia");                            //1
    tableroDeJuego->insertar(jugador.getPosicionX(),
                            jugador.getPosicionY(),
                            jugador.getPosicionZ(),
                            casillaVacia);                           //1

    jugador.setPosicionX(nuevoX);                                       //1
    jugador.setPosicionY(nuevoY);                                       //1
    jugador.setPosicionZ(nuevoZ);                                       //1
    tableroDeJuego->insertar(nuevoX, nuevoY, nuevoZ, jugador);       //1

    jugador.setMovimientos(jugador.getMovimientos() + 1);               //1

    if (jugador.getVida() <= 0) {                                       //1
        jugador.setVida(0);                                             //1
        jugadorEliminado = true;                                        //1
        cout << "Tu vida ha llegado a 0, has perdido la partida :(" << endl; //1
    } else {                                                                 //1
        cout << "aun sigues con vida, continua explorando..." << endl;       //1
    }
}

void Partida::reemplazarCasillaVacia(int nuevoX, int nuevoY, int nuevoZ) {
    Casilla casillaVacia;                                                                                               //1
    casillaVacia.setTipoCasilla("Vacia");                                                                            //1
    tableroDeJuego->insertar(jugador.getPosicionX(), jugador.getPosicionY(), jugador.getPosicionZ(), casillaVacia);  //1
    jugador.setPosicionX(nuevoX);                                                                                       //1
    jugador.setPosicionY(nuevoY);                                                                                       //1
    jugador.setPosicionZ(nuevoZ);                                                                                       //1
    tableroDeJuego->insertar(nuevoX, nuevoY, nuevoZ, jugador);                                                       //1
    if (jugador.getVida() <= 0) {                                                                                       //1
        jugador.setVida(0);                                                                                             //1
        jugadorEliminado = true;                                                                                        //1
        cout << "Tu vida ha llegado a 0, has perdido la partida :(" << endl;                                            //1
    } else {                                                                                                            //1
        cout << "Aun sigues con vida, continua explorando..." << endl;                                                  //1
    }
    jugador.setMovimientos(jugador.getMovimientos() + 1);                                                               //1
}

int Partida::calcularDistanciaPista(int nuevoX, int nuevoY, int nuevoZ) {
    int distanciaX = nuevoX - tesoroX;                                  //1
    int distanciaY = nuevoY - tesoroY;                                  //1
    int distanciaZ = nuevoZ - tesoroZ;                                  //1
    //convirtiendo distancias a valores positivos (si los son)
    if (distanciaX < 0) {                                               //1
        distanciaX *= -1;                                               //1
    }
    if (distanciaY < 0) {                                               //1
        distanciaY *= -1;                                               //1
    }
    if (distanciaZ < 0) {                                               //1
        distanciaZ *= -1;                                               //1
    }
    //calculando distancia de posicion actual a la del tesoro
    int distancia = distanciaX + distanciaY + distanciaZ;               //1

    cout << "Encontraste una Pista :D, esta dice:" << endl;             //1
    return distancia;                                                   //1
}

void Partida::mostrarEstadisticas() {
    cout << "Vida: " << jugador.getVida() << endl;                                                                       //1
    cout << "Puntos: " << jugador.getPuntos() << endl;                                                                   //1
    cout << "Movimientos: " << jugador.getMovimientos() << endl;                                                         //1
    cout << "Tiempo Jugado: " << jugador.getTiempoJugado() << " s" << endl;                                              //1
    cout << "Ubicacion: (" << jugador.getPosicionX() << ", " << jugador.getPosicionY() << ", " << jugador.getPosicionZ()
            << ")" << endl;                                                                                              //1
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
