#include "nube.h"

Nube::Nube(float x, float y) 
    : Enemigo(x, y, 192, 640, "Arqueros.png", 0.25){
    
    distanciaAtaque = 1000;
    modo = 0;    
    velocidad = 50;

    shootTime = 0.0f;
    vida = 3;
}

void Nube::update(sf::RectangleShape player, float delta){

    //float posJugador = player->getBody().getPosition().x;
    float posJugador = player.getPosition().x;

    float local_diffX = posJugador - body->getPosicion()[0];
    
    float local_diffabs = abs(local_diffX);
    
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
                actualizarPosicion((local_diffX/local_diffabs)*velocidad*delta,0); 
            }
            
        break;
        case(2): //le sigo y disparo
            actualizarPosicion((local_diffX/local_diffabs)*velocidad*delta,0); 
 
            if(shootTime <= 0.0){
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
        //cout<<"balas "<<pos[0]<<pos[1]<<endl;
        devolver = new Bullet(pos[0], pos[1], direccion, 2, 0);
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