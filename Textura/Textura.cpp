#include "Textura.h"

Textura::Textura(string entrada){

    t = new sf::Texture();
    bool cargado = motor->cargarSprite(*t, entrada, true);
  
}


Textura::~Textura(){
   delete t;
}

Texture * Textura::getTexture(){
    return t;
}

