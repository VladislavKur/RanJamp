#include "Rectangulo.h"

Rectangulo::~Rectangulo(){
    
}
Rectangulo::Rectangulo(float w, float h, float l , float t){


    body.left = l;
    body.top = t;
    body.width = w;
    body.height = h;

}

bool Rectangulo::getIntersect(Rectangulo & r){
    return body.intersects(r.getBody());
}

void Rectangulo::posicionar(float l, float t){
    body.left = l;
    body.top = t;
}