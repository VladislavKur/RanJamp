#include "pajaro.h"

Pajaro::Pajaro(float x, float y) : Enemigo(x,y){
    sf::Texture *text = new sf::Texture;

    sizeHeight = 75;
    sizeWidth = 75;

    cuerpo.setSize(sf::Vector2f(sizeWidth,sizeHeight));
    cuerpo.setPosition(x, y);

    alturaActual = y;
    alturaMinRelativa = alturaMax + alturaActual;
    alturaMaxRelativa = alturaActual - alturaMax;
    direccion = -1;
    haPegado = false;

    velocidad = 150;

    cuerpo.setOrigin(sizeWidth/2, sizeHeight/2);

    tamanyoHeightEsquina = sizeHeight/10;
    tamanyoWidthEsquina = sizeWidth/10;

    if(!text->loadFromFile("resources/sprites.png")) std::cout << "sadasds";
    
    cuerpo.setTexture(text);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));

    modo = 0;

    updateHitbox();
    
};

void Pajaro::updateHitbox(){

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

void Pajaro::update(Player* entrada, float delta){
///las colisiones
    
    posXanterior = posX;

    posX = posX - delta*velocidad*0.6;

    posYanterior = posY;

    posY = posY + direccion*delta*velocidad;

    if(posY >= alturaMinRelativa){ //la parte más baja que puede bajar
        posY = alturaMinRelativa;
        direccion = -1; //NEGATIVO en Y, porque queremos que SUBA
    }
    else if(posY <= alturaMaxRelativa){ //la parte más alta que puede subir 

        posY = alturaMaxRelativa;
        direccion = 1; //POSITIVO en Y, porque queremos que BAJE

    }

    if(entrada != NULL){
        if(coliDerecha.intersects(entrada->getBody().getGlobalBounds())
            || coliIzquierda.intersects(entrada->getBody().getGlobalBounds())
            || coliAbajo.intersects(entrada->coliArriba)
            || coliArriba.intersects(entrada->coliAbajo)){
            if(!haPegado)
                entrada->setVidas(entrada->getVidas()-1);
            haPegado = true;
            morir();
        }
    }
    updateHitbox();
};

void Pajaro::render( float porcentaje){
    cuerpo.setPosition(
        posXanterior + diffX*porcentaje,
        posYanterior + diffY*porcentaje );

    Motor * motor = Motor::instance();
    motor->dibujo(cuerpo);
}
