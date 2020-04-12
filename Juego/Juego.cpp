#include "Juego.h"


Juego* Juego::pinstance = 0;

Juego::Juego(){ //WIP FUNCION CARGARNIVEL
    mapa * mundo = mapa::instance(); 
    mundo->cargarmapa("Nivel1.tmx");
    mundo->crearSprites();
    mundo->cargarObjectGroups();
    mundo->crearObjetos();
    jugador = new Player();
    //if(jugador == nullptr) printf("asdasd");
    crearObjetos();
    crearEnemigos();
    view.setSize(1024,720); //FACHADA WIP
    
  for(int i = 0 ; i < maxBullets ; i++){
       bulletPlayer[i]=NULL;
  }

  for(int i = 0; i < maxBullets;i++){

      bulletEnemies[i] = NULL;

  }
  std::vector<sf::String> s; 
  s.push_back("SALTA");
  std::vector<Vector2f> pos;
  pos.push_back(Vector2f(10 , 1500));
  t = new texto(1 , s , pos);

}

Juego* Juego::instance(){

    if(pinstance == 0){

        pinstance = new Juego();

    }

    return(pinstance);
}

void Juego::update(float deltaTime){ //wip // UPDATE FUNCIONANDO 
  Motor * m = Motor::instance();
  mapa * mundo = mapa::instance(); 
  vector<int> dimensiones = mundo->cargarPosicionBordes();
  // for(int i = 0; i < dimensiones.size(); i ++){
  //   cout<< "dimensiones "<< i << " = "<< dimensiones[i] << endl;
  // }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ //WIP FACHADA y LECTURA TECLADO
      disparar(deltaTime);
  }
    //el for de abajo, mejor en una función aparte, por claridad y organizacion
    for(unsigned i = 0; i < maxBullets ;i++){
      if(bulletPlayer[i] != NULL){
        if(bulletPlayer[i]->lifetime<=0){
          delete bulletPlayer[i];
          bulletPlayer[i]=NULL;
        }
        else
          bulletPlayer[i]->update(deltaTime);//revisar
      }
      if(bulletEnemies[i] != NULL){
        if(bulletEnemies[i]->lifetime<=0){
          delete bulletEnemies[i];
          bulletEnemies[i] = NULL;
        }
        else
          bulletEnemies[i]->update(deltaTime);//revisar
      }
    }
    //puede que en alguna de estas funciones deltaTime NO sea necesario
    colisionPlayerMundo(deltaTime);
    colisionBulletMundo(deltaTime);
    colisionBulletEnemigo(deltaTime);
    colisionBulletJugador(deltaTime);
    
    jugador->update(deltaTime); //revisar
    int j = 0;
    while(objetos[j] != nullptr && j < numObjetos){ //WIP FACHADA y LECTURA TECLADO y FUNCION APARTE (probablemente rehacer entero)
     
     //std::cout << objetos[j] << std:: endl;
    // std::cout << numObjetos << "sadasdsa" << std:: endl;
     
      if( sf::Keyboard::isKeyPressed(sf::Keyboard::E) && objetos[j]->getBody().getGlobalBounds().intersects(jugador->getBody().getGlobalBounds())){

            switch (objetos[j]->getTipo()){ //este switch en una funcion aparte, pero está bien
                case 0:
                jugador->obtenerPU_Velocidad();
                     destruirObjetos(objetos[j]);
              
                break;
                case 1:
                    jugador->setArma(1);
                     destruirObjetos(objetos[j]);
                    break;

                case 2:
                   jugador->obtenerPU_SaltoDoble();
                     destruirObjetos(objetos[j]);
                    break;

                case 3:
                    jugador->obtenerPU_Velocidad();
                     destruirObjetos(objetos[j]);
                    break;
            
            default:
                std:: cout <<"Default" << std::endl;
                break;
            } 

        }
      j++;
    }

    
 
    Vector2f playerPos = jugador->getBody().getPosition();//WIP fachada

    view.setCenter(playerPos); //WIP fachada
    ///////////////Esta zona es WIP fachada y funcion diferente
    if( playerPos.x<view.getSize().x/2) {
      view.setCenter(view.getSize().x/2, playerPos.y);
    }
    if( playerPos.y > dimensiones[1]-view.getSize().y/2){
      view.setCenter(view.getCenter().x, dimensiones[1]-view.getSize().y/2);
    }
    if( playerPos.x>dimensiones[3]-view.getSize().x/2) {
      view.setCenter(dimensiones[3]-view.getSize().x/2, view.getCenter().y);
    }
    if( playerPos.y < view.getSize().y/2){
      view.setCenter(view.getCenter().x, view.getSize().y/2);
    }
    //////////////////

    m->getVentana()->setView(view); //wIP fachada

    for(int i = 0; i < numEmenigos; i++){
      if(enemies[i]==NULL) continue;
      enemies[i]->update(jugador , deltaTime);
      enemies[i]->updateHitbox(); //dentro de update de enemigo
      if(enemies[i]->getVidas() == 0){ //dentro de update de enemigo
        matarEnemigo(enemies[i]);
      }
   
      //esto del casteo está bien hecho, pero en una funcion aparte
      Centinela* casteado = dynamic_cast<Centinela*>(enemies[i]); 

      if(casteado != nullptr){

        if(casteado->getShoot()){

          for(int j = 0; j < maxBullets;j++){

            if(bulletEnemies[j] == NULL)
              bulletEnemies[j] = casteado->disparar();

          }

        }

      }      
    }
    jugador->updateHitbox(); //dentro de update de jugador
    

}

