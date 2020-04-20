#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemigos/nube.h"
#include "Player/Player.h"
#define kVel 900.0


int main() {

  const float UPDATE_TICK_TIME = 15.0; //magnitud: millisegundos

  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(1200, 1200), "P0. Fundamentos de los Videojuegos. DCCIA");
    
  //////////////
  ///BLOQUE////
  /////////////  
  sf::RectangleShape cuerpoMueve(sf::Vector2f(50.0f, 70.0f));
  cuerpoMueve.setFillColor(sf::Color(0,255,0));
  cuerpoMueve.setPosition(sf::Vector2f(100,600));
  

  Nube *enemigo = new Nube(1100,200);
  //Player* player = new Player(1100,600);

  //Bucle del juego

  sf::Clock updateClock;
  float delta;
  float elapsus;
  int contador = 0;
  while (window.isOpen()) {

    /////////////////////////////////////////////
    //LO PRIMERO ES LA COMPROBACION DE UPDATE//
    /////////////////////////////////////////////

    if(updateClock.getElapsedTime().asMilliseconds()>UPDATE_TICK_TIME){ //si hay que actualizar, actualiza
      delta = updateClock.restart().asSeconds();
      enemigo->update(cuerpoMueve, delta);
      //player->update(delta);
    }

    sf::Event event;
    while (window.pollEvent(event)) {

      switch (event.type) {
      //Si se recibe el evento de cerrar la ventana la cierro
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        switch (event.key.code) {
            //Tecla ESC para salir
            case sf::Keyboard::Escape:
            window.close();
            break;

            //Cualquier tecla desconocida se imprime por pantalla su código
            default:
            std::cout << event.key.code << std::endl;
            break;
        }
        default:
        break;
      }
    
    }
    //////////////////////////
    //LO SEGUNDO ES RENDERIZAR
    //////////////////////////

    window.clear();
    cuerpoMueve.move(kVel/1000.0,0);
    elapsus = updateClock.getElapsedTime().asMilliseconds();

    enemigo->render(window, elapsus/UPDATE_TICK_TIME);
    //player->render(window);
    window.draw(cuerpoMueve);
    window.display();
    contador++;
  }

  return 0;
}