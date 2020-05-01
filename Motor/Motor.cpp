#include "Motor.h"

Motor* Motor::pinstance=NULL;

Motor::Motor(){
    ventana = new sf::RenderWindow(sf::VideoMode(1080,720),"Totally not Pengo");
    updateClock.restart();
    
}


sf::View Motor::Camara(sf::Vector2f sad){


    sf::Vector2f center(sad.x/2, sad.y/2);


    sf::View view (center, sad);

    return view;
}

Motor* Motor::instance(){

    if(pinstance == 0){

        pinstance = new Motor();

    }

    return(pinstance);
}


void Motor::dibujo(sf::RectangleShape entrada){


        ventana->draw(entrada);



}

void Motor::dibujo( sf::Text  entrada){
    ventana->draw(entrada);
}

void Motor::dibujo(sf::CircleShape entrada){

  

        ventana->draw(entrada);

}

void Motor::dibujo(sf::Sprite entrada){



        ventana->draw(entrada);


}

bool cargarSprite(sf::Texture& entrada, std::string fichero){

    bool devolver = true;

    if(!entrada.loadFromFile("resources/" + fichero)){


        devolver = false;

    }

    return(devolver);

}

bool cargarSprite(sf::Texture& entrada, const char * fichero){

    bool devolver = true;

    if(!entrada.loadFromFile(fichero)){


        devolver = false;

    }

    return(devolver);

}

void Motor::setOrigin(sf::Sprite &entrada, int ancho , int largo){
    entrada.setOrigin( ancho/2 , largo/2);
}
void Motor::recorte(sf::Sprite &entrada,  int xi,int yi, int lengthX, int lengthY){

    entrada.setTextureRect(sf::IntRect(xi,yi,lengthX,lengthY));

}

void Motor::recorte(sf::RectangleShape &entrada,  int xi,int yi, int lengthX, int lengthY){

    entrada.setOrigin(xi + (lengthX/2),yi+(lengthY/2));

    entrada.setTextureRect(sf::IntRect(xi,yi,lengthX,lengthY));

}

void Motor::setTamanyoCuerpo(sf::RectangleShape &cuerpo,sf::Vector2f entrada){

    cuerpo.setSize(entrada);

}

void setTextura(sf::RectangleShape& cuerpo, sf::Texture* texture){

    cuerpo.setTexture(texture);

}


void setTextura(sf::Sprite& cuerpo, sf::Texture entrada){
    cuerpo.setTexture(entrada);
}


void posicionar(sf::RectangleShape& entrada, float x, float y){

    entrada.setPosition(x,y);

}

void posicionar(sf::Sprite& entrada, float x, float y){

    entrada.setPosition(x,y);

}


float Motor::getReloj(){

    float devolver = updateClock.getElapsedTime().asSeconds();

    return(devolver);
}

int Motor::getRelojM(){

    int devolver = updateClock.getElapsedTime().asMilliseconds();

    return(devolver);
}

float Motor::restartReloj(){

    float devolver = updateClock.restart().asSeconds();

    return(devolver);

}

int Motor::restartRelojM(){

    int devolver = updateClock.restart().asMilliseconds();

    return(devolver);

}

void Motor::limpieza(){

    ventana->clear();

}

void Motor::mostrar(){

    ventana->display();

}

bool Motor::getOpen(){

    return(ventana->isOpen());

}


