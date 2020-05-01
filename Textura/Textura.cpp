#include "Textura.h"



Textura::Textura(string entrada){

    t = new sf::Texture();
    bool cargado = motor->cargarSprite(*t, entrada);
}


Textura::Textura(const char * entrada){

    t = new sf::Texture();
    bool cargado = motor->cargarSprite(*t, entrada);
}


Textura::~Textura(){

}

Texture * Textura::getTexture(){
    return t;
}