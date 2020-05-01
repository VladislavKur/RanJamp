#pragma once
#include "Objeto.h"
#include <SFML/Graphics.hpp>
#include <iostream>

    
    
    
    Objeto::~Objeto(){}
    Objeto::Objeto(float x, float y, int t){
            
 
            tipo = t;
            hitbox = new Rectangulo(50,50,x,y);
            body = new Cuerpo(x,y,50,50,"powerup1.png",1,RECTANGLE);
           
            
        
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

    Cuerpo* Objeto::getBody(){
    return body;
}



    void Objeto::render(float porcentaje){
        
        body->render(porcentaje);
    }

    