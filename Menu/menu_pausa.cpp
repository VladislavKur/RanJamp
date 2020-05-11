#include "menu_pausa.h"
#include "../Juego/Juego.h"

menu_pausa* menu_pausa::p_instance = 0;
sf::Font* menu_pausa::fuente = new Font();

menu_pausa* menu_pausa::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        p_instance = new menu_pausa(*fuente, 4);

    }

    return(p_instance);
}

menu_pausa::menu_pausa( Font fuente, int max) : menu(fuente, max){
    t = new Textura("resources/Imagenes/MenuPausa.png");
    b = new Bloque(t);
}



void menu_pausa::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    menu_controles* menucont = menu_controles::instance();
    menu_vol* menuVol = menu_vol::instance();
    menu_inicial* menuIni = menu_inicial::instance();

    juego->pausarMusica(0);
    juego->reproducirMusica(2);
    juego->ponerBucleMusica(2);
    cambiarTexto(0,  "REANUDAR", juego->view.getCenter().x-100, juego->view.getCenter().y-125);
    cambiarTexto(1,  "CONTROLS", juego->view.getCenter().x-100, juego->view.getCenter().y-75);
    cambiarTexto(2, "OPTIONS", juego->view.getCenter().x-100, juego->view.getCenter().y-25 );
    cambiarTexto(3,  "MENU PRINCIPAL", juego->view.getCenter().x-100, juego->view.getCenter().y+25);

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
        cooldown_mov = 0.5;
        switch(selectedItem){
            case 0:
               juego->pausarMusica(2);
               juego->reproducirMusica(0);
               juego->ponerBucleMusica(0);
               man->cambiarEstado(juego);
               resetSelectedItem();
            break;

            case 1:
                man->cambiarEstado(menucont);
                resetSelectedItem();
            break;

            case 2:
                man->cambiarEstado(menuVol);
                 resetSelectedItem();
            break;
            case 3:
                man->cambiarEstado(menuIni);
                resetSelectedItem();
            break;
        }
    }
}