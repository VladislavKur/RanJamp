#include "texto.h"


texto::texto(int  i , std::vector<sf::String> t , std::vector<sf::Vector2f> posiciones){
    cantidad = i;
    text = new sf::Text[i];
    
    for(int j = 0; j < i; j++){

        text[j].setColor(sf::Color::White);
        text[j].setString(t[j]);
        text[j].setScale(5,5);
        text[j].setPosition(posiciones[j]);
    }
}

void texto::render(){
    Motor * motor = Motor::instance();
    for(int j = 0; j < cantidad; j++){
        motor->dibujo(text[j]);
    }
}

texto::~texto(){
    delete[]text;
}