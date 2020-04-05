#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motor/Motor.h"
#include "Juego/Juego.h"
#include "Player/Player.h"
#define kVel 5

int main() {
  /////////////
  ////START////
  /////////////
  // sf::Texture t; 
  // sf::Sprite s; 
  // if(!t.loadFromFile("Resources/sprites.png")){
  //   std::cout<<"mierda"<<endl;
  // }
  // s.setTexture(t);
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

        delta = m->restartReloj();

       instancia->update(delta);

      }

      elapsus = m->getRelojM();

      RenderWindow* window = m->getVentana();

      window->clear();
      
      if(elapsus >= UPDATE_TICK_TIME){
        instancia->render(1.0);
      }

      else{
         instancia->render(elapsus/UPDATE_TICK_TIME);
      }

      window->display();
    }
  //}

  return 0;
}
