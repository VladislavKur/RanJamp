#include "reptante.h"

Reptante::Reptante(sf::Texture& tex) : Enemigo(tex,0,0){
    //cuerpo.setTexture(tex);
    /*posX = 0.0;
    posY = 0.0;
    posXanterior = 0.0;
    posYanterior = 0.0;
    diffX = 0.0;
    diffY = 0.0;
    modo = 0;*/
    cuerpo.setOrigin(75 / 2, 75 / 2);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
    cuerpo.setPosition(posX, posY);
    cuerpo.setTexture(tex);
};

Reptante::Reptante(sf::Texture& tex, float x, float y) : Enemigo(tex,x,y){
    /*posX = x;
    posY = y;
    diffX= 0.0;
    diffY= 0.0;
    posXanterior = x;
    posYanterior = y;*/
    modo = 0;
    //cuerpo.setTexture(tex);
    cuerpo.setOrigin(75 / 2, 75 / 2);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
    cuerpo.setTexture(tex);
    cuerpo.setPosition(x, y);
    
    
};

void Reptante::update(sf::RectangleShape& entrada, float delta){
///las colisiones
    cuerpo.move(delta, 0);
};

void Reptante::render( float porcentaje){
    cuerpo.setPosition(
        posXanterior + diffX*porcentaje,
        posYanterior + diffY*porcentaje );

    Motor * motor = Motor::instance();
    motor->dibujo(cuerpo);
}