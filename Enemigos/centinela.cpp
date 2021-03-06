#include "centinela.h"


Centinela::Centinela( float x, float y, int type) 
    : Enemigo(x, y, 192, 640, "Arqueros2.png", 0.5){

    shoot = false;
    shootTime = 0.0;

    body->setSize(150,320);
    body->Origen(150/2, 320/2);

    body->setSpriteAnimacion(3);

    tipo = type;
    modo  = 0;
    velocidad = 0.3;
    distanciaDisparo = 1000;
    distanciaAtaque = 200;
    vida = 3;

}


void Centinela::update(Player* player, float deltaTime){

    float posJugador = player->getBody()->getPosicion()[0];

    float local_diffX = posJugador - body->getPosicion()[0];
    float local_diffabs = abs(local_diffX);

    bool cambio; //no nos cambiamos de modo por defecto

    if(local_diffX/local_diffabs == -1){

        body->Scalar(0.5,0.5);

    }
    else{
        body->Scalar(-0.5,0.5);    
    }
    

    do{
        cambio = false;//no nos cambiamos de modo por defecto
        switch(modo){

            case(0): //está quieto
                body->setSpriteAnimacion(3);

                if(local_diffabs < distanciaAtaque){//si está lo suficientemente cerca, cambiamos
                    modo = 1;
                    if(tipo == 1)
                        modo = 2;
                    cambio = true;
                }
                if(local_diffabs < distanciaDisparo){//si está lo suficientemente cerca, cambiamos
                    modo = 2;
                    cambio = true;
                }
            break;
            case(1):
                if(local_diffabs < distanciaDisparo){//si está lo suficientemente cerca, cambiamos
                    modo = 2;
                    cambio = true;
                }
                else if(local_diffabs> distanciaAtaque){
                    modo = 1;
                    cambio = true;
                }
                else{//si no cambiamos, actualiza su posicion
                   actualizarPosicion((local_diffX/local_diffabs)*velocidad*deltaTime,0);                  
                }
                
            break;
            case(2):
                
                if(local_diffabs > distanciaDisparo){//si está lo suficientemente lejos, cambiamos
                    modo = 1;
                    if(tipo == 1)
                        modo = 0;
                    cambio = true;
                } 
                else{//DISPARA!!!! 
                    body->setSpriteAnimacion(0);
                    if(shootTime <= 0.0 && body->getPosicionX() == 3){
                        bool auxiliar;

                        if((local_diffX/local_diffabs) == 1){

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

    body->update(deltaTime);
};

Bullet* Centinela::disparar(){
    Bullet* devolver = NULL;

    if(shoot){

        shoot = false;

        vector<float> pos = body->getPosicion();

        devolver = new Bullet(pos[0], pos[1], direccion, 2, 1);
    }

    return(devolver);
}

bool Centinela::getShoot(){
    return shoot;
}

void Centinela::render( float porcentaje){
    body->render(porcentaje);
}
