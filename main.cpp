#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motor/Motor.h"
#include "Juego/Juego.h"

#define kVel 5

int main() {
  /////////////
  ////START////
  /////////////

  const float UPDATE_TICK_TIME = 15.0;
  Motor * m = Motor::instance();
  //Creamos una ventana
  //if(m->crearVentana()){ //si la ventana se crea correctamente

    float elapsus;
    float delta;

    Juego* instancia = Juego::instance();

    //funcion inicializar juego de juego VERY WIP SUCH WOW

    while(m->getOpen()){
      if(m->getRelojM() > UPDATE_TICK_TIME){

        delta = m->rPestartReloj();

        instancia->update(delta);

      }

      elapsus = m->getRelojM();
      
      if(elapsus >= UPDATE_TICK_TIME){
        instancia->render(1.0);
      }

      else{
        instancia->render(elapsus/UPDATE_TICK_TIME);
      }
    }
  //}

  return 0;
}
