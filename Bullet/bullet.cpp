#include "bullet.h"
 

Bullet::Bullet(float p_x, float p_y, bool p_facing , int i) : body(){ //WIP fachada

    
    
    
    hitbox = new Rectangulo(10,10,p_x,p_y);
    velocidad=600; //quiza lo mejor es ponerlo como constantes
    lifetime=5;   //lo del comentario anterior

    facing=p_facing;

    
    dir = i;
    body = new Cuerpo(p_x, p_y, 10, 10, "Bala_fuego.png", 1, CIRCLE);
    /*body.setPosition(p_x, p_y); //wip fachada
    body.setFillColor(sf::Color(255,128,0)); //wip fachada
    body.setRadius(10); //wip fachada*/

    // sf::Texture * t; 
    // if(i == 1){
    //   t->loadFromFile("resources/Imagenes/Bala_fuego.png");
    // }else if(i == 2){
    //   t->loadFromFile("resources/Imagenes/Flecha.png");
    // }

    // body.setTexture(t);
    // if(i == 1){
    //  body.setTextureRect(sf::IntRect(0,0,128,128));
    // }else if(i == 2){
    //  body.setTextureRect(sf::IntRect(0,0,64,16));
    // }

}

void Bullet::update(float deltaTime){
    lifetime-=deltaTime;
    float sadX,sadY ;
    sadX = body->getPosicion()[0];
    sadY = body->getPosicion()[1];
    
      body->posicionamiento((facing ? 1 : -1)  * velocidad * deltaTime + sadX,sadY+0);

}
    

void Bullet::render(float porcentaje){
  
    body->render(porcentaje);
 
}
