#include "Textura.h"



Textura::Textura(string entrada){

    t = new sf::Texture();
    motor->cargarSprite(*t, entrada, true);
}



Textura::~Textura(){

}

Texture * Textura::getTexture(){
    return t;
}