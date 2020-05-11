#include <SFML/Graphics.hpp>
#include "Estado.h"

#ifndef MANEJADOR_H
#define MANEJADOR_H

//Patron State. Clase base para manejar e intercambiar los estados.
class Manejador{
private:
    static Manejador* p_instancia;
    Manejador();
    Estado* estado;

    //guardamos el estado anterior para cambiar a el mediante back()
    Estado* anterior;
   

public:
    static Manejador* instancia();
    ~Manejador();
    //Patron State
    void cambiarEstado(Estado* p_estado);
    //
    void update(float deltaTime);
    void render(float num);
    Estado * getAnterior();
    Estado * getEstado();
    //Volver al estado anterior
    void back();
    

    
};

#endif