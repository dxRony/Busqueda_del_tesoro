//
// Created by ronyrojas on 21/03/25.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
using namespace std;

template<typename T>
class LinkedList {
private:
    Node<T> *head; // puntero a la cabeza de la lista
    int size; // tamano de la lista

public:
    // constructor
    LinkedList();

    // destructor
    ~LinkedList();

    // Métodos básicos
    void insertarInicio(const T &data);

    void insertarFinal(const T &data);

    bool eliminar(const T &data);

    bool buscar(const T &data) const;

    void imprimir() const;

    int obtenerTamano() const;

    bool isEmpty() const;
};

//constructor
template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    size = 0;
}

// destructor
template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T> *actual = head;
    while (actual) {
        Node<T> *temp = actual;
        actual = actual->getNext();
        delete temp;
    }
}

template<typename T>
void LinkedList<T>::insertarInicio(const T &data) {
    Node<T> *nuevoNodo = new Node<T>(data);
    nuevoNodo->setNext(head);
    head = nuevoNodo;
    size++;
}

template<typename T>
void LinkedList<T>::insertarFinal(const T &data) {
    Node<T> *nuevoNodo = new Node<T>(data);
    if (!head) {
        head = nuevoNodo;
    } else {
        Node<T> *temp = head;
        while (temp->getNext()) {
            temp = temp->getNext();
        }
        temp->setNext(nuevoNodo);
    }
    size++;
}

template<typename T>
bool LinkedList<T>::eliminar(const T &data) {
    if (!head) {
        return false;
    }
    if (head->getData() == data) {
        Node<T> *temp = head;
        head = head->getNext();
        delete temp;
        size--;
        return true;
    }
    Node<T> *actual = head;
    while (actual->getNext() && actual->getNext()->getData() != data) {
        actual = actual->getNext();
    }

    if (!actual->getNext()) {
        return false;
    }
    Node<T> *temp = actual->getNext();
    actual->setNext(temp->getNext());
    delete temp;
    size--;
    return true;
}

template<typename T>
bool LinkedList<T>::buscar(const T &data) const {
    Node<T> *actual = head;
    while (actual) {
        if (actual->getData() == data) return true;
        actual = actual->getNext();
    }
    return false;
}

template<typename T>
void LinkedList<T>::imprimir() const {
    Node<T> *actual = head;
    while (actual) {
        cout << actual->getData() << " ->";
        actual = actual->getNext();
    }
    cout << "fin de la lista" << endl;
}

template<typename T>
int LinkedList<T>::obtenerTamano() const {
    return size;
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}
#endif //LINKEDLIST_H
