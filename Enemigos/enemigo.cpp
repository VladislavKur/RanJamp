#include "enemigo.h"

Enemigo::Enemigo(float x, float y){
    
    posX = x;
    posY = y;
    diffX= 0.0;
    diffY= 0.0;
    posXanterior = x;
    posYanterior = y;
    modo = 0;
    vida = 1;

};
Enemigo::~Enemigo(){
  
}
void Enemigo::morir(){ //WIP eliminar probablemente
    //cuerpo.setScale(sf::Vector2f(cuerpo.getScale().x*0.9, cuerpo.getScale().y*0.9));
    //if(cuerpo.getScale().x < 0.1)
    cuerpo.setScale(0,0);
    //Juego* juego = Juego::instance();
    //juego->matarEnemigo(this);
    vida = 0;
     
}


void Enemigo::actualizarPosicion(float entradaX, float entradaY){

    posXanterior = posX; //LA DE ANTES DE LOS CALCULOS DEL UPDATE
    posYanterior = posY;
    posX += entradaX; //LA DE DESPUES DE LOS CALCULOS DEL UPDATE
    posY += entradaY;
    diffX = posX - posXanterior; //LA DIFERENCIA ENTRE POSX y la anterior
    diffY = posY - posYanterior;

    std::cout << "ant"<<posXanterior<<" "<<posYanterior<<"\n"
            <<"posx"<<posX<<" "<<posY<<"\n"
            <<"diff"<<diffX<<" "<<diffY<<"\n"
            <<"entrada"<<entradaX<<"  "<<entradaY<<"\n";
};
