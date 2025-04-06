//
// Created by ronyrojas on 30/03/25.
//
#include "../include/Reporte.h"

void Reporte::agregarPartida(const Partida &partida) {
    partidas.insertarFinal(partida);
}

void Reporte::agregarJugador(const Jugador &jugador) {
    tablaJugadores.insertarFinal(jugador);
}

void Reporte::mostrarMenuReportesPartidas(int indiceJugador) {
    Node<Partida> *actual = partidas.obtenerPorIndice(indiceJugador);                                             //1
    if (!actual) {                                                                                                      //1
        cout << "No hay partida con este indice" << endl;                                                               //1
        return;                                                                                                         //1
    }
    int opcionPartida = 0;                                                                                              //1
    do {
        cout << "\nSelecciona el reporte que quieres ver del jugador: " << actual->getData().getJugador().getNombre() <<
                endl;                                                                                                   //n
        cout << "1. Nombre del jugador, tiempo total, movimientos y puntuacion." << endl;                               //n
        cout << "2. Ubicacion del tesoro y trayectora del jugador." << endl;                                            //n
        cout << "3. Pistas encontradas y su distancia al tesoro." << endl;                                              //n
        cout << "4. Enemigos enfrentados y tramapas activadas." << endl;                                                //n
        cout << "5. Grafico de los arboles de enemigos y trampas." << endl;                                             //n
        cout << "6. Regresar al menu de reportes" << endl;                                                              //n
        cout << "Selecciona una opcion... ";                                                                            //n
        cin >> opcionPartida;                                                                                           //n
        cout << "-------------------------------------" << endl;                                                        //n
        switch (opcionPartida) {                                                                                        //n
            case 1: {                                                                                                   //n
                cout << "\nNombre del jugador: " << actual->getData().getJugador().getNombre() << endl;                 //n
                cout << "Tiempo total: " << actual->getData().getJugador().getTiempoJugado() << " s" << endl;           //n
                cout << "Movimientos: " << actual->getData().getJugador().getMovimientos() << endl;                     //n
                cout << "Puntuacion: " << actual->getData().getJugador().getPuntos() << endl;                           //n
                if (actual->getData().getJugador().getEncontroTesoro()){                                                //n
                    cout << "Encontro tesoro: Si"<< endl;                                                               //n
                } else {                                                                                                //n
                    cout << "Encontro tesoro: No"<< endl;                                                               //n
                }
                break;                                                                                                  //n
            }
            case 2: {                                                                                                   //n
                cout << "\nUbicacion del tesoro y trayectoria del jugador:" << endl;                                    //n
                actual->getData().getRegistroTrayectoria()->imprimir();                                                 //n
                break;                                                                                                  //n
            }
            case 3: {                                                                                                   //n
                cout << "\nPistas encontradas y distancia al tesoro:" << endl;                                          //n
                actual->getData().getRegistroPistas()->imprimir();                                                      //n
                break;                                                                                                  //n
            }
            case 4: {                                                                                                   //n
                cout << "\nEnemigos enfrentados y trampas activadas: " << endl;                                         //n
                actual->getData().getRegistroEnemigosYTrampas()->imprimir();                                            //n
                break;                                                                                                  //n
            }
            case 5: {                                                                                                   //n
                cout << "\nGrafico de los arboles de enemigos y trampas:" << endl;                                      //n
                cout << "Grafico de arboles de enemigos (nivel alto a nivel bajo)" << endl;                             //n
                cout << "Grafico de arboles de trampas (nivel bajo a nivel alto)" << endl;                              //n
                break;                                                                                                  //n
            }
            case 6: {                                                                                                   //n
                return;                                                                                                 //n
            }
            default: {                                                                                                  //n
                cout << "Opcion no valida." << endl;                                                                    //n
                break;                                                                                                  //n
            }
        }
        cout << "\n-------------------------------------" << endl;                                                      //n
    } while (opcionPartida != 6);                                                                                       //n
}

void Reporte::mostrarTablaJugadores() {
    if (!tablaJugadores.getCabeza()) {                                                          //1
        cout << "No hay jugadores existentes" << endl;                                          //1
        return;                                                                                 //1
    }
    ordenarTablaJugadores();                                                                    //1
    Node<Jugador> *actual = tablaJugadores.getCabeza();                                         //1
    cout << "\n--- Tabla de Jugadores ---\n";                                                   //1
    int indice = 0;                                                                             //1
    while (actual) {                                                                            //n
        indice++;                                                                               //n
        cout << indice << ") Nombre: " << actual->getData().getNombre() << endl;                //n
        cout << "   Puntuacion: " << actual->getData().getPuntos() << endl;                     //n
        cout << "   Vida: " << actual->getData().getVida() << endl;                             //n
        cout << "   Movimientos: " << actual->getData().getMovimientos() << endl;               //n
        cout << "   Tiempo jugado: " << actual->getData().getTiempoJugado() << " s" << endl;    //n
        if (actual->getData().getEncontroTesoro()){                                             //n
            cout << "   Encontro el teosoro: Si" <<endl;                                        //n
        } else {                                                                                //n
            cout << "   Encontro el teosoro: No" <<endl;                                        //n
        }
        cout << "-------------------------\n";                                                  //n
        actual = actual->getNext();                                                             //n
    }
}

void Reporte::ordenarTablaJugadores() {
    if (!tablaJugadores.getCabeza()) {                                                          //1
        return;                                                                                 //1
    }
    bool intercambio;                                                                           //1
    do {
        intercambio = false;                                                                    //n
        Node<Jugador> *actual = tablaJugadores.getCabeza();                                     //n

        while (actual->getNext() != nullptr) {                                                  //n^2
            if (actual->getData().getPuntos() < actual->getNext()->getData().getPuntos()) {     //n^2
                Jugador temp = actual->getData();                                               //n^2
                actual->setData(actual->getNext()->getData());                                  //n^2
                actual->getNext()->setData(temp);                                               //n^2
                intercambio = true;                                                             //n^2
            }
            actual = actual->getNext();                                                         //n
        }
    } while (intercambio);                                                                      //n
}

LinkedList<Partida> &Reporte::getPartidas() {
    return partidas;
}
