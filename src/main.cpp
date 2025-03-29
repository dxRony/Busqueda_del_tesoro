#include <iostream>
#include "../include/edd/LinkedList.h"
#include "../include/edd/BST.h"
#include "../include/edd/ThreeDimensionalMatrix.h"
#include <cassert>
#include <ctime>
#include "../include/MotorDeJuego.h"
using namespace std;

int main() {
    cout << "Hello world!" << "!\n";
    srand(time(0));
    MotorDeJuego motorDeJuego;
    motorDeJuego.mostrarMenu();

    /*cout << "probando lista" << endl;

   LinkedList<int> listaDePrueba;
   listaDePrueba.insertarInicio(10);
   listaDePrueba.insertarInicio(5);
   listaDePrueba.insertarFinal(20);
   listaDePrueba.insertarFinal(30);

   cout << "imprimiendo lista: " << endl;
   listaDePrueba.imprimir();

   cout << "existe 10 en la lista... " << listaDePrueba.buscar(10) << endl;

   cout << "eliminando 10 en la lista..." << endl;
   listaDePrueba.eliminar(10);

   cout << "tamano lista: " << listaDePrueba.obtenerTamano() << endl;

   cout << "existe 10 en la lista... " << listaDePrueba.buscar(10) << endl;

   cout << "imprimiendo lista final: " << endl;
   listaDePrueba.imprimir();
   */

    /*cout << "probando bst" << endl;

    BST<int> bstPrueba;
    cout << "Insertando valores" <<endl;
    bstPrueba.insertar(50);
    bstPrueba.insertar(30);
    bstPrueba.insertar(70);
    bstPrueba.insertar(20);
    bstPrueba.insertar(40);
    bstPrueba.insertar(60);
    bstPrueba.insertar(80);

    cout << "\narbol despues de las inserciones" << endl;
    bstPrueba.mostrarDescendente();

    cout << "\nbuscando valores:" << endl;
    cout << "buscando 40 " << bstPrueba.buscar(40) << endl;
    cout << "buscando 100 " << bstPrueba.buscar(100) << endl;

    cout << "\neliminando valores" << endl;
    bstPrueba.eliminar(20);
    bstPrueba.eliminar(30);

    cout << "\narbol después de eliminar" << endl;
    bstPrueba.mostrarDescendente();

    cout << "\neliminando nodo con dos hijos" << endl;
    bstPrueba.eliminar(50);
    cout << "\narbol despues de eliminar 50:" << endl;
    bstPrueba.mostrarDescendente();

    cout << "\ninsertando valores" << endl;
    bstPrueba.insertar(10);
    bstPrueba.insertar(90);
    bstPrueba.insertar(55);

    cout << "\narbol despues de insertar" << endl;
    bstPrueba.mostrarDescendente();

    cout << "\neliminando nodo con un hijo" << endl;
    bstPrueba.eliminar(80);

    cout << "\narbol despues de eliminar 80:" << endl;
    bstPrueba.mostrarDescendente();

    cout << "\nEliminando la raiz 60:" << endl;
    bstPrueba.eliminar(60);

    cout << "\narbol despues de eliminar la raiz (60):" << endl;
    bstPrueba.mostrarDescendente();

    // Mostrar el árbol en orden ascendente
    cout << "arbol en orden ascendente:" << endl;
    bstPrueba.mostrarAscendente();

    // Mostrar el árbol en orden descendente
    cout << "\narbol en orden descendente:" << endl;
    bstPrueba.mostrarDescendente();
    */

    /*
    cout << "probando threeDimensionalMatrix" << endl;

    ThreeDimensionalMatrix<int> mat(3, 3, 2);
    mat.insertar(0, 0, 0, 1);
    mat.insertar(1, 0, 0, 2);
    mat.insertar(0, 1, 0, 3);
    mat.insertar(1, 1, 0, 4);
    mat.insertar(0, 0, 1, 5);
    mat.insertar(1, 0, 1, 6);
    mat.insertar(0, 1, 1, 7);
    mat.insertar(1, 1, 1, 8);
    mat.insertar(2, 0, 0, 9);
    mat.imprimir();

    Node<int> *nodo = mat.obtenerNodo(1, 1, 1);
    cout << "Obteniendo el contenido del nodo en la posicion (1, 1, 1): " << endl;
    cout << nodo->getData() << endl;
    cout << "obteniendo nodo arriba: " << nodo->getUp()->getData() << endl;
    cout << "obteniendo nodo abajo: " << nodo->getDown()->getData() << endl;
    cout << "obteniendo nodo derecha: " << nodo->getRight()->getData() << endl;
    cout << "obteniendo nodo izquierda: " << nodo->getLeft()->getData() << endl;
    //cout << "obteniendo nodo adelante: "<< nodo->getNext()->getData() << endl;
    cout << "obteniendo nodo atras: " << nodo->getPrev()->getData() << endl;
    */
    return 0;
}
