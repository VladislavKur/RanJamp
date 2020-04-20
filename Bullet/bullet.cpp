#include "bullet.h"
 

Bullet::Bullet(float p_x, float p_y, bool p_facing , int i) : body(){ //WIP fachada

    velocidad=600; //quiza lo mejor es ponerlo como constantes
    lifetime=5;   //lo del comentario anterior

    facing=p_facing;
    dir = i;
    body.setPosition(p_x, p_y); //wip fachada
    body.setFillColor(sf::Color(255,128,0)); //wip fachada
    body.setRadius(10); //wip fachada
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
    if(dir == 0)
      body.move( (facing ? 1 : -1) * velocidad*deltaTime,0);
    else
      body.move(0, (facing ? 1 : -1) * velocidad*deltaTime);
    
    //falta aplicar lo de los enemigos de antonioMonica pero aqui para la interpolacion
}

void Bullet::render(){
  Motor * motor = Motor::instance();
  motor->dibujo(body);
  //falta aplicar lo de los enemigos de antonioMonica pero aqui para la interpolacion
}
