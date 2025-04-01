//
// Created by ronyrojas on 27/03/25.
//
#include "../include/MotorDeJuego.h"
#include <iostream>
#include <limits>

#include "../include/Partida.h"
#include "../include/Reporte.h"
using namespace std;

void MotorDeJuego::mostrarMenu() {
    int opcion;
    do {
        cout << "   BIENVENIDO A BUSQUEDA DEL TESORO   " << endl;
        cout << "\n*********** Menu Principal ***********" << endl;
        cout << "1. Nueva Partida" << endl;
        cout << "2. Ver Reportes" << endl;
        cout << "3. Salir Del Juego" << endl;
        cout << "Selecciona Una Opcion: ";

        try {
            cin >> opcion;
            //viendo si la entrada es un numero
            if (cin.fail()) {
                throw runtime_error("Entrada invalida, debes ingresar un numero entre 1 y 3");
            }
            //viendo si la entrada es un numero en el rango permitido
            if (opcion < 1 || opcion > 3) {
                throw out_of_range("Opcion fuera de rango, debes ingresar un numero entre 1 y 3");
            }
            switch (opcion) {
                case 1: {
                    nuevaPartida();
                    break;
                }
                case 2: {
                    verReportes();
                    break;
                }
                case 3: {
                    finalizarEjecucion = true;
                    break;
                }
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear(); // limpiando entrada en consola
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignorando entrada incorrecta
        }
    } while (!finalizarEjecucion);
}

void MotorDeJuego::nuevaPartida() {
    string nombreJugador;
    int ancho, alto, profundidad;
    cout << "\nIniciando nueva partida..." << endl;
    cout << "Ingresa tu nombre jugador: ";
    cin >> nombreJugador;
    cout << "Ingresa el ancho del tablero: ";
    cin >> ancho;
    cout << "Ingresa el alto del tablero: ";
    cin >> alto;
    cout << "Ingresa la profundidad del tablero: ";
    cin >> profundidad;

    Partida nuevaPartida(nombreJugador, ancho, alto, profundidad);
    nuevaPartida.iniciarPartida();
    reporte.agregarPartida(nuevaPartida);
    reporte.agregarJugador(nuevaPartida.getJugador());
}

void MotorDeJuego::verReportes() {
    int opcionReporte;
    do {
        cout << "\nSelecciona el reporte que quieres ver:" << endl;
        cout << "1. Ver reportes de partidas completadas" << endl;
        cout << "2. Ver tabla de jugadores" << endl;
        cout << "3. Regresar al menu principal" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcionReporte;

        switch (opcionReporte) {
            case 1:
                reporte.mostrarReportesPartidas();
            break;
            case 2:
                reporte.mostrarTablaJugadores();
            break;
            case 3:
                return;
            default:
                cout << "Opción no válida, intenta de nuevo." << endl;
            break;
        }
    } while (opcionReporte != 3);
}
