#include "Juego.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>  

Juego* Juego::pinstance = 0;

Juego::Juego(){

    mapa * mundo = mapa::instance(); 
    mundo->cargarmapa("MapaFinal.txt");
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

void Juego::colisionPlayerMundo(float deltaTime){// ESTO LO HACE VERMIAAA !!!!! -> interseccion player y rectangleshape 
    
    mapa * mundo = mapa::instance(); 
    RectangleShape ** objetos = mundo->getObjetos();
    int i = 0;
    while (objetos){
      if(jugador.coliAbajo.intersects(objetos[i]->getGlobalBounds())){
        
      jugador.setSaltos( jugador.getPU_SaltoDoble() ? 2 : 1);
      jugador.setJumpSpeed(0);
  

      } else{
        jugador.setJumpSpeed(9.81f*deltaTime);
      }

      if(jugador.coliArriba.intersects(objetos[i]->getGlobalBounds())){
        jugador.setJumpSpeed(10);
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
  int tipo = 1;
  
 
  vector<Vector2f>  posicionPowerUp1 = mundo->cargarPosicionEnemigos_PowerUps(3);


  std::string tipoPowerUP = "10";//mundo->cargarPosicionEnemigos_PowerUps(3);
    int aux = std::stoi(tipoPowerUP);



  for(int i = 0; i > posicionPowerUp1.size();i++){
    
    Objeto objeto1 ( posicionPowerUp1[i] ,aux);
  }
  
  

  // LLAMAR A OBJETO Y PASAR LOS PARAMETROS
  

}