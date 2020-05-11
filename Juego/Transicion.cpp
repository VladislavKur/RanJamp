#include "Transicion.h"
#include "Manejador.h"
#include "Juego.h"
#include <math.h>
using namespace sf;

Transicion::~Transicion(){

}

Transicion* Transicion::p_instancia = NULL;

Transicion* Transicion::instancia(){
    if(p_instancia==NULL){
        p_instancia = new Transicion();
    }
    return p_instancia;
}

Transicion::Transicion(){
    hud* Hud = hud::instance();
    Motor* motor = Motor::instance();
    fuente= new Font[1];
    puntuacion=new Text[2];
    fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
    
    cambiarTexto(0,"Puntuacion: ", 350,100);
    cambiarTexto(1, to_string(Hud->getPuntos()), 650,100);

    vista = new View(FloatRect( 0,0,1080, 720 ));

    mago = new Cuerpo(vista->getCenter().x, vista->getCenter().y,128,256, "mago.png", 1, RECTANGLE);
    mago->setSize(100,100);
    mago->Origen(100/2, 100/2);
    mago->addAnimacion(0.1);

    portal = new Cuerpo( vista->getCenter().x, vista->getCenter().y, 128, 128, "portal.png",1 , RECTANGLE );
    portal->setSize(200,200);
    portal->Origen(200/2, 200/2);
    portal->addAnimacion(0.1);
    

    angulo=0;
    radio=400;

}

void Transicion::update(float deltaTime){
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    hud* Hud = hud::instance();
    Motor* motor = Motor::instance();

    
    motor->getVentana()->setView(*vista);
    cambiarTexto(1, to_string(Hud->getPuntos()), 650,100);

    mago->posicionamiento(radio*cos(angulo) + portal->getPosicion()[0], radio*sin(angulo)+portal->getPosicion()[1]);
    mago->rotar(-145*deltaTime);
    angulo += 4*deltaTime;

    portal->rotar(50*deltaTime);
    if(radio<150){
        mago->setSize(mago->getSize()[0]-1, mago->getSize()[1]-1);
        mago->Origen(mago->getSize()[0]/2, mago->getSize()[1]/2);
    }

    if(radio>=0){
        radio-=100*deltaTime;
    }else{
        juego->pausarMusica(6);
        juego->reproducirMusica(0);
        juego->ponerBucleMusica(0);
        man->cambiarEstado(juego);
    }
    
}

void Transicion::render(float num){
    Motor * motor = Motor::instance();
    portal->render(num);
    mago->render(num);
    for(int i=0 ; i<2 ; i++){
        motor->dibujo(puntuacion[i]);
    }
}

void Transicion::reset(){
    Juego* juego = Juego::instance();
    juego->pausarMusica(0);
    juego->reproducirMusica(6);
    juego->ponerBucleMusica(6);
    radio=400;
    angulo=0;
    mago->setSize(100, 100);
}

void Transicion::cambiarTexto(int i , String s, float posx , float posy){
  puntuacion[i].setFont(*fuente);
  puntuacion[i].setString(s);
  puntuacion[i].setPosition(posx , posy);
}