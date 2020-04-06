#include "centinela.h"


Centinela::Centinela( float x, float y, int type) : Enemigo(x,y){
    sf::Texture *text = new sf::Texture;

    shoot = false;

    shootTime = 0.0;

    cuerpo.setSize(sf::Vector2f(150.0f,250.0f));
    cuerpo.setPosition(100, 100);

    cuerpo.setOrigin(75, 150);

    if(!text->loadFromFile("resources/Imagenes/Arqueros.png")) std::cout << "sadasds";
    
    cuerpo.setTexture(text);
    cuerpo.setTextureRect(sf::IntRect(0, 0, 192 , 640));
   // cuerpo.setScale(1.5, 2.5);

    tipo = type;
    modo  = 0;
    velocidad = 0.3;
    distanciaDisparo = 1000;
    distanciaAtaque = 200;

};


void Centinela::update(Player* player, float deltaTime){

    sf::RectangleShape body = player->getBody();

    float posJugador = body.getPosition().x;

    float local_diffX = posJugador - posX;
    float local_diffabs = abs(local_diffX);

    diffX = 0; //inicialmente no se mueve
    diffY = 0; //inicialmente no se mueve

    bool cambio; //no nos cambiamos de modo por defecto
     do{
        cambio = false;//no nos cambiamos de modo por defecto
        switch(modo){

            case(0): //está quieto
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
                else{//DISPARA!!!! necesitamos el trabajo de vermivlad

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

                        shootTime -= deltaTime;

                    }
                    
                    //juego->dispararEnemigo(deltaTime,posX,posY,auxiliar);
                    

                }
                
            break;

        }
    }while(cambio); //si cambiamos de modo, volvemos a iterar en el bucle

};

void Centinela::render( float porcentaje){
    cuerpo.setPosition(
        posXanterior + diffX*porcentaje,
        posYanterior + diffY*porcentaje );

    Motor * motor = Motor::instance();
    motor->dibujo(cuerpo);
}

Bullet* Centinela::disparar(){
    Bullet* devolver = NULL;

    if(shoot){

        shoot = false;

        devolver = new Bullet(posX,posY,direccion, 2);
    }

    return(devolver);
}