#include "Estado.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Texto/texto.h"
using namespace sf;
#define numEstrellas 8

class Final : public Estado
{
private:
    Final();
    static Final* p_instancia;
    int graduaColor; //para el flash que pone la pantalla blanca
    bool dandoVueltas; //si estamos en el estado de dando vueltas o ya se ha terminado
    bool modRadio; 
    float angulos[numEstrellas];
    float radio;
    Cuerpo *estrellas[numEstrellas];
    Cuerpo *mago;
    sf::View* vista;
    Text *puntuacion;
    Text *the_end;
    Font *fuente;
    int vueltas;
    float finishDelay;
public:
    static Final* instancia();
    ~Final();

    //Para volver a hacerla desde el principio.
    void reset();
    void update(float deltaTime);
    void render(float num);
    //Similar a cambiarTexto de HUD. Coge el texto i, y cambia sus atributos.
    void cambiarTexto(int i , String s, float posx , float posy);
};
