#include "bullet.h"

  Bullet* Bullet::bullets[maxBullets];
  bool Bullet::array_inicializado=false;


//Necesario porque si no los punteros apuntan a drecciones aleatorias
  void Bullet::initBulletArray(){
    for(int i = 0 ; i < maxBullets ; i++){
        Bullet::bullets[i]=NULL;
    }
  }
  

Bullet::Bullet(float p_x, float p_y, bool p_facing , int i) : body(){
    if(!array_inicializado){
        initBulletArray();
        array_inicializado=true;
    }

    velocidad=600;
    lifetime=5;

    facing=p_facing;
    
    body.setPosition(p_x, p_y);
    body.setFillColor(sf::Color(255,128,0));
    body.setRadius(10);
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
    body.move( (facing ? 1 : -1) * velocidad*deltaTime,0);
}

void Bullet::render(){
  Motor * motor = Motor::instance();
  motor->dibujo(body);
}