#pragma once
#include "Objeto.h"
#include <SFML/Graphics.hpp>
#include <iostream>

    
    
    
    Objeto::~Objeto(){}
    Objeto::Objeto(sf::Vector2f Posicion, int t){

    
            body.setSize(sf::Vector2f(50,50));
            //body.setTexture(tex);
            body.setPosition(Posicion);

        tipo = t;


    }

    //t --> tipo
    void Objeto::update(Player &otherBody){
        sf::Texture *text = new sf::Texture ;
        //std::cout<<"Tipo : "<< tipo <<std::endl;
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::E) && body.getGlobalBounds().intersects(otherBody.getBody().getGlobalBounds())){

            body.setSize(sf::Vector2f(0,0));
            body.setPosition(-500,-500); //lejos de la accion  
           
            

            switch (tipo){
            
                case 1:
                    otherBody.setArma(1);
                    text->loadFromFile("resources/Imagenes/powerup1.png");
                    body.setTexture(text);
                    break;

                case 2:
                    otherBody.obtenerPU_SaltoDoble();
                    text->loadFromFile("resources/Imagenes/powerup2.png");
                    body.setTexture(text);
                    break;

                case 3:
                    otherBody.obtenerPU_Velocidad();
                    text->loadFromFile("resources/Imagenes/powerup3.png");
                    body.setTexture(text);
                    break;
            
            default:
                std:: cout <<"Default" << std::endl;
                break;
            } 

        }
        delete text; text = nullptr;

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