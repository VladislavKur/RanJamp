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
/*
    // ESTO VA EN MOTOR---
    Font fuente; 
    if(!fuente.loadFromFile("resources/fuentes/AnotherRound.otf")){
      cout<< "NO SE CARGA"<<endl;
    }
    //.-------
    menu men(fuente, 3); // crear  menu 
    men.cambiarTexto(0, sf::Color::Red, "PLAY" , 540 , 320); // Fachada
    men.cambiarTexto(1, sf::Color::White, "OPTIONS" , 540, 350); 
    men.cambiarTexto(2, sf::Color::White, "EXIT" , 540 , 380); 
    while (m->getVentana()->isOpen()) {
      //Bucle de obtención de eventos
        Event event;
        while (m->getVentana()->pollEvent(event)) {

          switch (event.type){
            case Event::Closed:
              m->getVentana()->close();
            break;
            
            case Event::KeyPressed:
              //Verifico si se pulsa alguna tecla de movimiento
              switch (event.key.code) {
                case Keyboard::Up:
                  men.moveUp();
                break;
                case Keyboard::Down:
                  men.moveDown();
                break;
                case Keyboard::Return:
                  switch (men.getItemPressed()){
                    case 0:
                        cout<<"eligo play" << endl;
                    break;
                    
                    case 1: 
                        cout<<"eligio opciones"<<endl;
                      break;
                    case 2:
                        cout<<"eligo salir"<<endl;
                        m->getVentana()->close();
                      break;
                  }
                break;
                default:
                break;
                
              }
          
            default: 
            break;  
          }
        }

        m->getVentana()->clear();
        men.render();
        m->getVentana()->display();
    }

*/

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


      // coliArV.setPosition( instancia->getJugador()->coliArriba.left , instancia->getJugador()->coliArriba.top );
      // coliArV.setFillColor(Color(255, 255, 0, 128));
      // coliArV.setSize( Vector2f( instancia->getJugador()->coliArriba.width, instancia->getJugador()->coliArriba.height ) );

      // coliAbV.setPosition( instancia->getJugador()->coliAbajo.left , instancia->getJugador()->coliAbajo.top );
      // coliAbV.setFillColor(Color(0,0,0, 128));
      // coliAbV.setSize( Vector2f( instancia->getJugador()->coliAbajo.width, instancia->getJugador()->coliAbajo.height ) );
      
      // coliIzV.setPosition( instancia->getJugador()->coliIzquierda.left , instancia->getJugador()->coliIzquierda.top );
      // coliIzV.setFillColor(Color(255, 0, 0, 128));
      // coliIzV.setSize( Vector2f( instancia->getJugador()->coliIzquierda.width, instancia->getJugador()->coliIzquierda.height ) );

      // coliDcV.setPosition( instancia->getJugador()->coliDerecha.left , instancia->getJugador()->coliDerecha.top );
      // coliDcV.setFillColor(Color(0, 0, 255, 128));
      // coliDcV.setSize( Vector2f( instancia->getJugador()->coliDerecha.width, instancia->getJugador()->coliDerecha.height ) );

      window->clear();
      
      if(elapsus >= UPDATE_TICK_TIME){
        instancia->render(1.0);
      }

      else{
         instancia->render(elapsus/UPDATE_TICK_TIME);
      }
      
     /* window->draw(coliDcV);
      window->draw(coliIzV);
      window->draw(coliArV);
      window->draw(coliAbV);*/

      window->display();

      
    }

  return 0;
}
