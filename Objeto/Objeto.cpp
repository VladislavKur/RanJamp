#pragma once
#include "Objeto.h"
#include <SFML/Graphics.hpp>
#include <iostream>

    
    
    
    Objeto::~Objeto(){}
    Objeto::Objeto(sf::Vector2f Posicion, int t){
             sf::Texture *text = new sf::Texture ;

 
            text->loadFromFile("resources/Imagenes/powerup1.png");
                    body.setTexture(text);
            body.setSize(sf::Vector2f(50,50));
            //body.setTexture(tex);
            body.setPosition(Posicion);

        tipo = t;
    

    }

    void Objeto::destroirObjeto(Objeto * obj){
        delete obj;
    }

    //t --> tipo
    void Objeto::update(Player &otherBody){
        

    }


    void Objeto::recogido(){

    }

    void Objeto::setTipo(int t){
        tipo = t;
    }

    int Objeto::getTipo(){
         return tipo;
    }

    sf::RectangleShape Objeto::getBody(){
    return body;
}



    void Objeto:: render(){
        Motor * motor = Motor::instance();
        motor->dibujo(body); 
    }