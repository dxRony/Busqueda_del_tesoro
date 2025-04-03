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

    bool buscar(const T &data) const {
        // se comienza desde la raiz
        Node<T> *arbol = raiz;                                                                  //1
        while (arbol != nullptr) {                                                              //n
            // guardando el valor de la raiz del arbol actual
            T valorRaiz = arbol->getData();                                                     //n
            if (data == valorRaiz) {                                                            //n
                // devolviendo true si el valor buscado esta en la raiz del arbol
                return true;                                                                    //n
            } else if (data < valorRaiz) {                                                      //n
                // si el valor es menor al valor de la raiz, se busca en el subarbol izquierdo
                arbol = arbol->getLeft();                                                       //n
            } else {                                                                            //n
                // si el valor es mayor al valor de la raiz, se busca en el subarbol derecho
                arbol = arbol->getRight();                                                      //n
            }
        }
        // si se recorre el BST y no se encuentra el valor, se devuelve false
        return false;                                                                           //n
    }

    // eliminar un valor del BST
    void eliminar(const T &data) {
        raiz = eliminarPrivado(raiz, data);                                                     //1
    }

private:
    Node<T> *eliminarPrivado(Node<T> *arbol, const T &data) {
        if (arbol == nullptr) {                                                                 //1
            // si el BST esta vacio, no se puede eliminar nada
            return nullptr;                                                                     //1
        }
        if (data < arbol->getData()) {                                                          //1
            // si el valor es menor que la raaz, se busca en el subarbol izquierdo
            arbol->setLeft(eliminarPrivado(arbol->getLeft(), data));                       //log n
        } else if (data > arbol->getData()) {                                                   //1
            // si el valor es mayor que la raiz, se busca en el subarbol derecho
            arbol->setRight(eliminarPrivado(arbol->getRight(), data));                     //log n
        } else {                                                                                //1
            // cuando el valor sea igual a la raiz, se elimina el nodo dependiendo del escenario
            if (arbol->getLeft() == nullptr && arbol->getRight() == nullptr) {                  //1
                // escenario 1 - nodo sin hijos (solo se borra el nodo)
                delete arbol;                                                                   //1
                return nullptr;                                                                 //1
            } else if (arbol->getLeft() == nullptr) {                                           //1
                // Escenario 2 - nodo solo con hijo derecho
                // Se guarda el subarbol derecho y se borra el arbol
                Node<T> *temp = arbol->getRight();                                              //1
                delete arbol;                                                                   //1
                return temp;                                                                    //1
            } else if (arbol->getRight() == nullptr) {                                          //1
                // escenario 2 - nodo solo con hijo izquierdo
                // se guarda el subarbol izquierdo y se borra el arbol
                Node<T> *temp = arbol->getLeft();                                               //1
                delete arbol;                                                                   //1
                return temp;                                                                    //1
            } else {                                                                            //1
                // escenario 3 - nodo con sus dos hijos
                // se encuentra el minimo del subarbol derecho
                Node<T> *temp = encontrarMinimoSubarbolDerecho(arbol->getRight());         //1
                // en la raiz del arbol se reemplaza el dato del minimo derecho
                arbol->setData(temp->getData());                                                //1
                // eliminando el minimo de hasta abajo del árbol
                arbol->setRight(eliminarPrivado(arbol->getRight(), temp->getData())); //1
            }
        }
        return arbol;                                                                           //1
    }

    Node<T> *encontrarMinimoSubarbolDerecho(Node<T> *arbol) const {
        // encontrando el minimo del arbol recibido
        while (arbol->getLeft() != nullptr) {                                                   //n
            // mientras haya un subárbol izquierdo, se obtiene
            arbol = arbol->getLeft();                                                           //n
        }
        // retornando el arbol donde ya no haya un subarbol izquierdo
        return arbol;                                                                           //1
    }
};
#endif // BST_H
