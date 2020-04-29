#include "pajaro.h"

Pajaro::Pajaro(float x, float y) 
    : Enemigo(x, y, 192, 640, "Arqueros.png", 0.25){

    alturaActual = y;
    alturaMinRelativa = alturaMax + alturaActual;
    alturaMaxRelativa = alturaActual - alturaMax;
    direccion = -1;
    haPegado = false;

    velocidad = 50;

//    updateHitbox();
    
};

void Pajaro::updateHitbox(){

   /* vector<float> gp = cuerpo.getPosition();
    sf::FloatRect gbb = cuerpo.getGlobalBounds();

    coliAbajo.left = gp.x - gbb.width/2 + 20;
    coliAbajo.top = gp.y + gbb.height/2 -50;
    coliAbajo.width = 0;
    coliAbajo.height = 0;
    
    coliIzquierda.left = gp.x - gbb.width/2+12;
    coliIzquierda.top = gp.y - gbb.height/2 + 25 ;
    coliIzquierda.width = gbb.width/2-15;
    coliIzquierda.height = gbb.height - 50;

    coliDerecha.left = gp.x + 5;
    coliDerecha.top = gp.y - gbb.height/2 +25;
    coliDerecha.width = gbb.width/2 + 25;
    coliDerecha.height = gbb.height -50;

    coliArriba.left = gp.x - gbb.width/2 + 20;
    coliArriba.top = gp.y-gbb.height/2 +25;
    coliArriba.width = 0;
    coliArriba.height = 0;*/

}

void Pajaro::update(Player* entrada, float delta){
///las colisiones
    float posX = body->getPosicion()[0];
    float posY = body->getPosicion()[1];

    //posX = posX - delta*velocidad*0.6;
    //posY = posY + direccion*delta*velocidad;
    
    body->posicionamiento(-delta*velocidad*0.6, direccion*delta*velocidad);

    if(posY >= alturaMinRelativa){ //la parte más baja que puede bajar
        posY = alturaMinRelativa;
        direccion = -1; //NEGATIVO en Y, porque queremos que SUBA
    }
    else if(posY <= alturaMaxRelativa){ //la parte más alta que puede subir 

        posY = alturaMaxRelativa;
        direccion = 1; //POSITIVO en Y, porque queremos que BAJE

    }

    if(entrada != NULL){
        if(coliDerecha.intersects(entrada->getBody().getGlobalBounds())
            || coliIzquierda.intersects(entrada->getBody().getGlobalBounds())
            || coliAbajo.intersects(entrada->coliArriba)
            || coliArriba.intersects(entrada->coliAbajo)){
            if(!haPegado)
                entrada->setVidas(entrada->getVidas()-1);
            haPegado = true;
        }
    }
    updateHitbox();
};

void Pajaro::render( float porcentaje){
    body->render(porcentaje);
}
