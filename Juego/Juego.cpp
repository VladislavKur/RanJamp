#include "Juego.h"


Juego* Juego::pinstance = 0;

Juego::Juego(){
    mapa * mundo = mapa::instance(); 
    mundo->cargarmapa("MapaFinal.tmx");
    mundo->crearSprites();
    mundo->cargarObjectGroups();
    mundo->crearObjetos();
    jugador = new Player();
    if(jugador == nullptr) printf("asdasd");
}

Juego* Juego::instance(){

    if(pinstance == 0){

        pinstance = new Juego();

    }

    return(pinstance);
}

void Juego::update(float deltaTime){ //wip


    for(unsigned i = 0; i < (sizeof(bulletPlayer)/sizeof(*bulletPlayer));i++){

       bulletPlayer[i].update(deltaTime);

    }
    for(unsigned i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

       bulletEnemies[i].update(deltaTime);

    }
    colisionPlayerMundo(deltaTime);
    
    jugador->update(deltaTime);
    RectangleShape rec = jugador->getBody();
    for(unsigned i = 0; i < (sizeof(enemies)/sizeof(*enemies));i++){

      enemies[i].update(rec, deltaTime);

    }

}

void Juego::colisionPlayerMundo(float deltaTime){// ESTO LO HACE VERMIAAA !!!!! -> interseccion player y rectangleshape 
    
    mapa * mundo = mapa::instance(); 
    RectangleShape ** objetos = mundo->getObjetos();
    bool pararse=false;
    for(unsigned int i=0 ; i<sizeof(objetos) ; i++){
      if(jugador->coliAbajo.intersects(objetos[i]->getGlobalBounds())){
        pararse=true;

      } 

      if(pararse){
        jugador->setSaltos( jugador->getPU_SaltoDoble() ? 2 : 1);
        jugador->setJumpSpeed(0);

      }else{
        jugador->setJumpSpeed( jugador->getJumpSpeed() + 9.81f*deltaTime);
      }
      if(jugador->coliArriba.intersects(objetos[i]->getGlobalBounds())){
        jugador->setJumpSpeed(10);
      }
    }

}

void Juego::render(float porcentaje){ //wip

    Motor * m = Motor::instance();
    mapa * mundo = mapa::instance();
    mundo->render();
    for(unsigned i = 0; i < (sizeof(bulletPlayer)/sizeof(*bulletPlayer));i++){

      bulletPlayer[i].render();

    }
    for(unsigned i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

     bulletEnemies[i].render();

    }

    jugador->render();
    
    
    for(unsigned i = 0; i < (sizeof(enemies)/sizeof(*enemies));i++){

      enemies[i].render(porcentaje);

    }
}


void Juego::crearObjetos(){ /// VlaDIS 
  mapa * mundo = mapa::instance();
  int tipo = 1;
  sf::Vector2f pos;
 
  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(3);




  for(unsigned i = 0; i > posicion.size();i++){

    pos.x =posicion[i][0];
    pos.y = posicion[i][1];
    
    Objeto objeto1 ( pos ,posicion[i][2]);
  }
  
  

  // LLAMAR A OBJETO Y PASAR LOS PARAMETROS
  

}