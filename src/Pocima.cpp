//
// Created by ronyrojas on 20/03/25.
//
#include "../include/Pocima.h"
using namespace std;


Pocima::Pocima() {
    curacion = 15 + rand() % 11;
}

int Pocima::getCuracion() {
    return curacion;
}

void Pocima::setCuracion(int curacion) {
    this->curacion = curacion;
}
