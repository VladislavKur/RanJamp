#include "menu_vol.h"

menu_vol* menu_vol::p_instance = 0;
sf::Font* menu_vol::fuente = new Font();

menu_vol* menu_vol::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        p_instance = new menu_vol(*fuente, 1);

    }

    return(p_instance);
}

menu_vol::menu_vol( Font fuente, int max) : menu(fuente, max){
t = new Textura("resources/Imagenes/MenuOpciones.png");
       b = new Bloque(t);
    
}



void menu_vol::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    

    cambiarTexto(0, "BACK", juego->view.getCenter().x+juego->view.getSize().x/2-300, juego->view.getCenter().y+juego->view.getSize().y/2-100);

    b->setPosition(juego->view.getCenter().x-juego->view.getSize().x/2, juego->view.getCenter().y-juego->view.getSize().y/2);
   

    /*if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }*/
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0){
        cooldown_mov = 0.5;
        switch(selectedItem){

            case 0:
                man->back();
            break;
        }
    }
}