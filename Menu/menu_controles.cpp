#include "menu_controles.h"

menu_controles* menu_controles::p_instance = 0;
sf::Font* menu_controles::fuente = new Font();

menu_controles* menu_controles::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        p_instance = new menu_controles(*fuente, 1);

    }

    return(p_instance);
}

menu_controles::menu_controles( Font fuente, int max) : menu(fuente, max){

   
}



void menu_controles::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    cambiarTexto(0, "BACK TO MENU", juego->view.getCenter().x-100, juego->view.getCenter().y-25);


   
    //menu_volumen* menuVol = menu_volumen::instance();

    /*if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }*/
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0){
        cooldown_mov = 0.35;
        switch(selectedItem){

            case 0:
               
                man->back();
            break;
        }
    }
}