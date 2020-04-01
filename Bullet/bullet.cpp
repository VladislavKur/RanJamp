#include "bullet.h"

  Bullet* Bullet::bullets[maxBullets];
  bool Bullet::array_inicializado=false;


//Necesario porque si no los punteros apuntan a drecciones aleatorias
  void Bullet::initBulletArray(){
    for(int i = 0 ; i < maxBullets ; i++){
        Bullet::bullets[i]=NULL;
    }
  }
  

Bullet::Bullet(float p_x, float p_y, bool p_facing) : body(){
    if(!array_inicializado){
        initBulletArray();
        array_inicializado=true;
    }

    lifetime=5;

    facing=p_facing;
    
    body.setPosition(p_x, p_y);
    body.setFillColor(sf::Color(255,128,0));
    body.setRadius(10);
}

void Bullet::update(float deltaTime){
    lifetime-=deltaTime;
    body.move( (facing ? 1 : -1) * 1200*deltaTime,0);
}

void Bullet::render(){
  Motor * motor = Motor::instance();
  motor->dibujo(body);
}