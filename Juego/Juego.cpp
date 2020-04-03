#include "Juego.h"

Juego* Juego::pinstance = 0;

Juego::Juego(){

}

Juego* Juego::instance(){

    if(pinstance == 0){

        pinstance = new Juego();

    }

    return(pinstance);
}

void Juego::update(float deltaTime){ //wip


    for(int i = 0; i < (sizeof(bulletPlayer)/sizeof(*bulletPlayer));i++){

       bulletPlayer[i].update(deltaTime);

    }
    for(int i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

       bulletEnemies[i].update(deltaTime);

    }
    jugador.update(deltaTime);
    RectangleShape rec = jugador.getBody();
    for(int i = 0; i < (sizeof(enemies)/sizeof(*enemies));i++){

      enemies[i].update(rec, deltaTime);

    }

}

void Juego::colisionPlayerMundo(){// ESTO LO HACE VERMIAAA !!!!! -> interseccion player y rectangleshape 
    
    mapa * mundo = mapa::instance(); 
    RectangleShape ** objetos = mundo->getObjetos();
    int i = 0;
    while (objetos){
      if(jugador.coliAbajo.intersects(objetos[i]->getGlobalBounds())){
        

      jugador.setSaltos(PU_saltoDoble ? 2 : 1);
      jugador.setJumpSpeed(0);
  

      }
      i++;
    }

}

void Juego::render(float porcentaje){ //wip

    for(int i = 0; i < (sizeof(bulletPlayer)/sizeof(*bulletPlayer));i++){

      bulletPlayer[i].render();

    }
    for(int i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

     bulletEnemies[i].render();

    }

    jugador.render();
    
    for(int i = 0; i < (sizeof(enemies)/sizeof(*enemies));i++){

      enemies[i].render(porcentaje);

    }
    // render Mapa  

}


void Juego::crearObjetos(){ /// VlaDIS 
  mapa * mundo = mapa::instance();

  vector<Vector2f>  posicionPowerUp1 = mundo->cargarPosicionEnemigos_PowerUps(3);

  // LLAMAR A OBJETO Y PASAR LOS PARAMETROS
}