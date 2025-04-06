//
// Created by ronyrojas on 27/03/25.
//
#include "../include/MotorDeJuego.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

void MotorDeJuego::mostrarMenu() {
    int opcion;
    do {
        cout << "   BIENVENIDO A BUSQUEDA DEL TESORO   " << endl;
        cout << "\n*********** Menu Principal ***********" << endl;
        cout << "1. Nueva Partida" << endl;
        cout << "2. Ver Reportes" << endl;
        cout << "3. Cargar jugadores con archivo.csv" << endl;
        cout << "4. Salir del juego" << endl;
        cout << "Selecciona Una Opcion: ";

        try {
            cin >> opcion;
            if (cin.fail()) {
                throw runtime_error("Entrada invalida, debes ingresar un numero entre 1 y 4");
            }
            if (opcion < 1 || opcion > 4) {
                throw out_of_range("Opcion fuera de rango, debes ingresar un numero entre 1 y 4");
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
                    cargarJugadores();
                    break;
                }
                case 4: {
                    finalizarEjecucion = true;
                    break;
                }
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
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
        cout << "Selecciona una opcion... ";
        cin >> opcionReporte;

        switch (opcionReporte) {
            case 1:
                int indiceJugador;
                cout << "\nSelecciona la partida del jugador que deseas ver: " << endl;
                reporte.getPartidas().imprimir();
                cin >> indiceJugador;
                reporte.mostrarMenuReportesPartidas(indiceJugador);
                break;
            case 2:
                reporte.mostrarTablaJugadores();
                break;
            case 3:
                return;
            default:
                cout << "opcion invalida, intenta de nuevo." << endl;
                break;
        }
    } while (opcionReporte != 3);
}

void MotorDeJuego::cargarJugadores() {
    string nombreArchivo;                                                                                               //1
    cout << "\nIngresa el nombre del archivo.csv: ";                                                                    //1
    cin >> nombreArchivo;                                                                                               //1

    ifstream archivo(nombreArchivo);                                                                                 //1

    if (!archivo.is_open()) {                                                                                           //1
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;                                                //1
        return;                                                                                                         //1
    }
    string linea;                                                                                                       //1
    while (getline(archivo, linea)) {                                                                             //n
        stringstream ss(linea);                                                                                     //n
        string nombre;                                                                                                  //n
        string puntosStr;                                                                                               //n
        string movimientosStr;                                                                                          //n

        getline(ss, nombre, ',');                                                                           //n
        getline(ss, puntosStr, ',');                                                                        //n
        getline(ss, movimientosStr);                                                                              //n

        try {
            int puntos = stoi(puntosStr);                                                                           //n
            int movimientos = stoi(movimientosStr);                                                                 //n

            Jugador nuevoJugador(nombre);                                                                               //n
            nuevoJugador.setPuntos(puntos);                                                                             //n
            nuevoJugador.setMovimientos(movimientos);                                                                   //n
            reporte.agregarJugador(nuevoJugador);                                                                //n
        } catch (const exception& e) {                                                                                  //n
            cout << "Error al procesar linea: " << linea << " - " << e.what() << endl;                                  //n
        }
    }
    archivo.close();                                                                                                    //1
    cout << "Se cargo a los jugadores desde el archivo" << endl;                                                        //1
}

