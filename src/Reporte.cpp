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
    Node<Partida> *actual = partidas.obtenerPorIndice(indiceJugador);
    if (!actual) {
        cout << "No hay partida con este indice" << endl;
        return;
    }
    int opcionPartida = 0;
    do {
        cout << "\nSelecciona el reporte que quieres ver del jugador: " << actual->getData().getJugador().getNombre() <<
                endl;
        cout << "1. Nombre del jugador, tiempo total, movimientos y puntuacion." << endl;
        cout << "2. Ubicacion del tesoro y trayectora del jugador." << endl;
        cout << "3. Pistas encontradas y su distancia al tesoro." << endl;
        cout << "4. Enemigos enfrentados y tramapas activadas." << endl;
        cout << "5. Grafico de los arboles de enemigos y trampas." << endl;
        cout << "6. Regresar al menu de reportes" << endl;
        cout << "Selecciona una opcion... ";
        cin >> opcionPartida;

        switch (opcionPartida) {
            case 1: {
                cout << "\nNombre del jugador: " << actual->getData().getJugador().getNombre() << endl;
                cout << "Tiempo total: " << actual->getData().getJugador().getTiempoJugado() << " s" << endl;
                cout << "Movimientos: " << actual->getData().getJugador().getMovimientos() << endl;
                cout << "Puntuacion: " << actual->getData().getJugador().getPuntos() << endl;
                break;
            }
            case 2: {
                cout << "\nUbicacion del tesoro y trayectoria del jugador:" << endl;
                actual->getData().getRegistroTrayectoria()->imprimir();
                break;
            }
            case 3: {
                cout << "\nPistas encontradas y distancia al tesoro:" << endl;
                actual->getData().getRegistroPistas()->imprimir();
                break;
            }
            case 4: {
                cout << "\nEnemigos enfrentados y trampas activadas: " << endl;
                actual->getData().getRegistroEnemigosYTrampas()->imprimir();
                break;
            }
            case 5: {
                cout << "\nGrafico de los arboles de enemigos y trampas:" << endl;
                break;
            }
            case 6: {
                return;
            }
            default: {
                cout << "Opcion no valida." << endl;
                break;
            }
        }
    } while (opcionPartida != 6);
}

void Reporte::mostrarTablaJugadores() {
    if (!tablaJugadores.getCabeza()) {
        cout << "No hay jugadores existentes" << endl;
        return;
    }
    ordenarTablaJugadores();
    Node<Jugador> *actual = tablaJugadores.getCabeza();
    cout << "\n--- Tabla de Jugadores ---\n";
    int indice = 0;
    while (actual) {
        indice++;
        cout << indice << ") Nombre: " << actual->getData().getNombre() << endl;
        cout << "   Puntuacion: " << actual->getData().getPuntos() << endl;
        cout << "   Vida: " << actual->getData().getVida() << endl;
        cout << "   Movimientos: " << actual->getData().getMovimientos() << endl;
        cout << "   Tiempo jugado: " << actual->getData().getTiempoJugado() << endl;
        cout << "-------------------------\n";
        actual = actual->getNext();
    }
}

void Reporte::ordenarTablaJugadores() {
    if (!tablaJugadores.getCabeza()) {
        return;
    }
    bool intercambio;
    do {
        intercambio = false;
        Node<Jugador> *actual = tablaJugadores.getCabeza();

        while (actual->getNext() != nullptr) {
            if (actual->getData().getPuntos() < actual->getNext()->getData().getPuntos()) {
                // Intercambiar los datos de los nodos
                Jugador temp = actual->getData();
                actual->setData(actual->getNext()->getData());
                actual->getNext()->setData(temp);
                intercambio = true;
            }
            actual = actual->getNext();
        }
    } while (intercambio);
}

LinkedList<Partida> &Reporte::getPartidas() {
    return partidas;
}
