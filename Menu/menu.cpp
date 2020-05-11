#include "menu.h"
#include "../Juego/Juego.h"
/*menu* menu::p_instancia=NULL;

menu* menu::instancia(){
    if(p_instancia==NULL){
        p_instancia = new menu(Font(), 3);
    }
    return p_instancia;
}*/

menu::menu(Font fuente , int max){
    font = fuente;
    texto = new Text[max];
    numOpciones = max;
    selectedItem = 0;
    texto[0].setColor(Color::Red);
}

menu::~menu(){
    
    delete [] texto;
    if(t != nullptr){
        delete t; 
        t = nullptr;
    }
    if(b != nullptr){    
        delete b;
        b =nullptr;
    }
}

void menu::render(float num){ 
    Motor * motor = Motor::instance();
    if(b != nullptr){
        b->render();
    }
    for(int i = 0; i < numOpciones; i++){
        motor->dibujo(texto[i]);
    }
    
}

void menu::moveUp(){
    if(selectedItem - 1 >= 0 ){
        texto[selectedItem].setColor(Color::White);
        selectedItem--;
        texto[selectedItem].setColor(Color::Red);
    }else if(selectedItem - 1 < 0){
        texto[selectedItem].setColor(Color::White);
        selectedItem = numOpciones-1;
        texto[selectedItem].setColor(Color::Red);
    }

}

void menu::moveDown(){
    if(selectedItem + 1 < numOpciones ){
        texto[selectedItem].setColor(Color::White);
        selectedItem++;
        texto[selectedItem].setColor(Color::Red);
    } else if(selectedItem + 1 >= numOpciones){
        texto[selectedItem].setColor(Color::White);
        selectedItem = 0;
        texto[selectedItem].setColor(Color::Red);
    }
}

int menu::getItemPressed(){
    return selectedItem;
}

void menu::cambiarTexto(int i , String s, float posx , float posy){
  texto[i].setFont(font);
  texto[i].setString(s);
  texto[i].setPosition(posx , posy);
}

void menu::resetSelectedItem(){
    for(int i = 0; i < numOpciones; i++)
    texto[i].setColor(Color::White);
    selectedItem = 0;
    texto[selectedItem].setColor(Color::Red);
}


