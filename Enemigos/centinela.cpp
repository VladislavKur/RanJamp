#include "centinela.h"

Centinela::Centinela(sf::Texture& tex) : Enemigo(tex,0.0f,0.0f){
    /*posX = 0.0;
    posY = 0.0;
    posXanterior = 0.0;
    posYanterior = 0.0;
    diffX = 0.0;
    diffY = 0.0;
    modo = 0;*/
    cuerpo.setOrigin(75 / 2, 75 / 2);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
    cuerpo.setPosition(posX, posY);

};

Centinela::Centinela(sf::Texture& tex, float x, float y) : Enemigo(tex,x,y){
    /*posX = x;
    posY = y;
    diffX= 0.0;
    diffY= 0.0;
    posXanterior = x;
    posYanterior = y;*/
    modo = 0;
    //cuerpo.setTexture(tex);
    cuerpo.setOrigin(75 / 2, 75 / 2);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
    cuerpo.setPosition(x, y);
};

/*void Centinela::actualizarPosicion(float entradaX, float entradaY){

    posXanterior = posX;
    posYanterior = posY;
    posX += entradaX;
    posY += entradaY;
    diffX = posX - posXanterior;
    diffY = posY - posYanterior;

};*/

void Centinela::update(sf::RectangleShape& entrada, float deltaTime){

    float posJugador = entrada.getPosition().x;

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
                    entrada.setScale(0.5,0.5);

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