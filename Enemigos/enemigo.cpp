#include "enemigo.h"

Enemigo::Enemigo(float x, float y, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala){
    modo = 0;
    body = new Cuerpo(x, y, sizeWidth, sizeHeight, fichero, escala, RECTANGLE);
}

Enemigo::~Enemigo(){
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

Cuerpo* Enemigo::getCuerpo(){
    return body;
}