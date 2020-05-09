#include "menu_inicial.h"
#include "../Juego/Juego.h"
menu_inicial* menu_inicial::p_instance = 0;
sf::Font* menu_inicial::fuente = new Font();

menu_inicial* menu_inicial::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        p_instance = new menu_inicial(*fuente, 4);

    }

    return(p_instance);
}

menu_inicial::menu_inicial( Font fuente, int max) : menu(fuente, max){
    t = new Textura("resources/Imagenes/Menu.png");
    b = new Bloque(t);
}



void menu_inicial::update(float deltaTime){
    cooldown_mov-=deltaTime;
    texto[selectedItem].setColor(Color::Red);
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    menu_controles* menucont = menu_controles::instance();
    menu_vol* menuVol = menu_vol::instance();

    cambiarTexto(0,  "PLAY", juego->view.getCenter().x-40, juego->view.getCenter().y-125);
    cambiarTexto(1, "CONTROLS", juego->view.getCenter().x-40, juego->view.getCenter().y-75);
    cambiarTexto(2,  "OPTIONS", juego->view.getCenter().x-40, juego->view.getCenter().y -25);
    cambiarTexto(3,  "EXIT", juego->view.getCenter().x-40, juego->view.getCenter().y+25);

        b->setPosition(juego->view.getCenter().x-juego->view.getSize().x/2, juego->view.getCenter().y-juego->view.getSize().y/2);
        b->setTextureRect(0,0,1080,720);
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0){
        cooldown_mov = 0.35;
        switch(selectedItem){
            case 0:
               man->cambiarEstado(juego);
              
            break;

            case 1:
                
                man->cambiarEstado(menucont);
                
            break;

            case 2:
                man->cambiarEstado(menuVol);
                 
            break;
            case 3:
                Motor * motor = Motor::instance();
                motor->getVentana()->close();
            break;
        }
    }
}