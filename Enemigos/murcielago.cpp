#include "murcielago.h"

Murcielago::Murcielago(float x, float y) 
    : Enemigo(x, y, 64, 64, "Murcielagos.png", 1){
    
    velocidad = 100;
    altura = 1;
    distanciaAtaque = 510;

    body->Origen(64/2, 64/2);
    
    haPegado = false;
    
}

void Murcielago::update(Player* player, float delta){//WIP fachada
    hud * Hud = hud::instance();
    float posJugadorX = player->getBody()->getPosicion()[0]; //WIP FACHADA
    float posJugadorY = player->getBody()->getPosicion()[1];

    float local_diffX = posJugadorX - body->getPosicion()[0];
    float local_diffY = posJugadorY - body->getPosicion()[1];
    float local_diffabsX = abs(local_diffX);
    float local_diffabsY = abs(local_diffY);
    
    bool cambio = false; //no nos cambiamos de modo por defecto
    
    do{
        cambio = false;//no nos cambiamos de modo por defecto
        
        switch(modo){
            case(0): //está quieto
                if(local_diffabsX < distanciaAtaque){//si está lo suficientemente cerca, cambiamos
                    modo = 1;
                    cambio = true;
                }
            break;
            case(1)://diagonal
                if(local_diffY <= altura){
                   modo = 2;
                   cambio = true;
                }
                else{
                    float movimientoSuaveX = (local_diffX/local_diffabsX)*velocidad*delta;
                    float movimientoSuaveY = (local_diffY/local_diffabsY)*velocidad*delta;
                    
                    body->moverse(movimientoSuaveX,movimientoSuaveY); 
                }
                
            break;
            case(2): //recto

                if(direccion == 0)
                    direccion = local_diffX/local_diffabsX;
                body->moverse(direccion*velocidad*delta,0);     
            break;

        }
        
    }while(cambio); //si cambiamos de modo, volvemos a iterar en el bucle

    if(coliDerecha->getIntersect(*player->getBody()->getGlobalBounds())
    || coliIzquierda->getIntersect(*player->getBody()->getGlobalBounds())
    || coliAbajo->getIntersect(*player->getColiArriba())
    || coliArriba->getIntersect(*player->getColiAbajo())
    ){
        if(!haPegado)
            //player->setVidas(player->getVidas()-1);
            Hud->restarVidas();
        muerto=true;
        haPegado = true;
    }
    body->update(delta);
}

void Murcielago::updateHitbox(){

    float gpx = body->getPosicion()[0];
    float gpy = body->getPosicion()[1];
    std::vector<float> gbb = body->getBounds();

    coliAbajo->setLeft(gpx - gbb[2]/2 + 20);
    coliAbajo->setTop(gpy + gbb[3]/2 - 50);
    coliAbajo->setWidth(0);
    coliAbajo->setHeight(0);
    
    coliIzquierda->setLeft( gpx -  gbb[2]/2+12); //rojo
    coliIzquierda->setTop( gpy -  gbb[3]/2 + 25) ;
    coliIzquierda->setWidth( gbb[2]/2-15);
    coliIzquierda->setHeight(gbb[3] -50);

    coliDerecha->setLeft(gpx+5);
    coliDerecha->setTop(gpy -  gbb[3]/2 +25);
    coliDerecha->setWidth(gbb[2]/2 +25);
    coliDerecha->setHeight(gbb[3] -50);

    coliArriba->setLeft(gpx -  gbb[2]/2 + 20);
    coliArriba->setTop( gpy-  gbb[3]/2 +25);
    coliArriba->setWidth(0);
    coliArriba->setHeight(0);
}

void Murcielago::render(float porcentaje){
    body->render(porcentaje);
}
