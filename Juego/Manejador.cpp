#include "Manejador.h"
// ESTADOS :: -1 -> cerrar
//             0-> Juego
//             1->Menu_inicio
//             2->menu_controles
//             3->menu_vol;

Manejador* Manejador::p_instancia = NULL;

Manejador* Manejador::instancia(){
    if(p_instancia==NULL){
        p_instancia = new Manejador();
    }
    return p_instancia;
}

Manejador::Manejador(){
    estado=NULL;
}

void Manejador::cambiarEstado(Estado* p_estado){
    anterior= estado;
    estado=p_estado;
}

void Manejador::render(float num){
    estado->render(num);
}

void Manejador::update(float deltaTime){
    estado->update(deltaTime);
}
void Manejador::back(){
    estado = anterior;
}