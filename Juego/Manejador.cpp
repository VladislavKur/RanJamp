#include "Manejador.h"

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
    if(estado!=NULL)
        estado=p_estado;
}

void Manejador::render(){
    estado->render();
}

void Manejador::update(){
    estado->update();
}