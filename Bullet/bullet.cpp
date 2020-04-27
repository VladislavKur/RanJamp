#include "bullet.h"
 

Bullet::Bullet(float p_x, float p_y, bool p_facing , int i) : body(){ //WIP fachada

    velocidad=600; //quiza lo mejor es ponerlo como constantes
    lifetime=5;   //lo del comentario anterior

    facing=p_facing;
    
    body.setPosition(p_x, p_y); //wip fachada
    body.setFillColor(sf::Color(255,128,0)); //wip fachada
    body.setRadius(10); //wip fachada

}

void Bullet::update(float deltaTime){
    lifetime-=deltaTime;
    body.move( (facing ? 1 : -1) * velocidad*deltaTime,0);
    //falta aplicar lo de los enemigos de antonioMonica pero aqui para la interpolacion
}

void Bullet::render(){
  Motor * motor = Motor::instance();
  motor->dibujo(body);
  //falta aplicar lo de los enemigos de antonioMonica pero aqui para la interpolacion
}
