//
// Created by ronyrojas on 24/03/25.
//

#ifndef THREEDIMENSIONALMATRIX_H
#define THREEDIMENSIONALMATRIX_H

#include "Node.h"
#include <iostream>
using namespace std;

template<typename T>
class ThreeDimensionalMatrix {
private:
    Node<T> *cabeza; // nodo raiz simbolizara estar en (0, 0, 0)
    int ancho;
    int alto;
    int profundidad;

public:
    //constructor que recibe las dimensiones de la matriz
    ThreeDimensionalMatrix(int ancho, int alto, int profundidad) {
        if (ancho < 2 || alto < 2 || profundidad < 2) {
            throw invalid_argument("Las dimensiones deben ser al menos 2x2x2");
        }
        this->ancho = ancho;
        this->alto = alto;
        this->profundidad = profundidad;
        // creando nodo cabeza, esta en posicion (0, 0, 0)
        cabeza = new Node<T>(T());
        Node<T> *nodoActual = cabeza;

        //recorriendo cada columna, de cada fila, de cada profundidad
        for (int z = 0; z < profundidad; ++z) {
            for (int y = 0; y < alto; ++y) {
                for (int x = 0; x < ancho; ++x) {
                    if (x == 0 && y == 0 && z == 0) {
                        //saltando el nodo en la posicion (0, 0, 0), ya existe
                        continue;
                    }
                    // creando nuevo nodo en la posicion actual
                    Node<T> *nuevoNodo = new Node<T>(T());

                    if (x > 0) {
                        //si x >0, significa que hay un izquierdo
                        //al nuevo nodo se le manda el actual como izquierdo
                        nuevoNodo->setLeft(nodoActual);
                        //al actual nodo se le manda el nuevoNodo como derecho
                        nodoActual->setRight(nuevoNodo);
                        //actualizando nodoActual, para llevar la secuencia de la fila
                        nodoActual = nuevoNodo;
                    } else {
                        nodoActual = nuevoNodo;
                    }
                    if (y > 0) {
                        //si y >0, significa que hay un nodo abajo, se obtiene
                        Node<T> *nodoAbajo = obtenerNodo(x, y - 1, z);
                        //al nuevo nodo se le conecta al de abajo
                        nuevoNodo->setDown(nodoAbajo);
                        //al de abajo se le conecta el arriba
                        nodoAbajo->setUp(nuevoNodo);
                    }
                    if (z > 0) {
                        //si z>0, significa que hay un nodo atras, se obtiene
                        Node<T> *nodoAtras = obtenerNodo(x, y, z - 1);
                        //al nuevo nodo se le conecta al de atras
                        nuevoNodo->setPrev(nodoAtras);
                        //al de atras se le conecta el de adelante
                        nodoAtras->setNext(nuevoNodo);
                    }
                }
            }
        }
    }

    Node<T> *obtenerNodo(int x, int y, int z) {
        //verificando limitas
        if (x < 0 || y < 0 || z < 0 || x >= ancho || y >= alto || z >= profundidad) {
            return nullptr;
        }
        Node<T> *actual = cabeza;
        //moviendo el actual hacia la derecha
        for (int i = 0; i < x && actual; ++i) {
            actual = actual->getRight();
        }
        //moviendo el actual hacia abajo
        for (int j = 0; j < y && actual; ++j) {
            actual = actual->getUp();
        }
        //moviendo el actual hacia adelante
        for (int k = 0; k < z && actual; ++k) {
            actual = actual->getNext();
        }
        return actual;
    }

    void insertar(int x, int y, int z, T valor) {
        //obteniendo nodo en la posicion indicada
        Node<T> *nodo = obtenerNodo(x, y, z);
        if (nodo) {
            //si existe el nodo se le manda un nuevo valor
            nodo->setData(valor);
        } else throw out_of_range("Posición inválida");
    }

    void imprimir() {
        cout << "*******************" << endl;
        for (int z = 0; z < profundidad; ++z) {
            cout << "Tablero en z = " << z << ":\n";
            for (int y = alto - 1; y >= 0; --y) {
                Node<T> *fila = obtenerNodo(0, y, z);
                for (int x = 0; x < ancho && fila; ++x) {
                    cout << fila->getData() << " ";
                    fila = fila->getRight();
                }
                cout << "\n";
            }
            cout << "\n";
            cout << "*******************" << endl;
        }
    }
};
#endif //THREEDIMENSIONALMATRIX_H
