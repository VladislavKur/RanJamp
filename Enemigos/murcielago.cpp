#include "murcielago.h"

Murcielago::Murcielago(float x, float y) 
    : Enemigo(x, y, 64, 64, "Murcielagos.png", 1){
    
    velocidad = 100;
    altura = 1;
    distanciaAtaque = 510;
    
    haPegado = false;
    
}

void Murcielago::update(Player* player, float delta){//WIP fachada
    sf::RectangleShape bodyJ = player->getBody();

    float posJugadorX = bodyJ.getPosition().x; //WIP FACHADA
    float posJugadorY = bodyJ.getPosition().y;

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
                    
                    actualizarPosicion(movimientoSuaveX,movimientoSuaveY); 
                }
                
            break;
            case(2): //recto

                if(direccion == 0)
                    direccion = local_diffX/local_diffabsX;
                actualizarPosicion(direccion*velocidad*delta,0);     
            break;

        }
        
    }while(cambio); //si cambiamos de modo, volvemos a iterar en el bucle

    if(coliDerecha.intersects(bodyJ.getGlobalBounds())
    || coliIzquierda.intersects(bodyJ.getGlobalBounds())
    || coliAbajo.intersects(player->coliArriba)
    || coliArriba.intersects(player->coliAbajo)
    ){
        if(!haPegado)
            player->setVidas(player->getVidas()-1);
        
        haPegado = true;
    }
    
}

void Murcielago::updateHitbox(){
    sf::Vector2f gp = cuerpo.getPosition();
    sf::FloatRect gbb = cuerpo.getGlobalBounds();
    
    coliAbajo.left = gp.x - gbb.width/2 + 20;
    coliAbajo.top = gp.y + gbb.height/2 -50;
    coliAbajo.width =0;
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
    coliArriba.height = 0;
}

void Murcielago::render(float porcentaje){
    body->render(porcentaje);
}
