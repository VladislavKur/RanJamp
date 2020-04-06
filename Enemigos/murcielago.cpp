#include "murcielago.h"

Murcielago::Murcielago(float x, float y) : Enemigo(x,y){
     sf::Texture *text = new sf::Texture;

    cuerpo.setSize(sf::Vector2f(50.0f,80.0f));
    
    
    cuerpo.setOrigin(75/2, 75/2);

    if(!text->loadFromFile("resources/Imagenes/Murcielagos.png")) std::cout << "sadasds";
    
    cuerpo.setTexture(text);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 64, 64));
    cuerpo.setPosition(x,y);
    velocidad = 100;
    altura = 1;
    distanciaAtaque = 510;
    
    haPegado = false;
    colision.setSize(sf::Vector2f(50.0f,50.0f));
    colision.setPosition(x-10.0, y-10.0);
    colision.setFillColor(sf::Color::White);
};

void Murcielago::update(Player* player, float delta){
    sf::RectangleShape body = player->getBody();

    float posJugadorX = body.getPosition().x;
    float posJugadorY = body.getPosition().y;

    float local_diffX = posJugadorX - posX;
    float local_diffY = posJugadorY - posY;
    float local_diffabsX = abs(local_diffX);
    float local_diffabsY = abs(local_diffY);

    diffX = 0; //inicialmente no se mueve
    diffY = 0; //inicialmente no se mueve
    
    
    bool cambio = false; //no nos cambiamos de modo por defecto
    do{
        cambio = false;//no nos cambiamos de modo por defecto
        //std::cout<<"cambio-->"<<cambio<<false<<std::endl;
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
            player->setVidas(player->getVidas()-1);
        haPegado = true;
        std::cout<<"muero"<<std::endl;
        morir();
    }
    
};

void Murcielago::render(float porcentaje){
    cuerpo.setPosition(
        posXanterior + diffX*porcentaje,
        posYanterior + diffY*porcentaje );
    //std::cout << "ENTRO EN RENDER enemigo , " << posXanterior <<  ", " << posYanterior  << std::endl;
    Motor * motor = Motor::instance();
    motor->dibujo(cuerpo);
    
};