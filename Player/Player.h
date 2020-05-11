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
    bool auxSaltos;
    Rectangulo* melee;
    float atacando_melee; //positivo = atacando

    //FUNCIONALIDAD
    void render(float );
    void update(float deltaTime , Mundo * mundo);
    void updateHitbox();
    void perderVida();
    void toggleGodMode();
    void saltar();
    bool GolpeMelee(float deltaTime);
    void reset();
    void sumarMonedas();
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

    void moveRight(float deltaTime, Mundo * mundo);
    void moveLeft(float deltaTime, Mundo * mundo);

    void setSize(float sizeX, float sizeY);

    void caer();
    void suelo(float posX, float posY);

    Rectangulo * getColiAbajo(){return coliAbajo;};
    Rectangulo * getColiArriba(){return coliArriba;};
    Rectangulo * getColiIzquierda(){return coliIzquierda;};
    Rectangulo * getColiDerecha(){return coliDerecha;};
};