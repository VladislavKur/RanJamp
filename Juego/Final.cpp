#include "Final.h"
#include "Manejador.h"
#include "Juego.h"
#include <math.h>
using namespace sf;

Final::~Final(){

}

Final* Final::p_instancia = NULL;

Final* Final::instancia(){
    if(p_instancia==NULL){
        p_instancia = new Final();
    }
    return p_instancia;
}

Final::Final(){
    hud* Hud = hud::instance();
    Motor* motor = Motor::instance();
    fuente= new Font[1];
    puntuacion=new Text[3];
    the_end = new Text[1];
    fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
    graduaColor=0;
    modRadio=true;
    cambiarTexto(0,"Puntuacion final: ", 350,100);
    cambiarTexto(1, to_string(Hud->getPuntos()), 650,100);
    cambiarTexto(2, "THE END", 475,600);
    vueltas=0;

    dandoVueltas=true;
    vista = new View(FloatRect( 0,0,1080, 720 ));

    mago = new Cuerpo(vista->getCenter().x, vista->getCenter().y,128,256, "mago.png", 1, RECTANGLE);
    mago->setSize(100,100);
    mago->Origen(100/2, 100/2);
    mago->addAnimacion(0.1);

    estrellas[0] = new Cuerpo(mago->getPosicion()[0], mago->getPosicion()[1], 100, 100, "estrella.png", 1, RECTANGLE);
    estrellas[1] = new Cuerpo(mago->getPosicion()[0], mago->getPosicion()[1], 100, 100, "estrella.png", 1, RECTANGLE);
    estrellas[2] = new Cuerpo(mago->getPosicion()[0], mago->getPosicion()[1], 100, 100, "estrella.png", 1, RECTANGLE);
    estrellas[3] = new Cuerpo(mago->getPosicion()[0], mago->getPosicion()[1], 100, 100, "estrella.png", 1, RECTANGLE);
    estrellas[4] = new Cuerpo(mago->getPosicion()[0], mago->getPosicion()[1], 100, 100, "estrella.png", 1, RECTANGLE);
    estrellas[5] = new Cuerpo(mago->getPosicion()[0], mago->getPosicion()[1], 100, 100, "estrella.png", 1, RECTANGLE);
    estrellas[6] = new Cuerpo(mago->getPosicion()[0], mago->getPosicion()[1], 100, 100, "estrella.png", 1, RECTANGLE);
    estrellas[7] = new Cuerpo(mago->getPosicion()[0], mago->getPosicion()[1], 100, 100, "estrella.png", 1, RECTANGLE);

    for(int i=0 ; i<numEstrellas ; i++){
        estrellas[i]->addAnimacion(0.1);
        estrellas[i]->setSize(50,50);
        estrellas[i]->Origen(50/2, 50/2);
    }
    float pi=3.1415926;

    angulos[0]=0;
    angulos[1]=pi/4;
    angulos[2]=pi/2;
    angulos[3]=3*pi/4;
    angulos[4]=pi;
    angulos[5]=5*pi/4;
    angulos[6]=3*pi/2;
    angulos[7]=7*pi/4;
    radio=400;

}

void Final::update(float deltaTime){
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    hud* Hud = hud::instance();
    Motor* motor = Motor::instance();

    motor->getVentana()->setView(*vista);
    cambiarTexto(1, to_string(Hud->getPuntos()), 650,100);
    
    if(dandoVueltas){
        for(int i=0 ; i<numEstrellas ; i++){if(estrellas[i] == NULL ) continue;
            estrellas[i]->rotar(-200*deltaTime);
            estrellas[i]->posicionamiento(radio*cos(angulos[i]) + mago->getPosicion()[0], radio*sin(angulos[i])+mago->getPosicion()[1]);
            angulos[i]+=6*deltaTime;
        }

        if(radio>=300) modRadio=false;
        if(radio<=0){
            modRadio=true;
            vueltas++;
            cout<<vueltas<<endl;
        } 

        if(modRadio){
            radio+=200*deltaTime;
        }else{
            radio-=200*deltaTime;
        }
        
        if(vueltas==3){
            dandoVueltas=false;
            for(int i=0; i<numEstrellas ; i++){
                delete estrellas[i];
                estrellas[i]=NULL;
            }
            graduaColor=255;
            delete mago;
            mago= new Cuerpo(vista->getCenter().x, vista->getCenter().y,128,256, "MAGOS BLANCO.png", 1, RECTANGLE);
            mago->setSize(100,100);
            mago->Origen(100/2, 100/2);
            mago->addAnimacion(0.1);
        }
    } else{
        if(graduaColor>0){
            graduaColor--;
        }
        

    }
    
    
}

void Final::render(float num){
    Motor * motor = Motor::instance();
    motor->getVentana()->clear(Color(graduaColor,graduaColor,graduaColor));
    mago->render(num);
    if(!dandoVueltas){
        for(int i=0 ; i<3 ; i++){
            motor->dibujo(puntuacion[i]);
        }
    }


    for(int i=0 ; i<numEstrellas ; i++){ if(estrellas[i]==NULL ) continue;
        estrellas[i]->render(num);
    }

}

void Final::reset(){
    radio=400;
    angulos[0]=0;
}

void Final::cambiarTexto(int i , String s, float posx , float posy){
  puntuacion[i].setFont(*fuente);
  puntuacion[i].setString(s);
  puntuacion[i].setPosition(posx , posy);
}