#include "nube.h"

Nube::Nube(float x, float y) 
    : Enemigo(x, y, 256, 256, "Nube.png", 0.25){
    
    distanciaAtaque = 1000;
    modo = 0;    
    velocidad = 100;

    shootTime = 0.0f;
}

void Nube::update(Player* player, float delta){

    float posJugador = player->getBody()->getPosicion()[0];
    float posJugadorY = player->getBody()->getPosicion()[1];

    float local_diffX = posJugador - body->getPosicion()[0];
    float local_diffY = posJugador - body->getPosicion()[1];
    
    float local_diffabs = abs(local_diffX);
    float local_diffabsY = abs(local_diffY);
    
    //float velPlayer =  900.0/1000.0;

    switch(modo){

        case(0): //está quieto
            if(local_diffabs < distanciaAtaque){//si está lo suficientemente cerca, cambiamos
                modo = 1;
            }
        break;
        case(1): //ataque -> le busco
            if(local_diffabs> distanciaAtaque){
                modo = 0;
            }else if(local_diffabs <= 3){                
                modo = 2;            
            }
            else{
                body->moverse((local_diffX/local_diffabs)*velocidad*delta,0); 
            }
            
        break;
        case(2): //le sigo y disparo
            //body->moverse((local_diffX/local_diffabs)*velocidad*delta,0); 

            if(local_diffabs <= 3 || local_diffabs >= -3){                
                modo = 1;            
            }

            if(shootTime <= 0.0){
                
                if((local_diffY/local_diffabsY) == 1){
                    direccion = true;
                }
                else{
                    direccion = false;
                }
                                
                shoot = true;
                shootTime = 1.5;
                
            }
            else{
                shootTime -= delta;
            }
            
        break;

    }

    body->update(delta);
}

Bullet* Nube::disparar(){
    Bullet* devolver = NULL;

    if(shoot){

        shoot = false;

        vector<float> pos = body->getPosicion();
        
        devolver = new Bullet(pos[0], pos[1], direccion, -1, 0);
    }

    return devolver;

}
bool Nube::getShoot(){
    return shoot;
}

void Nube::render(float porcentaje){
    body->render(porcentaje);
    //cout<<body->getPosicion()[0]<<" "<<body->getPosicion()[1]<<endl;
}