#include "Animacion.h"
#include <SFML/Graphics.hpp>
#include <iostream>


Animacion::~Animacion(){}

Animacion::Animacion(std::string fichero,sf::Vector2u cantidadImagenes, float SwitchTimeSprite, sf::Vector2f tamanyoCuerpo,sf::Vector2f tamanyoSprite){

    Motor * motor = Motor::instance();
    sf::Texture textura;

    if(!motor->cargarSprite(textura,fichero)){
        std::cerr << "Error cargando la imagen " << fichero;
        //hacer handle del error WIP
    }

    motor->setTamanyoCuerpo(this->body,tamanyoCuerpo);
    motor->setTextura(this->body, textura);
    motor->recorte(this->body,0*75,2*75,75,75);

    this->cantidadImagenes=cantidadImagenes; //cantidad de imagenes de spritesheet
    this->SwitchTimeSprite=SwitchTimeSprite; //el tiempo que tarda de una imagen a otra

    spriteActual.y= 0;  //empieza con el primero
    spriteActual.x = 0; //empieza con el primero
    
    temporizador = 0; //el temporizador se inicia a 0


    textureRect.height = textura.getSize().y/ float(cantidadImagenes.y); //
    textureRect.width = textura.getSize().x/ float(cantidadImagenes.x);

}

void Animacion::Update(float deltaTime){


    textureRect.left = spriteActual.x * textureRect.width;
    textureRect.top = spriteActual.y * textureRect.height;

}

void Animacion::setSprite(sf::Vector2u sprites){
    spriteActual.x = sprites.x;
    spriteActual.y = sprites.y;
}