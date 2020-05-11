#include "menu_inicial.h"
#include "../Juego/Juego.h"
#include "menu_mundos.h"

menu_inicial* menu_inicial::p_instance = 0;
sf::Font* menu_inicial::fuente = new Font();

menu_inicial* menu_inicial::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        p_instance = new menu_inicial(*fuente, 7);

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
    menu_mundos* mundos = menu_mundos::instance();
    Tienda * tienda = Tienda::instance();
    Motor * motor = Motor::instance();
    motor->getVentana()->setView(juego->view); //wIP fachada

    if(noeslaprimeravezxd){
        cambiarTexto(0,  "CONTINUAR PARTIDA", juego->view.getCenter().x-60, juego->view.getCenter().y-125);
        cambiarTexto(1,  "NUEVA PARTIDA", juego->view.getCenter().x-60, juego->view.getCenter().y-75);
        cambiarTexto(2,  "SELECCIONAR NIVEL", juego->view.getCenter().x-60, juego->view.getCenter().y-25);
        cambiarTexto(3,  "TIENDA", juego->view.getCenter().x-60, juego->view.getCenter().y +25);
        cambiarTexto(4, "CONTROLS", juego->view.getCenter().x-60, juego->view.getCenter().y+75);
        cambiarTexto(5,  "OPTIONS", juego->view.getCenter().x-60, juego->view.getCenter().y +125);
        cambiarTexto(6,  "EXIT", juego->view.getCenter().x-60, juego->view.getCenter().y+175);
    }
    else{
    cambiarTexto(0,  "PLAY", juego->view.getCenter().x-60, juego->view.getCenter().y-125);
    cambiarTexto(1,  "SELECCIONAR NIVEL", juego->view.getCenter().x-60, juego->view.getCenter().y-75);
    cambiarTexto(2,  "TIENDA", juego->view.getCenter().x-60, juego->view.getCenter().y -25);
    cambiarTexto(3, "CONTROLS", juego->view.getCenter().x-60, juego->view.getCenter().y+25);
    cambiarTexto(4,  "OPTIONS", juego->view.getCenter().x-60, juego->view.getCenter().y +75);
    cambiarTexto(5,  "EXIT", juego->view.getCenter().x-60, juego->view.getCenter().y+125);
    }
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
        if(noeslaprimeravezxd){
            switch(selectedItem){
            case 0:
                noeslaprimeravezxd=true;
               man->cambiarEstado(juego);
               resetSelectedItem();
              
            break;
            case 1:
                juego->matarJugador();
                man->cambiarEstado(juego);
                resetSelectedItem();
                break;
            case 2:
                man->cambiarEstado(mundos);
                resetSelectedItem();
                break;
            case 3:
                 man->cambiarEstado(tienda);
                 resetSelectedItem();
            break;
            case 4:
                
                man->cambiarEstado(menucont);
                resetSelectedItem();
                
            break;

            case 5:
                man->cambiarEstado(menuVol);
                resetSelectedItem();
                 
            break;
            case 6:
                motor->getVentana()->close();
            break;

        }}else{
        switch(selectedItem){
            case 0:
                noeslaprimeravezxd=true;
                resetSelectedItem();
               man->cambiarEstado(juego);
              
            break;
            case 1:
                resetSelectedItem();
                man->cambiarEstado(mundos);
                break;
            case 2:
                 man->cambiarEstado(tienda);
                 resetSelectedItem();
            break;
            case 3:
                
                man->cambiarEstado(menucont);
                resetSelectedItem();
                
            break;

            case 4:
                man->cambiarEstado(menuVol);
                resetSelectedItem();
                 
            break;
            case 5:
                motor->getVentana()->close();
            break;
            
        }
    }
    }
}