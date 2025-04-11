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
        if (ancho < 2 || alto < 2 || profundidad < 2) {                                 //1
            throw invalid_argument("Las dimensiones deben ser al menos 2x2x2");         //1
        }
        this->ancho = ancho;                                                            //1
        this->alto = alto;                                                              //1
        this->profundidad = profundidad;                                                //1
        // creando nodo cabeza, esta en posicion (0, 0, 0)
        cabeza = new Node<T>(T());                                                      //1
        Node<T> *nodoActual = cabeza;                                                   //1

        //recorriendo cada columna, de cada fila, de cada profundidad
        for (int z = 0; z < profundidad; ++z) {                                         //n
            for (int y = 0; y < alto; ++y) {                                            //n²
                for (int x = 0; x < ancho; ++x) {                                       //n³
                    if (x == 0 && y == 0 && z == 0) {                                   //n³
                        //saltando el nodo en la posicion (0, 0, 0), ya existe
                        continue;                                                       //n³
                    }
                    // creando nuevo nodo en la posicion actual
                    Node<T> *nuevoNodo = new Node<T>(T());                              //n³

                    if (x > 0) {                                                        //n³
                        //si x >0, significa que hay un izquierdo
                        //al nuevo nodo se le manda el actual como izquierdo
                        nuevoNodo->setLeft(nodoActual);                                 //n³
                        //al actual nodo se le manda el nuevoNodo como derecho
                        nodoActual->setRight(nuevoNodo);                                //n³
                        //actualizando nodoActual, para llevar la secuencia de la fila
                        nodoActual = nuevoNodo;                                         //n³
                    } else {                                                            //n³
                        nodoActual = nuevoNodo;                                         //n³
                    }
                    if (y > 0) {                                                        //n³
                        //si y >0, significa que hay un nodo abajo, se obtiene
                        Node<T> *nodoAbajo = obtenerNodo(x, y - 1, z);              //n³
                        //al nuevo nodo se le conecta al de abajo
                        nuevoNodo->setDown(nodoAbajo);                                  //n³
                        //al de abajo se le conecta el arriba
                        nodoAbajo->setUp(nuevoNodo);                                    //n³
                    }
                    if (z > 0) {                                                        //n³
                        //si z>0, significa que hay un nodo atras, se obtiene
                        Node<T> *nodoAtras = obtenerNodo(x, y, z - 1);              //n³
                        //al nuevo nodo se le conecta al de atras
                        nuevoNodo->setPrev(nodoAtras);                                  //n³
                        //al de atras se le conecta el de adelante
                        nodoAtras->setNext(nuevoNodo);                                  //n³
                    }
                }
            }
        }
    }

    ~ThreeDimensionalMatrix() {
        destruirMatriz();
    }

    void destruirMatriz() {
        for (int z = 0; z < profundidad; ++z) {
            for (int y = 0; y < alto; ++y) {
                Node<T> *actual = obtenerNodo(0, y, z);
                while (actual != nullptr) {
                    Node<T> *siguiente = actual->getRight();
                    delete actual;
                    actual = siguiente;
                }
            }
        }
    }

    Node<T> *obtenerNodo(int x, int y, int z) {
        //verificando limites
        if (x < 0 || y < 0 || z < 0 || x >= ancho || y >= alto || z >= profundidad) {   //1
            return nullptr;                                                             //1
        }
        Node<T> *actual = cabeza;                                                       //1
        //moviendo el actual hacia la derecha
        for (int i = 0; i < x && actual; ++i) {                                         //n
            actual = actual->getRight();                                                //n
        }
        //moviendo el actual hacia abajo
        for (int j = 0; j < y && actual; ++j) {                                         //n
            actual = actual->getUp();                                                   //n
        }
        //moviendo el actual hacia adelante
        for (int k = 0; k < z && actual; ++k) {                                         //n
            actual = actual->getNext();                                                 //n
        }
        return actual;                                                                  //1
    }

    void insertar(int x, int y, int z, T valor) {
        //obteniendo nodo en la posicion indicada
        Node<T> *nodo = obtenerNodo(x, y, z);                                           //1
        if (nodo) {                                                                     //1
            //si existe el nodo se le manda un nuevo valor
            nodo->setData(valor);                                                       //1
        } else throw out_of_range("Posición inválida");                                 //1
    }

    void imprimir() {
        cout << "*******************" << endl;                                          //1
        for (int z = 0; z < profundidad; ++z) {                                         //n
            cout << "Tablero en z = " << z << ":\n";                                    //n
            for (int y = alto - 1; y >= 0; --y) {                                       //n²
                Node<T> *fila = obtenerNodo(0, y, z);                                 //n²
                for (int x = 0; x < ancho && fila; ++x) {                               //n³
                    cout << fila->getData() << " ";                                     //n³
                    fila = fila->getRight();                                            //n³
                }
                cout << "\n";                                                           //n²
            }
            cout << "\n";                                                               //n
            cout << "*******************" << endl;                                      //n
        }
    }
};
#endif //THREEDIMENSIONALMATRIX_H
