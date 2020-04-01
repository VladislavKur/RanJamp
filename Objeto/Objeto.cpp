#pragma once
#include "Objeto.h"
#include <SFML/Graphics.hpp>
#include <iostream>

    
    
    
    Objeto::~Objeto(){}
    Objeto::Objeto(sf::Texture* tex,sf::Vector2f size,  sf::Vector2f Posicion,sf::Color color, int t){

        body.setFillColor(color);
      
         
            body.setSize(size);
            body.setTexture(tex);
            body.setPosition(Posicion);

        tipo = t;


    }

    //t --> tipo
    void Objeto::update(Player &otherBody){
        //std::cout<<"Tipo : "<< tipo <<std::endl;
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::E) && body.getGlobalBounds().intersects(otherBody.getBody().getGlobalBounds())){

            body.setSize(sf::Vector2f(0,0));
            body.setPosition(-500,-500); //lejos de la accion  
            std::cout << tipo << std:: endl;
            

            switch (tipo){
            
                case 1:
                    otherBody.setArma(1);
                    break;

                case 2:
                    otherBody.obtenerPU_SaltoDoble();
                    break;

                case 3:
                    otherBody.obtenerPU_Velocidad();
                    break;
            
            default:
                std:: cout <<"Default" << std::endl;
                break;
            } 

        }

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