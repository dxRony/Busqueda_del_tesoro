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

    // Crea y enlaza todos los nodos recursivamente
    //crea un nodo en la posicion indicada
    Node<T> *crearNodo(int x, int y, int z) {
        //evaluando que no se excedan las posiciones del array
        if (x >= ancho || y >= alto || z >= profundidad) {
            return nullptr;
        }
        //creando nodo
        Node<T> *nuevoNodo = new Node<T>(0); // Valor inicial 0

        //creando y registrando nodos a la par del nodo actual
        nuevoNodo->setRight(crearNodo(x + 1, y, z));
        nuevoNodo->setUp(crearNodo(x, y + 1, z));
        nuevoNodo->setNext(crearNodo(x, y, z + 1));

        //si el nodo actual tiene derecho, se le manda al derecho el actual como izquierdo
        if (nuevoNodo->getRight()) {
            nuevoNodo->getRight()->setLeft(nuevoNodo);
        }
        //si el nodo actual tiene nodo arriba, se le manda al de arriba el actual como el nodo de abajo
        if (nuevoNodo->getUp()) {
            nuevoNodo->getUp()->setDown(nuevoNodo);
        }
        //si el nodo actual tiene siguiente, se le manda al siguiente el actual como previo
        if (nuevoNodo->getNext()) {
            nuevoNodo->getNext()->setPrev(nuevoNodo);
        }
        //retornando el nodo creado en la posicion indicada
        cout << "Creando nodo en (" << x << "," << y << "," << z << ")"<< endl;
        return nuevoNodo;
    }

public:
    //constructor que recibe las dimensiones de la matriz
    ThreeDimensionalMatrix(int ancho, int alto, int profundidad) {
        if (ancho < 2 || alto < 2 || profundidad < 2) {
            throw invalid_argument("Las dimensiones para crear el tablero son de 2x2x2");
        }
        this->ancho = ancho;
        this->alto = alto;
        this->profundidad = profundidad;
        //creando nodo en la posicion origen de la matriz
        cabeza = crearNodo(0, 0, 0);
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
        for (int z = 0; z < profundidad; ++z) {
            cout << "Capa " << z << ":\n";
            for (int y = alto -1 ; y >= 0; --y) {
                Node<T> *fila = obtenerNodo(0, y, z);
                for (int x = 0; x < ancho && fila; ++x) {
                    cout << fila->getData() << " ";
                    fila = fila->getRight();
                }
                cout << "\n";
            }
            cout << "\n";
        }
    }
};
#endif //THREEDIMENSIONALMATRIX_H
