#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motor/Motor.h"
#include "Juego/Juego.h"
#include "Player/Player.h"
#include "Menu/menu_inicial.h"
#include "Menu/menu_controles.h"

#include "Juego/Manejador.h"
#define kVel 5

int main() {
  /////////////
  ////START////
  /////////////
  const float UPDATE_TICK_TIME = 15.0;
  Motor * m = Motor::instance();
  menu_inicial* _menu = menu_inicial::instance();
  hud * Hud = hud::instance(); 

    float elapsus;
    float delta;
  Font fuente;
  fuente.loadFromFile("resources/fuentes/AnotherRound.otf");
    //Crear singletons
    Juego* juego = Juego::instance();

    //menu
    
    

    Manejador* instancia = Manejador::instancia();
    instancia->cambiarEstado(_menu);

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

        case sf::Keyboard::Z:
          //juego->getJugador()->obtenerPU_SaltoDoble();
          //juego->getJugador()->obtenerPU_Slowhits();
          //juego->getJugador()->obtenerPU_Velocidad();
          Hud->setDobleSalto(true);
          Hud->setSlow(true);
          Hud->setVelocidad(true);
          Hud->setIVelocidad(350);
        break;
        case sf::Keyboard::X:
        //if ( tipoEstado == Juego ) ?
          juego->matarJugador();
        break;
        case sf::Keyboard::G:
          //juego->getJugador()->toggleGodMode();
          Hud->setGodMode();
        break;
        case sf::Keyboard::R:
          juego->getJugador()->reset();
        break;

        case sf::Keyboard::N:
          juego->nextLevel(-1);
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
