#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motor/Motor.h"
#include "Enemigos/pajaro.h"
#define kVel 5

int main(){

    Motor* motor = Motor::instance();

    Pajaro* pajaro = new Pajaro(900,400);

    float relojActual= 0.0;
    float deltaTime = 0.0;
    float porcentaje = 0.0;

    while(motor->getOpen()){

        relojActual = motor->getReloj();

        if(relojActual >= (1/15)){

            deltaTime = motor->restartReloj();

            pajaro->update(nullptr,deltaTime);

            relojActual = motor->getReloj();

        }

        porcentaje = relojActual/deltaTime;

        if(porcentaje > 1.0)
            porcentaje = 1.0;

        motor->limpieza();

        pajaro->render(porcentaje);

        motor->mostrar();

    }
}