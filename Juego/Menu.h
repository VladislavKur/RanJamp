#include "Estado.h"
#include "Manejador.h"
#include "Juego.h"
#include "../Texto/texto.h"

#ifndef MENU_H
#define MENU_H

class Menu : public Estado{
private:
    Menu();
    static Menu* p_instancia; 
    texto* textos;
public:
    ~Menu();
    static Menu* instancia(); 
    void update(float deltaTime);
    void render(float porcentaje); 
};


#endif