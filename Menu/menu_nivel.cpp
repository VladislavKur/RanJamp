#include "menu_nivel.h"

menu_nivel* menu_nivel::p_instance = 0;
sf::Font* menu_nivel::fuente = new Font();

menu_nivel* menu_nivel::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        
        p_instance = new menu_nivel(*fuente, 5);

    }

    return(p_instance);
}

menu_nivel::menu_nivel( Font fuen, int max) : menu(fuen, max){
       t = new Textura("resources/Imagenes/MenuControles.png");
       b = new Bloque(t);
   
}



void menu_nivel::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    cambiarTexto(0, "Nivel 1", juego->view.getCenter().x-juego->view.getSize().x/3-100, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(1, "Nivel 2", juego->view.getCenter().x-50, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(2, "Nivel 3", juego->view.getCenter().x+juego->view.getSize().x/3, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(3, "Nivel 4", juego->view.getCenter().x-juego->view.getSize().x/5-50, juego->view.getCenter().y);
    cambiarTexto(4, "BACK", juego->view.getCenter().x+juego->view.getSize().x/2-300, juego->view.getCenter().y+juego->view.getSize().y/2-100);

    b->setPosition(juego->view.getCenter().x-juego->view.getSize().x/2, juego->view.getCenter().y-juego->view.getSize().y/2);
    b->setTextureRect(0,0,0,0);
    //menu_volumen* menuVol = menu_volumen::instance();

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && cooldown_mov<0 && selectedItem == 0){
        moveDown();moveDown();moveDown();
        cooldown_mov = 0.25;
    }
   if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && cooldown_mov<0 && selectedItem == 3 ){
        moveUp();moveUp();moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0 ){
        cooldown_mov = 0.5;
        switch(selectedItem){

            case 0:
                nivel += "1.tmx"; 
                juego->nivelSeleccionado(nivel);
                man->cambiarEstado(juego);
                resetSelectedItem();
            break;
            case 1:
                nivel += "2.tmx"; 
                juego->nivelSeleccionado(nivel);
                man->cambiarEstado(juego);
                resetSelectedItem();
            break;
            case 2:
                nivel += "3.tmx"; 
                
               juego->nivelSeleccionado(nivel);
                man->cambiarEstado(juego);
                resetSelectedItem();
            break;
            case 3:
                nivel += "4.tmx"; 
                juego->nivelSeleccionado(nivel);
                man->cambiarEstado(juego);
                resetSelectedItem();
            break;
            case 4:
                man->back();
                resetSelectedItem();
            break;
        }
    }
}