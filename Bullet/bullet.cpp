#include "bullet.h"
 

Bullet::Bullet(float p_x, float p_y, bool p_facing , int i, int cod_textura) : body(){ //WIP fachada

    
    
    
    velocidad=600; //quiza lo mejor es ponerlo como constantes
    lifetime=2;   //lo del comentario anterior

    facing=p_facing;
    
    
    dir = i;
    switch(cod_textura){
        case 0:
            body = new Cuerpo(p_x, p_y, 128, 128, "Bala_fuego.png", 1, CIRCLE);
            body->setSize(16, 16);
            hitbox = new Rectangulo(16,16,p_x-p_x/2,p_y-p_y/2);
            
        break;
        case 1:
            body = new Cuerpo(p_x, p_y, 64, 16, "Flecha.png", 1, RECTANGLE);
            hitbox = new Rectangulo(64,16,p_x,p_y);
        break;
    }

    if(dir == -1){
        body->rotar(90);
    }

    if(facing){
        body->Scalar(-1,1);
    }
   
    
    body->addAnimacion(0.1);

}

void Bullet::update(float deltaTime){
    lifetime-=deltaTime;

    if(dir == -1){
        body->moverse(0, (facing ? 1 : -1)  * velocidad * deltaTime);
    }
    else{
        body->moverse((facing ? 1 : -1)  * velocidad * deltaTime,0);
    }
    
    updateHitbox();
    
}
    

void Bullet::render(float porcentaje){
  
    body->render(porcentaje);
 
}

void Bullet::updateHitbox(){
    hitbox->setLeft(body->getPosicion()[0]);
    hitbox->setTop (body->getPosicion()[1]);
}

Bullet::~Bullet(){
    if(body != NULL){
        delete body;
        body = NULL;
    }
    if(hitbox != NULL){
        delete hitbox;
        hitbox = NULL;
    }
}