//
// Created by ronyrojas on 21/03/25.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <iostream>
using namespace std;

template<typename T>
class LinkedList {
private:
    Node<T> *head; //puntero a la cabeza de la lista
    int size; //tamano de la lista

public:
    // constructor
    LinkedList();

    // destructor
    ~LinkedList();

    void insertarInicio(const T &data);

    void insertarFinal(const T &data);

    bool eliminar(const T &data);

    bool buscar(const T &data) const;

    void imprimir() const;

    Node<T> *obtenerPorIndice(int indice);

    int obtenerTamano() const;

    Node<T> *getCabeza() const;

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
    while (head) {
        Node<T> *temp = head;
        head = head->getNext();
        delete temp;
    }
}

template<typename T>
void LinkedList<T>::insertarInicio(const T &data) {
    Node<T> *nuevoNodo = new Node<T>(data);         //1
    nuevoNodo->setNext(head);                       //1
    head = nuevoNodo;                               //1
    size++;                                         //1
}

template<typename T>
void LinkedList<T>::insertarFinal(const T &data) {
    Node<T> *nuevoNodo = new Node<T>(data);         //1
    if (!head) {                                    //1
        head = nuevoNodo;                           //1
    } else {                                        //1
        Node<T> *temp = head;                       //1
        while (temp->getNext()) {                   //n
            temp = temp->getNext();                 //n
        }
        temp->setNext(nuevoNodo);                   //1
    }
    size++;                                         //1
}

template<typename T>
bool LinkedList<T>::eliminar(const T &data) {
    if (!head) {                                    //1
        return false;                               //1
    }
    if (head->getData() == data) {                  //1
        Node<T> *temp = head;                       //1
        head = head->getNext();                     //1
        delete temp;                                //1
        size--;                                     //1
        return true;                                //1
    }
    Node<T> *actual = head;                         //1
    while (actual->getNext() && actual->getNext()->getData() != data) { //n
        actual = actual->getNext();                                     //n
    }
    if (!actual->getNext()) {                       //1
        return false;                               //1
    }
    Node<T> *temp = actual->getNext();              //1
    actual->setNext(temp->getNext());               //1
    delete temp;                                    //1
    size--;                                         //1
    return true;                                    //1
}

template<typename T>
bool LinkedList<T>::buscar(const T &data) const {
    Node<T> *actual = head;                         //1
    while (actual) {                                //n
        if (actual->getData() == data) return true; //n
        actual = actual->getNext();                 //n
    }
    return false;                                   //1
}

template<typename T>
void LinkedList<T>::imprimir() const {
    Node<T> *actual = head;                             //1
    int i = 0;                                          //1
    while (actual) {                                    //n
        cout << i << ") " << actual->getData() << " \n";//n
        i++;                                            //n
        actual = actual->getNext();                     //n
    }
}

template<typename T>
Node<T> *LinkedList<T>::obtenerPorIndice(int indice) {
    if (indice < 0) {                                   //1
        throw out_of_range("indice invalido");          //1
    }
    Node<T> *actual = head;                             //1
    int contador = 0;                                   //1

    while (actual != nullptr) {                         //n
        if (contador == indice) {                       //n
            return actual;                              //n
        }
        actual = actual->getNext();                     //n
        contador++;                                     //n
    }
    throw out_of_range("indice fuera de rango");        //1
}

template<typename T>
int LinkedList<T>::obtenerTamano() const {
    return size;
}

template<typename T>
Node<T> *LinkedList<T>::getCabeza() const {
    return head;
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}
#endif //LINKEDLIST_H
