#pragma once
#include <SFML/Graphics.hpp>
#include "../Animacion/Animacion.h"
#include "../Mundo/Mundo.h"
#include "../Enumerador/typeBody.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Rectangulo/Rectangulo.h"
#include "../Hud/hud.h"

class Player{
private:
    sf::Vector2u textura;
    Cuerpo* body;
    
    float velocidad;
    int saltos;
    int arma;
    bool PU_saltoDoble; bool PU_velocidad; bool PU_slowhits; // Powerups, se pueden hacer un array mas adelante
    float jumpSpeed;
    float jumpHeight; //Constante (en principio)
    Animacion animacion;
    int vidas;
    float cooldownSalto;
    float cooldownDisparo;
    float cooldownShift;

    bool godMode;
    int vidasAnteriores;
    Rectangulo * hitbox;
    bool facing;
    bool caida;
    float caidaTiempo;

    Rectangulo * coliAbajo;
    Rectangulo * coliArriba;
    Rectangulo * coliIzquierda;
    Rectangulo * coliDerecha;
    
    vector<int> llaves;
    int monedas;
public:
    //CANON
    Player(){};
    Player(int x, int y);
    //Player(sf::Texture* textura, sf::Vector2u cantidadImagenes, float SwitchTimeSprite);
    ~Player() ;
    //Para controlar el doble salto
    bool auxSaltos;
    //Rectangulo de colisiones encargado de dañar a los enemigos a corto alcance durante el golpe melee
    Rectangulo* melee;

    float atacando_melee; //positivo = atacando (es un timer)

    //FUNCIONALIDAD
    void render(float );
    void update(float deltaTime , Mundo * mundo);
    //Se llama en update. Recoloca los rectángulos de colisión.
    void updateHitbox();
    //Ser golpeado por un enemigo, un bloque de pinchos, un proyectil...
    void perderVida();
    //Iniciar o detener el modo dios (inmortalidad)
    void toggleGodMode();
    //Inicio del salto
    void saltar();
    //Se llama en update. Actualiza la posicion del rectangulo de colision del golpe melee
    bool GolpeMelee(float deltaTime);
    //El jugador vuelve a su posicion inicial como si hubiera comenzado de nuevo el nivel
    void reset();
    //Coger una moneda
    void sumarMonedas();
    //Coger la llave que abre la puerta "i"
    void cogerLlave(int i);

    //GET
    int getSaltos(){return saltos;}
    int getArma(){return arma;}
    float getAtacandoMelee(){return atacando_melee;}
    bool getPU_SaltoDoble(){return PU_saltoDoble;}; 
    bool getPU_Velocidad(){return PU_velocidad;}; 
    bool getPU_Slowhits(){return PU_slowhits;};
    bool getCayendo(){return caida;};
    float getJumpSpeed(){return jumpSpeed;};
    Cuerpo * getBody(){return body;}
    Rectangulo * getHitbox(){return hitbox;}
    int getVidas(){return vidas;}
    float getCooldownSalto(){return cooldownSalto;};
    float getCooldownDisparo(){return cooldownDisparo;}
    float getVelocidad(){return velocidad;}
    bool getFacing(){return facing;}
    bool getModoDios(){return godMode;}
    int getMonedas(){return monedas;}
    Rectangulo getMelee(){return *melee;}
    vector<int> getLlaves(){return llaves;}
    Rectangulo * getColiAbajo(){return coliAbajo;};
    Rectangulo * getColiArriba(){return coliArriba;};
    Rectangulo * getColiIzquierda(){return coliIzquierda;};
    Rectangulo * getColiDerecha(){return coliDerecha;};
    //SET
    void obtenerPU_SaltoDoble();
    void obtenerPU_Velocidad();
    void obtenerPU_Slowhits();

    void perderPU_SaltoDoble(){PU_saltoDoble=false;}
    void perderPU_Velocidad(){PU_velocidad=false;}
    void perderPU_Slowhits(){PU_slowhits=false;}

    void setJumpSpeed(float);
    
    void setSaltos(int);
    void avanzarCooldownDisparo(float deltaTime){cooldownDisparo-=deltaTime;};
    void setCooldownDisparo(float p_cooldown);

    void setVelocidad(float);
    void setArma(int);
    bool setVidas(int);
    void setPosicion(float, float );

    //Movimiento
    void moveRight(float deltaTime, Mundo * mundo);
    void moveLeft(float deltaTime, Mundo * mundo);

    //Reasignar el tamaño del sprite
    void setSize(float sizeX, float sizeY);

    //Movimiento vertical (gravedad)
    void caer();
    //Tocar el suelo y dejar de caer
    void suelo(float posX, float posY);

    
};