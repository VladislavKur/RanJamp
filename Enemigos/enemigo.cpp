#include "enemigo.h"

Enemigo::Enemigo(float x, float y, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala){
    modo = 0;
    body = new Cuerpo(x, y, sizeWidth, sizeHeight, fichero, escala, RECTANGLE);
    body->addAnimacion(0.1);
    coliDerecha = new Rectangulo(0,0,0,0);
    coliIzquierda = new Rectangulo(0,0,0,0);
    coliAbajo = new Rectangulo(0,0,0,0);
    coliArriba = new Rectangulo(0,0,0,0);
    muerto=false;
}

Enemigo::~Enemigo(){
        if(coliAbajo != NULL){
            delete coliAbajo;
            coliAbajo = NULL;
        }
        if(coliArriba != NULL){
            delete coliArriba;
            coliArriba = NULL;
        }
        if(coliIzquierda != NULL){
            delete coliIzquierda;
            coliIzquierda = NULL;
        } 
        if(coliDerecha != NULL){
            delete coliDerecha;
            coliDerecha = NULL;
        }
        if(body != NULL){
            delete body;
        }

}

void Enemigo::actualizarPosicion(float entradaX, float entradaY){
    body->posicionamiento(entradaX, entradaY);
}

bool Enemigo::comprobarColision(Cuerpo* cuerpo){
    bool dev = body->colisiona(cuerpo);
    if(dev)
        muerto =true;
    return dev;
}

bool Enemigo::setVidas(int v){
    
    vida = v;

    if(vida <= 0)
        muerto = true;
    else
        muerto = false;
    
    return muerto;
}

int Enemigo::getVidas(){
    return vida;
}

Cuerpo* Enemigo::getCuerpo(){
    return body;
}

void Enemigo::restarVida(int i){
    vida -= i;
    if(vida <= 0){
        muerto = true;
    }
    
}