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
    
    //if(cuerpo.getGlobalBounds().intersects(body.getGlobalBounds())){
    if(coliDerecha.intersects(body.getGlobalBounds())
    || coliIzquierda.intersects(body.getGlobalBounds())
    || coliAbajo.intersects(player->coliArriba)
    || coliArriba.intersects(player->coliAbajo)
    ){
        if(!haPegado)
            player->setVidas(player->getVidas()-1);
        haPegado = true;
        std::cout<<"muero"<<std::endl;
        morir();
    }
    
};
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
    cuerpo.setPosition(
        posXanterior + diffX*porcentaje,
        posYanterior + diffY*porcentaje );
    //std::cout << "ENTRO EN RENDER enemigo , " << posXanterior <<  ", " << posYanterior  << std::endl;
    Motor * motor = Motor::instance();
    motor->dibujo(cuerpo);
    
};