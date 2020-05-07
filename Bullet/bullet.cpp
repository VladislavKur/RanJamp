#include "bullet.h"
 

Bullet::Bullet(float p_x, float p_y, bool p_facing , int i) : body(){ //WIP fachada

    
    
    
    hitbox = new Rectangulo(10,10,p_x,p_y);
    velocidad=600; //quiza lo mejor es ponerlo como constantes
    lifetime=5;   //lo del comentario anterior

    facing=p_facing;

    
    dir = i;
    body = new Cuerpo(p_x, p_y, 10, 10, "Bala_fuego.png", 1, CIRCLE);
    


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
