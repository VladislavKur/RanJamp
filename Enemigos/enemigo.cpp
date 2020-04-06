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
void Enemigo::morir(){
    //cuerpo.setScale(sf::Vector2f(cuerpo.getScale().x*0.9, cuerpo.getScale().y*0.9));
    //if(cuerpo.getScale().x < 0.1)
    cuerpo.setScale(0,0);
    //Juego* juego = Juego::instance();
    //juego->matarEnemigo(this);
    vida = 0;
     
}
void Enemigo::updateHitbox(){
    sf::Vector2f gp = cuerpo.getPosition();
    sf::FloatRect gbb = cuerpo.getGlobalBounds();

    coliAbajo.left = gp.x - gbb.width/2 + 20;
    coliAbajo.top = gp.y + gbb.height/2 -30;
    coliAbajo.width = gbb.width/2 -40;
    coliAbajo.height = 5;
    
    coliIzquierda.left = gp.x - gbb.width/2+12;
    coliIzquierda.top = gp.y - gbb.height/2 + 25 ;
    coliIzquierda.width = gbb.width/2-15;
    coliIzquierda.height = gbb.height -25;

    coliDerecha.left = gp.x + 5;
    coliDerecha.top = gp.y - gbb.height/2 +25;
    coliDerecha.width = gbb.width/2 + 30;
    coliDerecha.height = gbb.height -25;

    coliArriba.left = gp.x - gbb.width/2 + 20;
    coliArriba.top = gp.y-gbb.height/2 +25;
    coliArriba.width = gbb.width - 40;
    coliArriba.height = 5;
}

void Enemigo::actualizarPosicion(float entradaX, float entradaY){

    posXanterior = posX;
    posYanterior = posY;
    posX += entradaX;
    posY += entradaY;
    diffX = posX - posXanterior;
    diffY = posY - posYanterior;

};