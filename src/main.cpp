#include <iostream>
#include <cassert>
#include <ctime>
#include "../include/MotorDeJuego.h"
using namespace std;

int main() {
    cout << "Hello world!" << "!\n";
    srand(time(0));
    MotorDeJuego motorDeJuego;
    motorDeJuego.mostrarMenu();
    return 0;
}
