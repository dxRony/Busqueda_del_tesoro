#ifndef BST_H
#define BST_H

#include "Node.h"
#include <iostream>
using namespace std;

template<typename T>
class BST {
private:
    // raiz/incio del arbol
    Node<T> *raiz;

public:
    BST() {
        raiz = nullptr;
    }

    ~BST() {
        destruirArbol(raiz);
    }

    void destruirArbol(Node<T> *nodo) {
        if (nodo != nullptr) {
            destruirArbol(nodo->getLeft());
            destruirArbol(nodo->getRight());
            delete nodo;
        }
    }

    void insertar(const T &data) {
        // si el arbol esta vacio, crear un nuevo nodo como raiz
        if (raiz == nullptr) {                                                                  //1
            raiz = new Node<T>(data);                                                           //1
            return;                                                                             //1
        }
        Node<T> *actual = raiz;                                                                 //1
        while (true) {                                                                          //n
            if (data < actual->getData()) {                                                     //n
                // si el valor es menor, se guarda en el subarbol izq
                if (actual->getLeft() == nullptr) {                                             //n
                    //si se llega al final del arbol se inserta
                    actual->setLeft(new Node<T>(data));                                         //n
                    break;                                                                      //n
                } else {
                    // si no, se avanza al siguiente nodo izquierdo                             //n
                    actual = actual->getLeft();                                                 //n
                }
            } else {                                                                            //n
                // si el valor es mayor, se guarda en el subarbol der
                if (actual->getRight() == nullptr) {                                            //n
                    //si se llega al final de arbol se inserta
                    actual->setRight(new Node<T>(data));                                        //n
                    break;                                                                      //n
                } else {
                    // si no se avanza al siguiente subarbol derecho
                    actual = actual->getRight();                                                //n
                }
            }
        }
    }

    void imprimir(int recorrido) {
        if (recorrido == 1) {                                                                   //1
            //recorriendo arbol de manera descendente (derecho, raiz, izquierdo)
             imprimirDescendente(raiz, 0);                                               //1
        }
    }

private:
    void imprimirDescendente(Node<T> *nodo, int espacio){
        if (nodo == nullptr){                                                                   //1
            return;                                                                             //1
        }
        int sangria = 5;                                                                        //1
        espacio += sangria;                                                                     //1

        imprimirDescendente(nodo->getRight(), espacio);                                    //log n

        cout << "\n";                                                                           //1
        for (int i = sangria; i < espacio; i++) {                                               //n
            cout << " ";                                                                        //n
        }
        cout << nodo->getData() << "\n";                                                        //1
        imprimirDescendente(nodo->getLeft(), espacio);                                     //log n
    }
};
#endif // BST_H