void Juego::colisionPlayerMundo(float deltaTime){//WIP FACHADA (a lo mejor esta funcion debería estar dentro de player.cpp)
    
    mapa * mundo = mapa::instance(); 
    RectangleShape ** objetos = mundo->getObjetos();//WIP FACHADA
    
    Vector2f posobj; //WIP FACHADA
    bool pararse=false;
    bool aux = false;
    Vector2f posant; //WIP FACHADA
    for(int i=0 ; i<  mundo->getNumObjetos(); i++){
      if(jugador->coliAbajo.intersects(objetos[i]->getGlobalBounds())){//WIP FACHADA
        posobj = objetos[i]->getPosition();
        pararse=true;
      } 
      
      if(pararse){
        jugador->setSaltos( jugador->getPU_SaltoDoble() ? 2 : 1);

        if(aux == false){
          jugador->setPosicion(jugador->getBody().getPosition().x,posobj.y-55); //WIP FACHADA y explicar que hace esto detalladamente pls
          jugador->updateHitbox(); //updateHitbox debería llamarse dentro de jugador setPosicion
          aux = true;
          posant = jugador->getBody().getPosition(); //WIP FACHADA
          
        } else if(posant != jugador->getBody().getPosition()){ //WIP FACHADA
          aux = false;
        }
        jugador->setJumpSpeed(0);

      }else{
        jugador->setJumpSpeed( jugador->getJumpSpeed() + 9.81f*5*deltaTime);
      }
      if(jugador->coliArriba.intersects(objetos[i]->getGlobalBounds())){ //WIP fachada
        jugador->setJumpSpeed(10);
      }
    }


}

void Juego::render(float porcentaje){ //WIP INTERPOLACION (¿y el render de player?)

    //Motor * m = Motor::instance();
    mapa * mundo = mapa::instance();
    mundo->render();
    for(unsigned i = 0; i < maxBullets;i++){
      if(bulletPlayer[i]==NULL) continue;
      bulletPlayer[i]->render(); //interpolacion

    }

    for(unsigned i = 0; i < maxBullets;i++){

      //if(bulletEnemies[i] == NULL)continue;
      if(bulletEnemies[i] != nullptr){bulletEnemies[i]->render();} //interpolacion
    }

    jugador->render();
    
    int i = 0;
    int j = 0;
    while(enemies[i] != nullptr && i < numEmenigos){
      //cout << " ENEMIGO " << i << endl;
      enemies[i]->render(porcentaje);//esto está interpolado
      i++;
    }

    t->render();
    while(objetos[j] != nullptr && j < numObjetos){
     
      objetos[j]->render();
      j++;
    }
    
}


void Juego::crearObjetos(){ //WIP FACHADA
  mapa * mundo = mapa::instance();
 
  sf::Vector2f pos; //WIP fachada
 
  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(3);
  numObjetos = posicion.size();
  objetos = new Objeto *[posicion.size()]; 


  for(unsigned i = 0; i < posicion.size();i++){

    pos.x =posicion[i][0];
    pos.y = posicion[i][1];
    
    Objeto *objeto1 = new Objeto(pos ,posicion[i][2]);
    objetos[i] =  objeto1;
  }
  
  

  // LLAMAR A OBJETO Y PASAR LOS PARAMETROS
}

void Juego::destruirObjetos(Objeto* enem){ //está nice
 for (int i = 0; i < numObjetos; i++){
    if(objetos[i] == enem){
      for(int j = i; j < numObjetos; j++){
        objetos[j] = objetos[j+1];        
      }
      objetos[numObjetos] = NULL;
      numObjetos--;
    }
  }

}

//CREARENEMIGOS FUNCIONE

