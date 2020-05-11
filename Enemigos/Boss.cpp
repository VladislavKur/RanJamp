#include "Boss.h"

Boss::Boss( float x, float y) 
    : Enemigo(x, y, 232, 134, "boss.png", 2.0){

    shoot = false;
    shootTime = 0.0;

    body->setSize(400,200);
    body->Origen(400/2, 200/2);    
    body->addAnimacion(0.1);
    
    modo  = 0;
    vida = 15;
    velocidad = 50;
    distanciaDisparo = 600; //dispara contra jugador
    distanciaAtaque = 200;   //le pega

    mano = new Rectangulo(60, 60, x-(x/9), y-(y/70));
    
    haPegado = false;


}


void Boss::update(Player *player, float deltaTime){
    hud * Hud = hud::instance();
    float posJugadorX = player->getBody()->getPosicion()[0];
    float posJugadorY = player->getBody()->getPosicion()[1];

    float local_diffX = posJugadorX - body->getPosicion()[0];
    float local_diffY = posJugadorY - body->getPosicion()[1];

    float local_diffabsX = abs(local_diffX);
    float local_diffabsY = abs(local_diffY);

    bool cambio; //no nos cambiamos de modo por defecto
    do{
        cambio = false;//no nos cambiamos de modo por defecto
        
        switch(modo){
            case(0): //está quieto
                if(local_diffabsX < distanciaAtaque){//si está lo suficientemente cerca, cambiamos -> golpe
                    modo = 1;
                    cambio = true;
                }else if(local_diffabsX < distanciaDisparo){//si está lo suficientemente cerca, cambiamos ->disparo
                    modo = 2;
                    cambio = true;
                }
                else{
                    body->setSpriteAnimacion(0);
                }
            break;
            case(1):                
                if(local_diffabsX > distanciaAtaque){//si está lo suficientemente cerca, cambiamos -> disparo
                    modo = 0;
                    cambio = true;
                }
                else {//si no cambiamos, actualiza su posicion
                    body->setSpriteAnimacion(3);

                        float posx = body->getPosicion()[0];
                        float posy = body->getPosicion()[1];
                        
                        if((local_diffX/local_diffabsX) == -1){
                            mano->posicionar(posx-(posx/9), posy-(posy/70));
                        }
                        else{
                            mano->posicionar(posx+(posx/14), posy-(posy/70));
                        }
                        
                        cout<<posx<<endl;


                    if(body->getPosicionX() != 7)
                        haPegado = true;
                    if(body->getPosicionX() == 7){
                        //if(body->colisiona(player->getBody()) && haPegado){
                        if((player->getColiDerecha()->getIntersect(*mano) 
                            || player->getColiIzquierda()->getIntersect(*mano))&& haPegado){
                            haPegado = false;
                            // player->setVidas(player->getVidas() - 2);
                            Hud->restarVidas();
                            Hud->restarVidas();
                            player->getBody()->moverse((local_diffX/local_diffabsX)*80, 0+30);//empuja al jugador
                        }
                    }                    
                }
                
            break;
            case(2):
                if(local_diffabsX < distanciaAtaque){ //si está lo suficientemente lejos, cambiamos
                    modo = 1;
                    cambio = true;
                }
                else if(local_diffabsX > distanciaDisparo){//si está lo suficientemente cerca, cambiamos -> disparo
                    modo = 0;
                    cambio = true;
                } 
                else{//DISPARA
                    body->setSpriteAnimacion(2); //disparar

                    if(shootTime <= 0.0){
                        bool auxiliar;

                        if((local_diffX/local_diffabsX) == 1){
                            auxiliar = true;
                        }
                        else{
                            auxiliar = false;
                        }
                        
                        direccion = auxiliar;
                        
                        shoot = true;
                        shootTime = 3.0;
                    }
                    else{
                        shootTime -= deltaTime;
                    }
                }           
            break;
        }

    }while(cambio); //si cambiamos de modo, volvemos a iterar en el bucle

    body->Scalar((local_diffX/local_diffabsX), 1);

    body->update(deltaTime);
}

Bullet* Boss::disparar(){
    Bullet* devolver = NULL;

    if(shoot){

        shoot = false;

        vector<float> pos = body->getPosicion();
        
        devolver = new Bullet(pos[0], pos[1], direccion, 2, 0);
        devolver->getBody()->Scalar(1.5,1.5);
    }

    return(devolver);
}

bool Boss::getShoot(){
    return shoot;
}
bool Boss::getPegado(){
    return haPegado;
}

void Boss::setPegado(bool p){
    haPegado = p;
}

void Boss::render( float porcentaje){
    body->render(porcentaje);
}
