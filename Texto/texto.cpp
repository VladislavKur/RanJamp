#include "texto.h"


texto::texto(int  i , std::vector<sf::String> t , std::vector<sf::Vector2f> posiciones){
    cantidad = i;
    text = new sf::Text[i];
    if(!font.loadFromFile("resources/fuentes/PixelBug.otf")){
        cout<< "no se ha encontrado arial.tff"<<endl;
    }
    for(int j = 0; j < i; j++){
        text[j].setFont(font);
        text[j].setColor(sf::Color::White);
        text[j].setString(t[j]);
       // cout<< "textoooo " << t[j] << endl;
        text[j].setScale(5,5);
        text[j].setPosition(posiciones[j]);
        cout<<"posi "<< posiciones[j].x << " " << posiciones[j].y << endl;
    }
}

void texto::render(){
    Motor * motor = Motor::instance();
    for(int j = 0; j < cantidad; j++){
        motor->dibujo(text[j]);
        if(text[j].getString().isEmpty()){
            cout<< "FUOJGINGORIDN"<<endl;
        }
    }
}