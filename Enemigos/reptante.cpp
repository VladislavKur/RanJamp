#include "reptante.h"


Reptante::Reptante(float x, float y) : Enemigo(x,y){
    sf::Texture *text = new sf::Texture;

    cuerpo.setSize(sf::Vector2f(100.0f,100.0f));
    cuerpo.setPosition(100, 100);

    cuerpo.setOrigin(75/2, 75/2);

    if(!text->loadFromFile("resources/sprites.png")) std::cout << "sadasds";
    
    cuerpo.setTexture(text);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));

    modo = 0;    
    
};

void Reptante::update(Player* entrada, float delta){
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