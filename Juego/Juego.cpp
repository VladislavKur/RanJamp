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

void Juego::update(float deltaTime){ //wip // UPDATE FUNCIONANDO 


    for(int i = 0; i < (sizeof(bulletPlayer)/sizeof(*bulletPlayer));i++){

       bulletPlayer[i].update(deltaTime);

    }
    for(int i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

       bulletEnemies[i].update(deltaTime);

    }
    jugador->update(deltaTime); // JUGADOR SE PUEDA MOVER....

    RectangleShape rec = jugador->getBody();
    for(int i = 0; i < (sizeof(enemies)/sizeof(*enemies));i++){

      enemies[i].update(rec, deltaTime); // POBAR QUE FUNCIONA ...

    }

}

void Juego::colisionPlayerMundo(float deltaTime){// ESTO LO HACE VERMIAAA !!!!! -> interseccion player y rectangleshape 
    
    mapa * mundo = mapa::instance(); 
    RectangleShape ** objetos = mundo->getObjetos();
    int i = 0;
    while (objetos){
      if(jugador->coliAbajo.intersects(objetos[i]->getGlobalBounds())){
        
      jugador->setSaltos( jugador->getPU_SaltoDoble() ? 2 : 1);
      jugador->setJumpSpeed(0);
  

      } else{
        jugador->setJumpSpeed(9.81f*deltaTime);
      }

      if(jugador->coliArriba.intersects(objetos[i]->getGlobalBounds())){
        jugador->setJumpSpeed(10);
      }
      i++;
    }

}

void Juego::render(float porcentaje){ //wip

    Motor * m = Motor::instance();
    mapa * mundo = mapa::instance();
    mundo->render();

    for(int i = 0; i < (sizeof(bulletPlayer)/sizeof(*bulletPlayer));i++){

      bulletPlayer[i].render();

    }
    for(int i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

     bulletEnemies[i].render();

    }

    jugador->render();
    
    
    for(int i = 0; i < (sizeof(enemies)/sizeof(*enemies));i++){

      enemies[i].render(porcentaje);

    }
}


void Juego::crearObjetos(){ /// VlaDIS // LLAMARLO EN EL CONSTRUCTOR
  mapa * mundo = mapa::instance();
  int tipo = 1;
  sf::Vector2f pos;
 
  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(3);




  for(int i = 0; i > posicion.size();i++){

    pos.x =posicion[i][0];
    pos.y = posicion[i][1];
    
    Objeto objeto1(pos ,posicion[i][2]);
  }
  
  

  // LLAMAR A OBJETO Y PASAR LOS PARAMETROS
}

//CREARENEMIGOS FUNCIONE

// void Juego::crearEnemigos(){ 
//   mapa * mundo = mapa::instance();

//   vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(1);

//   for(int i = 0; i > posicion.size();i++){

//     switch (posicion[i][2]){
      
//       case 1:
//         Murcielago murcielago(posicion[i][0] , posicion[i][1]);
//         break;
      
//       case 2:
//         Murcielago murcielago(posicion[i][0] , posicion[i][1]);
//         break;
      
//       case 3:
//         Murcielago murcielago(posicion[i][0] , posicion[i][1]);
//         break;
      

//       default:
//         break;
//     }

//   }
  
// }