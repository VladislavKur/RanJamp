#include "menu.h"
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!
menu::menu(Font fuente , int max){
    font = fuente;
    texto = new Text[max];
    numOpciones = max;
    selectedItem = 0;
}

menu::~menu(){

}

void menu::render(){ 
    Motor * motor = Motor::instance();
    for(int i = 0; i < numOpciones; i++){
        motor->dibujo(texto[i]);
    }
}

void menu::moveUp(){
    if(selectedItem - 1 >= 0 ){
        texto[selectedItem].setColor(Color::White);
        selectedItem--;
        texto[selectedItem].setColor(Color::Red);
    }
}

void menu::moveDown(){
    if(selectedItem + 1 < num_items ){
        texto[selectedItem].setColor(Color::White);
        selectedItem++;
        texto[selectedItem].setColor(Color::Red);
    }
}

int menu::getItemPressed(){
    return selectedItem;
}

void menu::cambiarTexto(int i ,Color c, String s, float posx , float posy){
  texto[i].setFont(font);
  texto[i].setColor(c);
  texto[i].setString(s);
  texto[i].setPosition(posx , posy);
}
