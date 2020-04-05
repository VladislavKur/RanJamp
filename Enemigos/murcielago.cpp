#include "murcielago.h"


Murcielago::Murcielago(sf::Texture& tex) : Enemigo(tex,0,0){
    //cuerpo.setTexture(tex);
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

Murcielago::Murcielago(sf::Texture& tex, float x, float y) : Enemigo(tex,x,y){
    velocidad = 0.3;
    altura = 0;
    distanciaAtaque = 1000;
};

void Murcielago::update(Player& player, float delta){
    sf::RectangleShape body = player.getBody();

    float posJugadorX = body.getPosition().x;
    float posJugadorY = body.getPosition().y;

    float local_diffX = posJugadorX - posX;
    float local_diffY = posJugadorY - posY;
    float local_diffabsX = abs(local_diffX);
    float local_diffabsY = abs(local_diffY);

    diffX = 0; //inicialmente no se mueve
    diffY = 0; //inicialmente no se mueve


    bool cambio; //no nos cambiamos de modo por defecto
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

    if(cuerpo.getGlobalBounds().intersects(body.getGlobalBounds())){
        if(!haPegado)
            player.setVidas(player.getVidas()-1);
        if(player.getVidas() == 0 ){
            player.morir();
        }
        haPegado = true;
        morir();
    }
    
};

void Murcielago::render(float porcentaje){
    cuerpo.setPosition(
        posXanterior + diffX*porcentaje,
        posYanterior + diffY*porcentaje );
    
    Motor * motor = Motor::instance();
    motor->dibujo(cuerpo);

    /////HABLAR CON FIDEL
    //renderizar con getPosition() en vez de move()
};