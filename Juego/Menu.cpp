#include "Menu.h"
using namespace std;
using namespace sf;

Menu* Menu::p_instancia=NULL;
Menu* Menu::instancia(){
    if(p_instancia==NULL){
        p_instancia=new Menu();
    }
    return p_instancia;
}

Menu::Menu(){
    vector<sf::String> strings;
    strings.push_back("RANJAMP");
    strings.push_back("Pulsa ESPACIO");
    vector<Vector2f> posiciones;
    posiciones.push_back(Vector2f(225,3));
    posiciones.push_back(Vector2f(13,300));
    textos = new texto(2, strings, posiciones);
}

Menu::~Menu(){

}

void Menu::update(float deltaTime){
    Manejador* manejador = Manejador::instancia();
    Juego* juego = Juego::instance();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        manejador->cambiarEstado(juego);
    }
}

void Menu::render(float porcentaje){
    if(textos!=NULL)
        textos->render();
}