void Juego::crearEnemigos(){ //está nice
  mapa * mundo = mapa::instance();

  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(1);
  numEmenigos = posicion.size();
  enemies = new Enemigo *[posicion.size()]; 
  for(unsigned i = 0; i < posicion.size();i++){
    float posx =  posicion[i][0];
    float posy =  posicion[i][1];
    if(posicion[i][2] == 1){
        //cout << "he añadido murcielago " << posx << ","  << posy  << endl; //eliminar
        Murcielago * murcielago = new Murcielago(posx, posy);
        enemies[i] = (Enemigo *) murcielago;
    }else if(posicion[i][2] == 2){
        //cout << "he añadido centinela" << endl; //eliminar
        Centinela * centinela = new Centinela(posx, posy,1);
        enemies[i] = (Enemigo *) centinela;
    }else if(posicion[i][2] == 3){
        //cout << "he añadido un centinela que se mueve"<< endl; //eliminar
        Centinela* centinela = new Centinela(posx,posy,0);
        enemies[i] = (Enemigo *) centinela;
    }
    else if(posicion[i][2] == 4){
        //cout << "he añadido reptante" << endl; //eliminar
        Pajaro * pajaro = new Pajaro(posx, posy); // WIP el reptante está sin terminar LOL
        enemies[i] = (Enemigo *) pajaro;
    }

  }
  
}

void Juego::matarEnemigo(Enemigo* enem){ //está nice
  for (int i = 0; i < numEmenigos; i++){
    if(enemies[i] == enem){
      for(int j = i; j < numEmenigos; j++){
        enemies[j] = enemies[j+1];        
      }
      enemies[numEmenigos] = NULL;
      numEmenigos--;
    }
  }
}

void Juego::matarJugador(){ //está nice
  mapa* mundo = mapa::instance();
  mundo->setCargado(false);
  mundo->liberar();
  mundo->cargarmapa("MapaFinal.tmx");
  mundo->crearSprites();
  mundo->cargarObjectGroups();
  mundo->crearObjetos();
  jugador = new Player();
  //if(jugador == nullptr) printf("asdasd");//quitar
  crearObjetos();
  crearEnemigos();
  view.setSize(1024,720);
    
  for(int i = 0 ; i < maxBullets ; i++){
       bulletPlayer[i]=NULL;
  }

  for(int i = 0; i < maxBullets;i++){

      bulletEnemies[i] = NULL;

  }

}


void Juego::disparar(float deltaTime){ //WIP FACHADA (¿a lo mejor debería estar dentro de jugador?)
   //a lo mejor parte del código aquí y parte del código en jugador (sin fundamento, a debatir)
        for(int i=0 ; i<maxBullets ; i++){
          if(bulletPlayer[i]==NULL && jugador->getCooldownDisparo()<=0 && jugador->getArma()==1){
            //y por estas cosas usamos fachada ^.^
            bulletPlayer[i]=new Bullet( jugador->getBody().getPosition().x , jugador->getBody().getPosition().y, (jugador->getBody().getScale().x > 0) , 1 );
            jugador->setCooldownDisparo(10*deltaTime);
            break;
          }
        }
    
}


void Juego::colisionBulletMundo(float deltaTime){//WIP fachada
    mapa * mundo = mapa::instance(); 
    RectangleShape ** objetos = mundo->getObjetos();

  for(unsigned int i=0 ; i<maxBullets ; i++){
    for(int j=0 ; j<mundo->getNumObjetos(); j++){
      if(bulletPlayer[i]==NULL) continue;
      if(objetos[j]==NULL) continue;

      if(objetos[j]->getGlobalBounds().intersects( bulletPlayer[i]->getBody().getGlobalBounds() )){
        delete bulletPlayer[i];
        bulletPlayer[i]=NULL;
      }
    }
  }
}

void Juego::colisionBulletJugador(float deltaTime){ //WIP fachada

  for(unsigned int i = 0; i < maxBullets; i++){

    if(bulletEnemies[i] != NULL){

      if(jugador->getBody().getGlobalBounds().intersects(bulletEnemies[i]->getBody().getGlobalBounds())){

        jugador->setVidas(jugador->getVidas()-1);

        std::cout << "Vidas del jugador: " << jugador->getVidas() << "\n";
        delete bulletEnemies[i];
        bulletEnemies[i] = NULL;

      }
    }
  }
}

void Juego::colisionBulletEnemigo(float deltaTime){//WIP fachada
  for(unsigned int i=0 ; i<maxBullets ; i++){
    for(int j=0 ; j<numEmenigos ; j++){
      if(bulletPlayer[i]==NULL) continue;
      if(enemies[j]==NULL)      continue;

      if(enemies[j]->getCuerpo().getGlobalBounds().intersects( bulletPlayer[i]->getBody().getGlobalBounds() )){
          for (int index = j; index < numEmenigos; index++)
            enemies[index] = enemies[index+1];
          enemies[numEmenigos] = NULL;
          numEmenigos--;

          delete bulletPlayer[i];
          bulletPlayer[i]=NULL;
      }
    }
  }
}
