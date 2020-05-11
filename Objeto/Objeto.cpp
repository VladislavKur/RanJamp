#include "Objeto.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Objeto.h"

    
    
    
    Objeto::~Objeto(){
        if(body != nullptr){
            delete body;
            body = nullptr;
        }
        if(hitbox != nullptr){
            delete hitbox;
            hitbox = nullptr;
        }
    }
    Objeto::Objeto(float x, float y, int t){
            
 
        tipo = t;
        hitbox = new Rectangulo(50,50,x,y);
        string fichero;
        switch(tipo){
            case 0:
                fichero = "velocidad.png";
            break;

            case 1:
                fichero="powerup1.png";
            break;
                
            case 2:
                fichero="saltos.png";
            break;

            case 3:
                fichero="slow.png";
            break;

            case 4:
                fichero="slow.png";
            break;

            default:
                fichero="estrella.png";
            break;
        }
        body = new Cuerpo(x,y,32,32,fichero,1,RECTANGLE);
        body->setSize(50,50);
        body->addAnimacion(0.1);
            
        
    }

    void Objeto::destroirObjeto(Objeto * obj){
        delete obj;
    }

    //t --> tipo
    // void Objeto::update(Player &otherBody){
        

    // }


    // void Objeto::recogido(){

    // }

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

    