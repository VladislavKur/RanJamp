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
       t = new Textura("resources/Imagenes/MenuControles.png");
       b = new Bloque(t);
   
}



void menu_controles::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    cambiarTexto(0, "BACK", juego->view.getCenter().x+juego->view.getSize().x/2-300, juego->view.getCenter().y+juego->view.getSize().y/2-100);

    b->setPosition(juego->view.getCenter().x-juego->view.getSize().x/2, juego->view.getCenter().y-juego->view.getSize().y/2);
   
    //menu_volumen* menuVol = menu_volumen::instance();

    /*if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }*/
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0 ){
        cooldown_mov = 0.5;
        switch(selectedItem){

            case 0:
                man->back();
            break;
        }
    }
}