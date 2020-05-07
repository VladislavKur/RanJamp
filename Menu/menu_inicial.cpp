#include "menu_inicial.h"


menu_inicial::menu_inicial( Font fuente, int max) : menu(fuente, max){

}



void menu_inicial::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )){
        switch(selectedItem){
            case 0:
                man->cambiarEstado(juego);
            break;

            case 1:

            break;

            case 2:
                
            break;
        }
    }
}