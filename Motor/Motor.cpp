#include "Motor.h"

Motor* Motor::pinstance=NULL;

Motor::Motor(){
    ventana = new sf::RenderWindow(sf::VideoMode(1080,720),"Totally not Pengo");
    updateClock.restart();
    
  
}

Motor::~Motor(){
    delete ventana;
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


void Motor::dibujo(sf::Shape* cuerpo){

    sf::RectangleShape* casteadoRect = dynamic_cast<sf::RectangleShape*>(cuerpo);
    sf::CircleShape* casteadoCirc = dynamic_cast<sf::CircleShape*>(cuerpo);

    if(casteadoRect != NULL)
        ventana->draw(*casteadoRect);
    else if(casteadoCirc)
        ventana->draw(*casteadoCirc);
        
}
void Motor::dibujo(sf::RectangleShape & cuerpo){
    ventana->draw(cuerpo);
}
void Motor::dibujo( sf::Text  entrada){
    ventana->draw(entrada);
}

void Motor::dibujo(sf::Sprite entrada){
    if(entrada.getTexture() != nullptr){
        ventana->draw(entrada);
    }
}

bool Motor::cargarSprite(sf::Texture& entrada, std::string fichero){

    bool devolver = true;

    if(!entrada.loadFromFile("resources/Imagenes/" + fichero)){
        devolver = false;
    }

    return(devolver);
}

bool Motor::cargarSprite(sf::Texture& entrada, std::string fichero, bool x){

    bool devolver = x;

    if(!entrada.loadFromFile(fichero)){
        devolver = false;
    }

    return(devolver);
}


void Motor::posicionarOrigen(sf::Shape* cuerpo, float ancho, float altura){
    sf::RectangleShape* casteadoRect = dynamic_cast<sf::RectangleShape*>(cuerpo);
    sf::CircleShape* casteadoCirc = dynamic_cast<sf::CircleShape*>(cuerpo);

    if(casteadoRect != NULL)
        casteadoRect->setOrigin(ancho/2, altura/2);
    else if(casteadoCirc != NULL)
        casteadoCirc->setOrigin(ancho/2, altura/2);
}

 /*bool Motor::cargarSprite(sf::Texture& entrada, const char * fichero){

     bool devolver = true;

     if(!entrada.loadFromFile(fichero)){


         devolver = false;

    }

     return(devolver);

 }*/

void Motor::setOrigin(sf::Sprite &entrada, int ancho , int largo){
    entrada.setOrigin( ancho/2 , largo/2);
}
void Motor::setOrigin2(sf::Sprite &entrada, int ancho , int largo){
    entrada.setOrigin( ancho , largo);
}
void Motor::recorte(sf::Sprite &entrada,  int xi,int yi, int lengthX, int lengthY){

    entrada.setTextureRect(sf::IntRect(xi*lengthX,yi*lengthY,lengthX,lengthY));

}

void Motor::recorte(sf::RectangleShape &entrada,  int xi,int yi, int lengthX, int lengthY){
    entrada.setTextureRect(sf::IntRect(xi,yi,lengthX,lengthY));
}
void Motor::recorte(sf::Shape* cuerpo,  int xi,int yi, int lengthX, int lengthY){
    sf::RectangleShape* casteadoRect = dynamic_cast<sf::RectangleShape*>(cuerpo);
    sf::CircleShape* casteadoCirc = dynamic_cast<sf::CircleShape*>(cuerpo);

    if(casteadoRect != NULL)
        casteadoRect->setTextureRect(sf::IntRect(xi,yi,lengthX,lengthY));
    else if(casteadoCirc != NULL)
        casteadoCirc->setTextureRect(sf::IntRect(xi,yi,lengthX,lengthY));

}

void Motor::setTamanyoCuerpo(sf::Shape* cuerpo,sf::Vector2f entrada){

    sf::RectangleShape* casteadoRect = dynamic_cast<sf::RectangleShape*>(cuerpo);
    sf::CircleShape* casteadoCirc = dynamic_cast<sf::CircleShape*>(cuerpo);

    if(casteadoRect != NULL)
        casteadoRect->setSize(entrada);
    if(casteadoCirc != NULL)
        casteadoCirc->setRadius(entrada.x); // revisar si sale bala mal

}

void Motor::setScale(sf::Shape* cuerpo, float escalaX, float escalaY) {
    sf::RectangleShape* casteadoRect = dynamic_cast<sf::RectangleShape*>(cuerpo);
    sf::CircleShape* casteadoCirc = dynamic_cast<sf::CircleShape*>(cuerpo);

    if(casteadoRect != NULL)
        casteadoRect->setScale(sf::Vector2f(escalaX, escalaY));
    else if(casteadoCirc != NULL)
        casteadoCirc->setScale(sf::Vector2f(escalaX, escalaY));
}

void Motor::setTextura(sf::Shape* cuerpo, sf::Texture* texture){
    sf::RectangleShape* casteadoRect = dynamic_cast<sf::RectangleShape*>(cuerpo);
    sf::CircleShape* casteadoCirc = dynamic_cast<sf::CircleShape*>(cuerpo);

    if(casteadoRect != NULL)
        casteadoRect->setTexture(texture);
    else if(casteadoCirc != NULL)
        casteadoCirc->setTexture(texture);

}


void Motor::setTextura(sf::Sprite * cuerpo, sf::Texture * entrada){
    cuerpo->setTexture(*entrada);
}


void Motor::posicionar(sf::Shape* entrada, float x, float y){
    sf::RectangleShape* casteadoRect = dynamic_cast<sf::RectangleShape*>(entrada);
    sf::CircleShape* casteadoCirc = dynamic_cast<sf::CircleShape*>(entrada);

    if(casteadoRect != NULL)
        casteadoRect->setPosition(x,y);
    else if(casteadoCirc != NULL)
        casteadoCirc->setPosition(x,y);

}

void Motor::mover(sf::Shape* entrada, float x, float y){
    sf::RectangleShape* casteadoRect = dynamic_cast<sf::RectangleShape*>(entrada);
    sf::CircleShape* casteadoCirc = dynamic_cast<sf::CircleShape*>(entrada);

    if(casteadoRect != NULL)
        casteadoRect->move(x,y);
    else if(casteadoCirc != NULL)
        casteadoCirc->move(x,y);

}


void Motor::posicionar(sf::RectangleShape& entrada, float x, float y){
    entrada.setPosition(x,y);
}
bool Motor::compararColision(sf::Shape* cuerpo1, sf::Shape* cuerpo2){
    bool dev = false;

    if(cuerpo1->getGlobalBounds().intersects(cuerpo2->getGlobalBounds())){
        dev = true;
    }

    return dev;
}

void Motor::posicionar(sf::Sprite& entrada, float x, float y){

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


