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
        if (raiz == nullptr) {
            raiz = new Node<T>(data);
            return;
        }

        Node<T> *actual = raiz;
        while (true) {
            if (data < actual->getData()) {//
                // si el valor es menor, se guarda en el subarbol izq
                if (actual->getLeft() == nullptr) {
                    //si se llega al final del arbol se inserta
                    actual->setLeft(new Node<T>(data));
                    break;
                } else {
                    // si no, se avanza al siguiente nodo izquierdo
                    actual = actual->getLeft();
                }
            } else {
                // si el valor es mayor, se guarda en el subarbol der
                if (actual->getRight() == nullptr) {
                    //si se llega al final de arbol se inserta
                    actual->setRight(new Node<T>(data));
                    break;
                } else {
                    // si no se avanza al siguiente subarbol derecho
                    actual = actual->getRight();
                }
            }
        }
    }

    // Mostrar el árbol en orden ascendente (izquierda, raíz, derecha)
    void mostrarAscendente() const {
        mostrarAscendentePrivado(raiz, 0);
    }

    // Mostrar el árbol en orden descendente (derecha, raíz, izquierda)
    void mostrarDescendente() const {
        mostrarDescendentePrivado(raiz, 0);
    }

    bool buscar(const T &data) const {
        Node<T> *arbol = raiz; // se comienza desde la raiz
        while (arbol != nullptr) {
            T valorRaiz = arbol->getData(); // guardando el valor de la raiz del arbol actual
            if (data == valorRaiz) {
                // devolviendo true si el valor buscado esta en la raiz del arbol
                return true;
            } else if (data < valorRaiz) {
                // si el valor es menor al valor de la raiz, se busca en el subarbol izquierdo
                arbol = arbol->getLeft();
            } else {
                // si el valor es mayor al valor de la raiz, se busca en el subarbol derecho
                arbol = arbol->getRight();
            }
        }
        // si se recorre todo el BST y no se encuentra el valor, se devuelve false
        return false;
    }

    // eliminar un valor del BST
    void eliminar(const T &n) {
        raiz = eliminarPrivado(raiz, n);
    }

private:
    void mostrarAscendentePrivado(Node<T> *arbol, int cont) const {
        if (arbol == nullptr) {
            // Si el arbol esta vacio, no se imprime nada
            return;
        } else {
            // recorriendo el subárbol izquierdo (valores menores)
            mostrarAscendentePrivado(arbol->getLeft(), cont + 1);
            // imprimiendo el valor del nodo actual
            for (int i = 0; i < cont; i++) {
                cout << "   ";
            }
            cout << arbol->getData() << endl;
            // recorriendo el subarbol derecho (valores mayores)
            mostrarAscendentePrivado(arbol->getRight(), cont + 1);
        }
    }

    void mostrarDescendentePrivado(Node<T> *arbol, int cont) const {
        if (arbol == nullptr) {
            // Si el arbol está vacio, no se imprime nada
            return;
        } else {
            // recorriendo el subarbol derecho (valores mayores)
            mostrarDescendentePrivado(arbol->getRight(), cont + 1);
            // imprimiendo el valor del nodo actual
            for (int i = 0; i < cont; i++) {
                cout << "   ";
            }
            cout << arbol->getData() << endl;
            // recorriendo el subarbol izquierdo (valores menores)
            mostrarDescendentePrivado(arbol->getLeft(), cont + 1);
        }
    }

    Node<T> *eliminarPrivado(Node<T> *arbol, const T &data) {
        if (arbol == nullptr) {
            // si el BST esta vacio, no se puede eliminar nada
            return nullptr;
        }
        if (data < arbol->getData()) {
            // si el valor es menor que la raaz, se busca en el subarbol izquierdo
            arbol->setLeft(eliminarPrivado(arbol->getLeft(), data));
        } else if (data > arbol->getData()) {
            // si el valor es mayor que la raiz, se busca en el subarbol derecho
            arbol->setRight(eliminarPrivado(arbol->getRight(), data));
        } else {
            // cuando el valor sea igual al de la raiz, se elimina el nodo dependiendo del escenario
            if (arbol->getLeft() == nullptr && arbol->getRight() == nullptr) {
                // escenario 1 - nodo sin hijos (solo se borra el nodo)
                delete arbol;
                return nullptr;
            } else if (arbol->getLeft() == nullptr) {
                // Escenario 2 - nodo solo con hijo derecho
                // Se guarda el subarbol derecho y se borra el arbol
                Node<T> *temp = arbol->getRight();
                delete arbol;
                return temp;
            } else if (arbol->getRight() == nullptr) {
                // escenario 2 - nodo solo con hijo izquierdo
                // se guarda el subarbol izquierdo y se borra el arbol
                Node<T> *temp = arbol->getLeft();
                delete arbol;
                return temp;
            } else {
                // escenario 3 - nodo con sus dos hijos
                // se encuentra el minimo del subarbol derecho
                Node<T> *temp = encontrarMinimoSubarbolDerecho(arbol->getRight());
                // en la raiz del arbol se reemplaza el dato del minimo derecho
                arbol->setData(temp->getData());
                // eliminando el minimo de hasta abajo del árbol
                arbol->setRight(eliminarPrivado(arbol->getRight(), temp->getData()));
            }
        }
        return arbol;
    }

    Node<T> *encontrarMinimoSubarbolDerecho(Node<T> *arbol) const {
        // encontrando el minimo del arbol recibido
        while (arbol->getLeft() != nullptr) {
            // mientras haya un subárbol izquierdo, se obtiene
            arbol = arbol->getLeft();
        }
        // retornando el arbol donde ya no haya un subarbol izquierdo
        return arbol;
    }
};

#endif // BST_H
