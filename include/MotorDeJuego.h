//
// Created by ronyrojas on 27/03/25.
//

#ifndef MOTORDEJUEGO_H
#define MOTORDEJUEGO_H
#include "Reporte.h"

class MotorDeJuego {
public:
    void mostrarMenu();

private:
    void nuevaPartida();

    void verReportes();

    bool finalizarEjecucion = false;

    Reporte reporte;
};
#endif //MOTORDEJUEGO_H
