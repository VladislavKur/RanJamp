#include <SFML/Graphics.hpp>
#include <iostream>
#include "Motor/Motor.h"
#include "Juego/Juego.h"
#include "Player/Player.h"
#include "Menu/menu_inicial.h"
#include "Juego/Manejador.h"
#define kVel 5

int main() {
  /////////////
  ////START////
  /////////////
  const float UPDATE_TICK_TIME = 15.0;
  Motor * m = Motor::instance();

    float elapsus;
    float delta;
  Font fuente;
  fuente.loadFromFile("resources/fuentes/AnotherRound.otf");
    //Crear singletons
    Juego* juego = Juego::instance();

    //menu
    menu* _menu = new menu(fuente, 3);
    _menu->cambiarTexto(0, Color::White, "PLAY", 100, 100 );
    _menu->cambiarTexto(1, Color::White, "CONTROLS", 100, 200 );
    _menu->cambiarTexto(2, Color::White, "EXIT", 100, 300 );

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

        case sf::Keyboard::P:
          juego->getJugador()->obtenerPU_SaltoDoble();
          juego->getJugador()->obtenerPU_Slowhits();
          juego->getJugador()->obtenerPU_Velocidad();
        break;
        case sf::Keyboard::X:
        //if ( tipoEstado == Juego ) ?
          juego->matarJugador();
        break;
        case sf::Keyboard::G:
          juego->getJugador()->toggleGodMode();
        break;
        case sf::Keyboard::R:
          juego->getJugador()->reset();
        break;

        case sf::Keyboard::N:
          juego->nextLevel();
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
