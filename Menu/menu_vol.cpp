#include "menu_vol.h"

menu_vol* menu_vol::p_instance = 0;
sf::Font* menu_vol::fuente = new Font();

menu_vol* menu_vol::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        p_instance = new menu_vol(*fuente, 4, 1, 2);

    }

    return(p_instance);
}

menu_vol::menu_vol( Font fuente, int max, int maxS , int Aux) : menu(fuente, max){
    t = new Textura("resources/Imagenes/MenuOpciones.png");
    b = new Bloque(t);
    pausa = false;
    maxSprites = maxS;
    maxAux = Aux;
    sprites = new Cuerpo *[maxSprites];
    sprites[0] = new Cuerpo(300 , 100,150,150,"Tick.png",1, 0,-1);
    sprites[0]->Scalar(0.2,0.2);
    aux = new Text[maxAux];

}



void menu_vol::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();

    cambiarAux(0, "SONIDO:", juego->view.getCenter().x-100, juego->view.getCenter().y-100);
    cambiarTexto(0, "-", juego->view.getCenter().x-100, juego->view.getCenter().y);
    cambiarAux(1, to_string((int)juego->getVolumen(0)+1), juego->view.getCenter().x, juego->view.getCenter().y);
    cambiarTexto(1, "+", juego->view.getCenter().x+100, juego->view.getCenter().y);
    cambiarTexto(2, "Mute", juego->view.getCenter().x, juego->view.getCenter().y+100);
    cambiarTexto(3, "BACK", juego->view.getCenter().x+juego->view.getSize().x/2-300, juego->view.getCenter().y+juego->view.getSize().y/2-200);

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
                if(juego->getVolumen(0) >= 10){
                    juego->setVolumen(0 ,juego->getVolumen(0)-10);
                }
            break;
            case 1:
                if(juego->getVolumen(0) <= 90){
                    juego->setVolumen(0, juego->getVolumen(0)+10);
                }
            break;
            case 2:
                if(pausa == false){
                    juego->pausarMusica(0);
                    pausa = true;
                }else{
                    juego->reproducirMusica(0);
                    pausa = false;
                }
            break;
            case 3:
                man->back();
                resetSelectedItem();
            break;
        }
    }

    sprites[0]->posicionamiento(juego->view.getCenter().x-50, juego->view.getCenter().y+120);
    if(pausa == true){
        sprites[0]->recorte(150,0);
    }else{
        sprites[0]->recorte(0,0);
    }
}

