#include "menu_mundos.h"
#include "menu_nivel.h"
#include "menu_inicial.h"
menu_mundos* menu_mundos::p_instance = 0;
sf::Font* menu_mundos::fuente = new Font();

menu_mundos* menu_mundos::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        p_instance = new menu_mundos(*fuente, 6);

    }

    return(p_instance);
}

menu_mundos::menu_mundos( Font fuente, int max) : menu(fuente, max){
       t = new Textura("resources/Imagenes/Menu.png");
       b = new Bloque(t);
   
}



void menu_mundos::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    menu_nivel* nivel = menu_nivel::instance();
    menu_inicial* inicio = menu_inicial::instance();
    cambiarTexto(0, "Mundo 1", juego->view.getCenter().x-juego->view.getSize().x/3-100, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(1, "Mundo 2", juego->view.getCenter().x-50, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(2, "Mundo 3", juego->view.getCenter().x+juego->view.getSize().x/3, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(3, "Mundo 4", juego->view.getCenter().x-juego->view.getSize().x/5-50, juego->view.getCenter().y);
    cambiarTexto(4, "Jefe Final", juego->view.getCenter().x+juego->view.getSize().x/5-50, juego->view.getCenter().y);
    cambiarTexto(5, "BACK", juego->view.getCenter().x+juego->view.getSize().x/2-300, juego->view.getCenter().y+juego->view.getSize().y/2-100);

    b->setPosition(juego->view.getCenter().x-juego->view.getSize().x/2, juego->view.getCenter().y-juego->view.getSize().y/2);
    
    //menu_volumen* menuVol = menu_volumen::instance();

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }
     if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }
   if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0){
        cooldown_mov = 0.5;
        switch(selectedItem){

            case 0:
                man->cambiarEstado(nivel);
            break;
            case 1:
                man->cambiarEstado(nivel);
            break;
            case 2:
               man->cambiarEstado(nivel);
            break;
            case 3:
                man->cambiarEstado(nivel);
            break;
            case 4:
               man->cambiarEstado(nivel);
            break;
            case 5:
                man->cambiarEstado(inicio);
            break;
        }
    }
}