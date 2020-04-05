#include "Motor.h"

Motor* Motor::pinstance=NULL;

Motor::Motor(){
    ventana = new sf::RenderWindow(sf::VideoMode(1080,720),"Totally not Pengo");
    updateClock.restart();
}


Motor* Motor::instance(){

    if(pinstance == 0){

        pinstance = new Motor();

    }

    return(pinstance);
}

// bool Motor::instanced = false;

// bool Motor::crearVentana(){

//     bool devolver = false;

//     //if(!instanced){

//         devolver = true;

//         ventana->create(sf::VideoMode(1080,720),"Totally not Pengo");

//         updateClock.restart();

//         instanced = true;
//     //}

//     return(devolver);

// }



void Motor::dibujo(sf::RectangleShape entrada){


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

void posicionar(sf::RectangleShape& entrada, float x, float y){

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

bool Motor::getOpen(){

    return(ventana->isOpen());

}

void setTextura(sf::RectangleShape& cuerpo, sf::Texture entrada){

}



