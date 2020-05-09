#include <SFML/Graphics.hpp>
#include <iostream>
#include "Enemigos/nube.h"
#include "Player/Player.h"
#include "Motor/Motor.h"

#define kVel 90.0
#define maxBullets 512

int main() {

  const float UPDATE_TICK_TIME = 15.0; //magnitud: millisegundos

  //Creamos una ventana
  //sf::RenderWindow window(sf::VideoMode(1200, 1200), "P0. Fundamentos de los Videojuegos. DCCIA");
  Motor* motor = Motor::instance();
  //////////////
  ///BLOQUE////
  /////////////  
  sf::RectangleShape cuerpoMueve(sf::Vector2f(50.0f, 70.0f));
  cuerpoMueve.setFillColor(sf::Color(0,255,0));
  cuerpoMueve.setPosition(sf::Vector2f(100,600));
  

  Nube *enemigo = new Nube(1100,200);

  sf::Clock updateClock;
  float delta;
  float elapsus;
  int contador = 0;

  Bullet* bulletNube[maxBullets];
  for(int i = 0; i < maxBullets;i++){
    bulletNube[i] = NULL;
  }


  while (motor->getOpen()) {

    for(unsigned i = 0; i < maxBullets ;i++){
        if(bulletNube[i] != NULL){
          if(bulletNube[i]->lifetime<=0){
            delete bulletNube[i];
          bulletNube[i] = NULL;
        }
        else
          bulletNube[i]->update(delta);//revisar
        }
    }

    if(updateClock.getElapsedTime().asMilliseconds()>UPDATE_TICK_TIME){ //si hay que actualizar, actualiza
      delta = updateClock.restart().asSeconds();
      enemigo->update(cuerpoMueve, delta);
      //player->update(delta);
    }

    Nube* casteadoNube = dynamic_cast<Nube*>(enemigo); 
    if(casteadoNube != nullptr){
        if(casteadoNube->getShoot()){
          for(int j = 0; j < maxBullets;j++){
            if(bulletNube[j] == NULL)
              bulletNube[j] = casteadoNube->disparar();
          }
        }
    }

    sf::Event event;
    while (motor->getVentana()->pollEvent(event)) {

      switch (event.type) {
      //Si se recibe el evento de cerrar la ventana la cierro
      case sf::Event::Closed:
        motor->getVentana()->close();
        break;

      case sf::Event::KeyPressed:
        switch (event.key.code) {
            //Tecla ESC para salir
            case sf::Keyboard::Escape:
            motor->getVentana()->close();
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


    cuerpoMueve.move(kVel/1000.0,0);

    bool morir = false;
    for(unsigned int i = 0; i < maxBullets; i++){
      if(bulletNube[i] != NULL){

        if(cuerpoMueve.getGlobalBounds().intersects(bulletNube[i]->getBody().getGlobalBounds())){

          morir = true;
          std::cout << "Vidas del jugador: " << 0 << "\n";
          
          bulletNube[i] = NULL;
          delete bulletNube[i];

          if(morir == true){
            //matarJugador();
            cuerpoMueve.setScale(0.5, 0.5);
          }
        }
      }

    }

    motor->limpieza();

    for(unsigned i = 0; i < maxBullets;i++){
      if(bulletNube[i] != nullptr){bulletNube[i]->render();} //interpolacion
    }
    elapsus = updateClock.getElapsedTime().asMilliseconds();

    enemigo->render(elapsus/UPDATE_TICK_TIME);
    //player->render(window);
    motor->dibujo(cuerpoMueve);
    motor->mostrar();
    contador++;
  }

  return 0;
}