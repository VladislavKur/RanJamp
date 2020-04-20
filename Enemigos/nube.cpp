#include "nube.h"

Nube::Nube(float x, float y) : Enemigo(x,y){
    sf::Texture *text = new sf::Texture;

    cuerpo.setSize(sf::Vector2f(100.0f,100.0f));
    cuerpo.setPosition(100, 100);

    cuerpo.setOrigin(75/2, 75/2);

    if(!text->loadFromFile("resources/sprites.png")) 
        std::cout << "sadasds";
    
    cuerpo.setTexture(text);
    cuerpo.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));

    distanciaAtaque = 1000;
    modo = 0;    
    velocidad = 50;
}

void Nube::update(sf::RectangleShape& body, float delta){
    //sf::RectangleShape body = player->getBody();

    float posJugador = body.getPosition().x;

    float local_diffX = posJugador - posX;
    float local_diffabs = abs(local_diffX);
    
    float velPlayer =  900.0/1000.0;

    diffX = 0; //inicialmente no se mueve
    diffY = 0; //inicialmente no se mueve

   switch(modo){

        case(0): //está quieto
            if(local_diffabs < distanciaAtaque){//si está lo suficientemente cerca, cambiamos
                modo = 1;
                cout<<"quieto"<<"\n";
            }
        break;
        case(1): //ataque -> le busco
            if(local_diffabs> distanciaAtaque){
                modo = 0;
            }else if(local_diffX == 0){                
                modo = 2;            
            }
            else{
                cout<<"ataque"<<"\n";
                actualizarPosicion((local_diffX/local_diffabs)*velocidad*delta,0); 
            }
            
        break;
        case(2): //le sigo y disparo
            cout<<"le sigo"<<"\n";
            actualizarPosicion((local_diffX/local_diffabs)*velPlayer*delta,0); 
            //posX = posJugador;

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
            
            //juego->dispararEnemigo(deltaTime,posX,posY,auxiliar);

        break;

    }
}

Bullet* Nube::disparar(){
    Bullet* devolver = NULL;

    if(shoot){

        shoot = false;

        devolver = new Bullet(posX,posY,direccion, 2);
    }

    return(devolver);

}

void Nube::render(sf::RenderWindow &v, float porcentaje){
    cuerpo.setPosition(
        posXanterior + diffX*porcentaje,
        posYanterior + diffY*porcentaje );

    /*Motor * motor = Motor::instance();
    motor->dibujo(cuerpo);*/
    v.draw(cuerpo);
}