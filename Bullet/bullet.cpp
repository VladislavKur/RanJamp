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

    if(facing){
        body->Scalar(-1,1);
    }

    
    
    body->addAnimacion(0.1);
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
    
      body->moverse((facing ? 1 : -1)  * velocidad * deltaTime,0);
    //cout<<body->getPosicion()[0]<<"//////"<<body->getPosicion()[1]<<endl;
    updateHitbox();
    cout<<body->getPosicion()[0]<<"//////"<<hitbox->getLeft()<<endl;
    
}
    

void Bullet::render(float porcentaje){
  
    body->render(porcentaje);
 
}

void Bullet::updateHitbox(){
    hitbox->setLeft(body->getPosicion()[0]);
    hitbox->setTop (body->getPosicion()[1]);
}
