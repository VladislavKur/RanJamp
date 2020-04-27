#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motor/Motor.h"
#include "Juego/Juego.h"
#include "Player/Player.h"
#include "Juego/Manejador.h"
#include "Juego/Menu.h"
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

    //Crear singletons
    Juego* juego = Juego::instance();
    Menu* menu = Menu::instancia();
    Manejador* instancia = Manejador::instancia();
    instancia->cambiarEstado(menu);

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
          /*Sif(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){ //WIP FACHADA y LECTURA TECLADO
      jugador->morir();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){ //WIP FACHADA y LECTURA TECLADO
      jugador->godMode();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){ //WIP FACHADA y LECTURA TECLADO
      
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){ //WIP FACHADA y LECTURA TECLADO
      
  }*/
        case sf::Keyboard::P:
          juego->getJugador()->obtenerPU_SaltoDoble();
          juego->getJugador()->obtenerPU_Slowhits();
          juego->getJugador()->obtenerPU_Velocidad();
        break;
        case sf::Keyboard::X:
          juego->getJugador()->morir();
        break;
        case sf::Keyboard::G:
          juego->getJugador()->toggleGodMode();
        break;
        case sf::Keyboard::R:
          juego->getJugador()->reset();
        break;

        case sf::Keyboard::N:
          
          //juego->nextLevel();
        break;

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


      coliArV.setPosition( juego->getJugador()->coliArriba.left , juego->getJugador()->coliArriba.top );
      coliArV.setFillColor(Color(255, 255, 0, 128));
      coliArV.setSize( Vector2f( juego->getJugador()->coliArriba.width, juego->getJugador()->coliArriba.height ) );

      coliAbV.setPosition( juego->getJugador()->coliAbajo.left , juego->getJugador()->coliAbajo.top );
      coliAbV.setFillColor(Color(0,0,0, 128));
      coliAbV.setSize( Vector2f( juego->getJugador()->coliAbajo.width, juego->getJugador()->coliAbajo.height ) );
      
      coliIzV.setPosition( juego->getJugador()->coliIzquierda.left , juego->getJugador()->coliIzquierda.top );
      coliIzV.setFillColor(Color(255, 0, 0, 128));
      coliIzV.setSize( Vector2f( juego->getJugador()->coliIzquierda.width, juego->getJugador()->coliIzquierda.height ) );

      coliDcV.setPosition( juego->getJugador()->coliDerecha.left , juego->getJugador()->coliDerecha.top );
      coliDcV.setFillColor(Color(0, 0, 255, 128));
      coliDcV.setSize( Vector2f( juego->getJugador()->coliDerecha.width, juego->getJugador()->coliDerecha.height ) );

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
     // std::cout<<"PU_Saltodoble: " << instancia->getJugador()->getPU_SaltoDoble() << " ------- AuxSaltos: "<<instancia->getJugador()->auxSaltos<<" ------- Saltos: "<<instancia->getJugador()->getSaltos()<< " ------- Cooldown: "<< instancia->getJugador()->getCooldownSalto() <<endl;

      //cout<<instancia->getJugador()->getJumpSpeed()<<endl;

      
    }
  //}

  return 0;
}
