#include "Textura.h"

Textura::Textura(string entrada){

    t = new sf::Texture();
    motor->cargarSprite(*t, entrada, true);
  
}


Textura::~Textura(){
   if(t != nullptr){
    delete t;
    t = nullptr;
   }
}

Texture * Textura::getTexture(){
    return t;
}

