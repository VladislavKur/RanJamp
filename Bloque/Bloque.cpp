#include "Bloque.h"

Bloque::Bloque(Textura * t){
     motor = Motor::instance();

    s = new sf::Sprite();
    

    motor->setTextura(*s, *t->getTexture());
}

void Bloque::setTextureRect(int x, int y, int ancho, int largo){
    motor->recorte(*s, x,y ,ancho,largo);
}

void Bloque::setPosition(float x, float y){
    motor->posicionar(*s, x , y);
}

void Bloque::render(){
    motor->dibujo(*s);
}