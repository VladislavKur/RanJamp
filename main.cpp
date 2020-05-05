#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motor/Motor.h"
#include "Juego/Juego.h"
#include "Player/Player.h"
#include "Menu/menu.h"
#define kVel 5

int main() {
  /////////////
  ////START////
  /////////////
  const float UPDATE_TICK_TIME = 15.0;
  Motor * m = Motor::instance();

    float elapsus;
    float delta;
    Juego* instancia = Juego::instance();

    RectangleShape coliArV;
    RectangleShape coliAbV;
    RectangleShape coliIzV;
    RectangleShape coliDcV;


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

        case sf::Keyboard::P:
          instancia->getJugador()->obtenerPU_SaltoDoble();
          instancia->getJugador()->obtenerPU_Slowhits();
          instancia->getJugador()->obtenerPU_Velocidad();
        break;
        case sf::Keyboard::X:
          instancia->matarJugador();
        break;
        case sf::Keyboard::G:
          instancia->getJugador()->toggleGodMode();
        break;
        case sf::Keyboard::R:
          instancia->getJugador()->reset();
        break;

        case sf::Keyboard::N:
          instancia->nextLevel();
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

      
    }

  return 0;
}
