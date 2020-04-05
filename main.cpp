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

    RectangleShape coliArV;
    RectangleShape coliAbV;
    RectangleShape coliIzV;
    RectangleShape coliDcV;

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
        //std::cout<<delta<<std::endl;
        instancia->update(delta);

      }

      elapsus = m->getRelojM();

/*
      coliArV.setPosition( instancia->getJugador()->coliArriba.left , instancia->getJugador()->coliArriba.top );
      coliArV.setFillColor(Color(255, 255, 0, 128));
      coliArV.setSize( Vector2f( instancia->getJugador()->coliArriba.width, instancia->getJugador()->coliArriba.height ) );

      coliAbV.setPosition( instancia->getJugador()->coliAbajo.left , instancia->getJugador()->coliAbajo.top );
      coliAbV.setFillColor(Color(0,0,0, 128));
      coliAbV.setSize( Vector2f( instancia->getJugador()->coliAbajo.width, instancia->getJugador()->coliAbajo.height ) );
      
      coliIzV.setPosition( instancia->getJugador()->coliIzquierda.left , instancia->getJugador()->coliIzquierda.top );
      coliIzV.setFillColor(Color(255, 0, 0, 128));
      coliIzV.setSize( Vector2f( instancia->getJugador()->coliIzquierda.width, instancia->getJugador()->coliIzquierda.height ) );

      coliDcV.setPosition( instancia->getJugador()->coliDerecha.left , instancia->getJugador()->coliDerecha.top );
      coliDcV.setFillColor(Color(0, 0, 255, 128));
      coliDcV.setSize( Vector2f( instancia->getJugador()->coliDerecha.width, instancia->getJugador()->coliDerecha.height ) );
*/
      window->clear();
      
      if(elapsus >= UPDATE_TICK_TIME){
        instancia->render(1.0);
      }

      else{
         instancia->render(elapsus/UPDATE_TICK_TIME);
      }

      window->draw(coliDcV);
      window->draw(coliIzV);
      window->draw(coliArV);
      window->draw(coliAbV);

      window->display();


      //window->clear(Color(128,0,0));
//
      //window->draw(instancia->getJugador()->getBody());
//
      //window->display();

      cout<<instancia->getJugador()->getJumpSpeed()<<endl;

      

    }
  //}

  return 0;
}
