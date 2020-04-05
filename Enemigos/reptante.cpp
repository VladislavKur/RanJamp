#include "reptante.h"


Reptante::Reptante(float x, float y) : Enemigo(x,y){
     /*sf::Texture tex;
    if (!tex.loadFromFile("resources/sprites.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    modo = 0;
    cuerpo.setTexture(tex);
    cuerpo.setOrigin(75 / 2, 75 / 2);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
    cuerpo.setTexture(tex);
    cuerpo.setPosition(x, y);*/
    
    
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