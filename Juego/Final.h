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
    bool modRadio; //controla que las estrellas se acerquen o alejen del mago
    float angulos[numEstrellas]; //angulos de las estrellas, para moverlas
    float radio; //distancia entre estrellas y mago
    Cuerpo *estrellas[numEstrellas];
    Cuerpo *mago;
    sf::View* vista;
    Text *puntuacion; //incluye el "the end", por lo demas es igual que en Transicion
    Font *fuente;
    int vueltas; //cantidad de vueltas que han dado las estrellas
    float finishDelay; //tiempo que tarda en enviarte al menu principal
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
