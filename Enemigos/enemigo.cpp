#include "enemigo.h"

Enemigo::Enemigo(float x, float y){
    
    posX = x;
    posY = y;
    diffX= 0.0;
    diffY= 0.0;
    posXanterior = x;
    posYanterior = y;
    modo = 0;
    vida = 1;

};
Enemigo::~Enemigo(){
  
}
void Enemigo::morir(){ //WIP eliminar probablemente
    //cuerpo.setScale(sf::Vector2f(cuerpo.getScale().x*0.9, cuerpo.getScale().y*0.9));
    //if(cuerpo.getScale().x < 0.1)
    cuerpo.setScale(0,0);
    //Juego* juego = Juego::instance();
    //juego->matarEnemigo(this);
    vida = 0;
     
}


void Enemigo::actualizarPosicion(float entradaX, float entradaY){

    posXanterior = posX;
    posYanterior = posY;
    posX += entradaX;
    posY += entradaY;
    diffX = posX - posXanterior;
    diffY = posY - posYanterior;

};
