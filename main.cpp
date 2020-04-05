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

      RenderWindow* window = m->getVentana();

      sf::Event event;
    while(window->pollEvent(event)){
      switch (event.type)
      {
      //Para poder cerrar la ventana se necesita:
      case sf::Event::EventType::Closed :
        window->close();
      break;

      case sf::Event::EventType::KeyPressed:

        switch (event.key.code) {

        default:
          break;
        }

      break; // de KeyPressed
      
      default:
        break;
      }
    }
      if(m->getRelojM() > UPDATE_TICK_TIME){

        delta = m->restartReloj();

        instancia->update(delta);

      }

      elapsus = m->getRelojM();


      window->clear();
      
      if(elapsus >= UPDATE_TICK_TIME){
        instancia->render(1.0);
      }

      else{
         instancia->render(elapsus/UPDATE_TICK_TIME);
      }

      window->display();


      //window->clear(Color(128,0,0));
//
      //window->draw(instancia->getJugador()->getBody());
//
      //window->display();

    }
  //}

  return 0;
}
