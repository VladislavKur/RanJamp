#include "centinela.h"


Centinela::Centinela( float x, float y) : Enemigo(x,y){
   sf::Texture *text = new sf::Texture;

    cuerpo.setSize(sf::Vector2f(100.0f,100.0f));
    cuerpo.setPosition(100, 100);

    cuerpo.setOrigin(75/2, 75/2);

    if(!text->loadFromFile("resources/sprites.png")) std::cout << "sadasds";
    
    cuerpo.setTexture(text);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));

    modo  = 0;
    velocidad = 0.3;
    distanciaDisparo = 100;
    distanciaAtaque = 100;

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
                    cambio = true;
                } 
                else{//DISPARA!!!! necesitamos el trabajo de vermivlad

                    ////WIP
                    ////WIP
                    ////WIP
                    ////WIP
                    ////WIP
                    body.setScale(0.5,0.5);

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