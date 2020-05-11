#pragma once
#include <SFML/Graphics.hpp>
#include "../Animacion/Animacion.h"
#include "../Mundo/Mundo.h"
#include "../Enumerador/typeBody.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Rectangulo/Rectangulo.h"
#include "../Hud/hud.h"

//Player es el personaje del jugador
class Player{
private:
    sf::Vector2u textura;
    Cuerpo* body;
    
    float velocidad; //velocidad de movimiento
    int saltos; //cantidad de saltos que aun se pueden realizar
    int arma; //arma equipada
    bool PU_saltoDoble; bool PU_velocidad; bool PU_slowhits; // Powerups, se pueden hacer un array mas adelante
    float jumpSpeed; //velocidad vertical
    float jumpHeight; //Constante (en principio)
    Animacion animacion;
    int vidas; //cantidad de vidas del jugador
    float cooldownSalto;  //tiempo entre saltos
    float cooldownDisparo; //tiempo entre disparos
    float cooldownShift;  //tiempo entre cambios de arma

    bool godMode; //modo inmortal
    int vidasAnteriores; //guardamos esto para cuando reseteemos el nivel, saber cuantas tenia al iniciarlo
    bool facing; //false: mirando hacia la izquierda, true derecha

    //administracion de la gravedad
    bool caida;
    float caidaTiempo;

    //Rectangulos de colision. Abajo: Pies, para detener caidas. Izda, dcha para evitar moverse dentro de una plataforma. Arriba para darse de cabeza contra una.
    Rectangulo * coliAbajo;
    Rectangulo * coliArriba;
    Rectangulo * coliIzquierda;
    Rectangulo * coliDerecha;
    
    vector<int> llaves;
    int monedas; //cantidad de monedas acumuladas
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

    //otorgar powerups al jugador
    void obtenerPU_SaltoDoble();
    void obtenerPU_Velocidad();
    void obtenerPU_Slowhits();

    //quitar powerups al jugador
    void perderPU_SaltoDoble(){PU_saltoDoble=false;}
    void perderPU_Velocidad(){PU_velocidad=false;}
    void perderPU_Slowhits(){PU_slowhits=false;}

    //cambiar la velocidad momentanea vertical. Util, por ejemplo, para detener al jugador.
    void setJumpSpeed(float);
    
    //para resetear los saltos del jugador cuando este toca el suelo
    void setSaltos(int);
    //avanzar temporizadores
    void avanzarCooldownDisparo(float deltaTime){cooldownDisparo-=deltaTime;};
    //colocar el temporizador en un punto maximo, cuando llegue a 0 terminara, por tanto esto indica el tiempo.
    void setCooldownDisparo(float p_cooldown);

    //SET
    //cambiar de velocidad. Util, por ejemplo, para el powerup de velocidad.
    void setVelocidad(float);
    //cambiar de arma
    void setArma(int);
    //hacer que el jugador tenga una cierta cantidad de vidas
    bool setVidas(int);
    //Teletransportar al jugador a un lugar determinado
    void setPosicion(float, float );

    //Movimiento del jugador
    void moveRight(float deltaTime, Mundo * mundo);
    void moveLeft(float deltaTime, Mundo * mundo);

    //Reasignar el tamaño del sprite
    void setSize(float sizeX, float sizeY);

    //Movimiento vertical (gravedad)
    void caer();
    //Tocar el suelo y dejar de caer
    void suelo(float posX, float posY);

    
};