#include "pajaro.h"

Pajaro::Pajaro(float x, float y) 
    : Enemigo(x, y, 64, 64, "Murcielagos_BLUE.png", 1){

    alturaActual = y;
    alturaMinRelativa = alturaMax + alturaActual;
    alturaMaxRelativa = alturaActual - alturaMax;
    direccion = -1;
    haPegado = false;

    velocidad = 50;
    vida = 2;
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

void Pajaro::update(Player* player, float delta){
///las colisiones
    //float posX = body->getPosicion()[0];
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

    if(player != NULL){
        if(coliDerecha->getIntersect(*player->getBody()->getGlobalBounds())
        || coliIzquierda->getIntersect(*player->getBody()->getGlobalBounds())
        || coliAbajo->getIntersect(*player->getColiArriba())
        || coliArriba->getIntersect(*player->getColiAbajo())){
            if(!haPegado)
                player->setVidas(player->getVidas()-1);
            haPegado = true;
        }
    }
    updateHitbox();
};

void Pajaro::render( float porcentaje){
    body->render(porcentaje);
}
