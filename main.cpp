#include <iostream>
#include "include/edd/LinkedList.h"
using namespace std;

int main() {
    cout << "Hello world " << "!\n";

    cout << "probando lista" << endl;
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

    return 0;
}
