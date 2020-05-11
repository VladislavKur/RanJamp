#include "menu_vol.h"

menu_vol* menu_vol::p_instance = 0;
sf::Font* menu_vol::fuente = new Font();

menu_vol* menu_vol::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        p_instance = new menu_vol(*fuente, 5);

    }

    return(p_instance);
}

menu_vol::menu_vol( Font fuente, int max) : menu(fuente, max){
    t = new Textura("resources/Imagenes/MenuOpciones.png");
    b = new Bloque(t);
    pausa = false;
    
}



void menu_vol::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    
    cambiarTexto(0, "-", juego->view.getCenter().x-100, juego->view.getCenter().y);
    cambiarTexto(1, to_string((int)juego->getVolumen()+1), juego->view.getCenter().x, juego->view.getCenter().y);
    cambiarTexto(2, "+", juego->view.getCenter().x+100, juego->view.getCenter().y);
    cambiarTexto(3, "Mute", juego->view.getCenter().x, juego->view.getCenter().y+100);
    cambiarTexto(4, "BACK", juego->view.getCenter().x+juego->view.getSize().x/2-300, juego->view.getCenter().y+juego->view.getSize().y/2-200);

    b->setPosition(juego->view.getCenter().x-juego->view.getSize().x/2, juego->view.getCenter().y-juego->view.getSize().y/2);
   

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0){
        cooldown_mov = 0.5;
        switch(selectedItem){

            case 0:
                if(juego->getVolumen() >= 10){
                    juego->setVolumen(juego->getVolumen()-10);
                }
            break;
            case 2:
                if(juego->getVolumen() <= 90){
                    juego->setVolumen(juego->getVolumen()+10);
                }
            break;
            case 3:
                if(pausa == false){
                    juego->pausarMusica();
                    pausa = true;
                }else{
                    juego->reproducirMusica();
                    pausa = false;
                }
            break;
            case 4:
                man->back();
                resetSelectedItem();
            break;
        }
    }
}