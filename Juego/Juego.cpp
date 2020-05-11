#include "Juego.h"
#include "Manejador.h"
#include "Transicion.h"
#include "Final.h"
#include "../Menu/menu_inicial.h"

#include "../Menu/menu_pausa.h"

Juego* Juego::pinstance = 0;

Juego::Juego(){
    nivel = 0;
    inicializarNiveles();
    cargarMusica();
    mundo = new Mundo();  
    mundo->cargarmapa(niveles[nivel].c_str());
    mundo->crearSprites();
    mundo->cargarObjectGroups();
    mundo->crearObjetos();
    mundo->cargarPosicionPlayer_Puerta(4);
    mundo->crearObstaculos();// Obstaculos
    mundo->crearMonedasLlaves();// Monedas y llaves
    vector<float> posP = mundo->cargarPosicionPlayer_Puerta(2);
    jugador = new Player(posP[0], posP[1]);
    crearObjetos();
    crearEnemigos();
    view.setSize(1080,720); 
    //view.setCenter(1080/2,720/2);
    view.setCenter(view.getSize().x/2,view.getSize().y/2);

  for(int i = 0 ; i < maxBullets ; i++){
       bulletPlayer[i]=NULL;
  }

  for(int i = 0; i < maxBullets;i++){
      bulletEnemies[i] = NULL;
  }

  for(int i = 0; i < maxBullets;i++){
      bulletNube[i] = NULL;
  }

  for(int i = 0; i < maxBullets;i++){
      bulletBoss[i] = NULL;
  }

  std::vector<sf::String> s; 
  s.push_back("SALTA");
  std::vector<Vector2f> pos;
  pos.push_back(Vector2f(10 , 1500));

  portal = new Cuerpo(mundo->getPuerta()->getPosicion()[0]+128/3, mundo->getPuerta()->getPosicion()[1]+128/3, 128, 128, "portal.png",1 , RECTANGLE );
  portal->setSize(4*32,4*32);
  portal->Origen(portal->getSize()[0]/2,portal->getSize()[1]/2);
  portal->addAnimacion(0.1);
}
Juego::~Juego(){
      if(jugador != nullptr){
        delete jugador;
        jugador = nullptr;
      }
      delete [] enemies;

      delete [] objetos;
      
      for(int i= 0; i < maxBullets; i++){
        if(bulletPlayer[i] != nullptr){
          delete bulletPlayer[i];
          bulletPlayer[i] = nullptr;
        }
        if(bulletEnemies[i] != nullptr){
          delete bulletEnemies[i];
          bulletEnemies[i] = nullptr;
        }
        if(bulletNube[i] != nullptr){
          delete bulletNube[i];
          bulletNube[i] = nullptr;
        }
        if(bulletBoss[i] != nullptr){
          delete bulletBoss[i];
          bulletBoss[i] = nullptr;
        }
      }
      if(so != nullptr){
        delete so;
        so = nullptr;
      }
      if(mundo != nullptr){
        delete mundo;
        mundo = nullptr;
      }
  
      delete[] niveles; 

}

Juego* Juego::instance(){

    if(pinstance == 0){

        pinstance = new Juego();

    }

    return(pinstance);
}

void Juego::update(float deltaTime){ 
  Motor * m = Motor::instance();
  hud * Hud = hud::instance();
  if(Hud->getVidas() == 0){
    matarJugador();
  }
  pausa();
  vector<int> dimensiones = mundo->cargarPosicionBordes();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ 
      disparar(deltaTime);
      so[3]->reproducirMusica();
  }
  
    for(unsigned i = 0; i < maxBullets ;i++){
      if(bulletPlayer[i] != NULL){
        

        if(bulletPlayer[i]->lifetime<=0){
          delete bulletPlayer[i];
          bulletPlayer[i]=NULL;
        }
        else
          bulletPlayer[i]->update(deltaTime);
      }
      if(bulletEnemies[i] != NULL){
        if(jugador->getPU_Slowhits()){
          bulletEnemies[i]->setVelocidad(300);
        } else bulletEnemies[i]->setVelocidad(600);
        if(bulletEnemies[i]->lifetime<=0){
          delete bulletEnemies[i];
          bulletEnemies[i] = NULL;
        }
        else
          bulletEnemies[i]->update(deltaTime);
      }
      if(bulletNube[i] != NULL){
        if(jugador->getPU_Slowhits()){
          bulletNube[i]->setVelocidad(300);
        } else bulletNube[i]->setVelocidad(600);
        if(bulletNube[i]->lifetime<=0){
          delete bulletNube[i];
          bulletNube[i] = NULL;
        }
        else
          bulletNube[i]->update(deltaTime);
      }
      if(bulletBoss[i] != NULL){
        if(bulletBoss[i]->lifetime<=0){
          delete bulletBoss[i];
          bulletBoss[i] = NULL;
        }
        else
          bulletBoss[i]->update(deltaTime);
      }
    }
    colisionPlayerMundo(deltaTime);
    colisionPlayerObstaculos(deltaTime);
    colisionBulletMundo();
    colisionBulletEnemigo();
    colisionBulletJugador();
    colisionMeleeEnemigo();
    portal->posicionamiento(mundo->getPuerta()->getPosicion()[0]+128/3, mundo->getPuerta()->getPosicion()[1]+128/3);
    portal->rotar(50*deltaTime);
    
    jugador->update(deltaTime , mundo);
    if(Keyboard::isKeyPressed(Keyboard::Num1)){
      if(Hud->getArma()[0] > 0){
        jugador->setArma(1);
      }
    }
    if(Keyboard::isKeyPressed(Keyboard::Num2)){
      if(Hud->getArma()[1] > 0){
        jugador->setArma(2);
      }
    }
    
    int j = 0;
    while(objetos[j] != nullptr && j < numObjetos){ 
     
      if( sf::Keyboard::isKeyPressed(sf::Keyboard::E) && 
      objetos[j]->getBody()->getGlobalBounds()->getIntersect(*jugador->getBody()->getGlobalBounds())){

            switch (objetos[j]->getTipo()){
                case 0:
                    Hud->setVelocidad(true);
                    Hud->setIVelocidad(350);
                    destruirObjetos(objetos[j]);
                    break;
                case 1:
                     jugador->setArma(1);
                     if(Hud->getArma()[0] == 0){
                      Hud->setArma(0,1);
                     }
                     destruirObjetos(objetos[j]);
                    break;

                case 2:
                    Hud->setDobleSalto(true);
                    destruirObjetos(objetos[j]);
                    break;

                case 3:
                    Hud->setSlow(true);
                    destruirObjetos(objetos[j]);
                    break;
                case 4: 
                    Hud->setSlow(true);
                    destruirObjetos(objetos[j]);
                    break;
            default:
                std:: cout <<"Default" << std::endl;
                break;
            } 

        }
      j++;
    }

    j = mundo->getNumMonedasLlaves() - 1 ;
    while(mundo->getMonedasLlaves()[j] != nullptr && j >= 0){ 
    
      if(mundo->getMonedasLlaves()[j]->getGlobalBounds()->getIntersect(*jugador->getBody()->getGlobalBounds())){

            switch (mundo->getMonedasLlaves()[j]->getTipo()){ 
                case 0:
                    Hud->sumarMonedas();
                    mundo->EliminarMonedasLLaves(mundo->getMonedasLlaves()[j]);
                    break;
                case 1:
                    jugador->cogerLlave(1);
                    mundo->EliminarMonedasLLaves(mundo->getMonedasLlaves()[j]);
                    mundo->EliminarMonedasLLaves(mundo->getMonedasLlaves()[j]);
                    break;
                default:
                    cout <<"Default" << endl;
                break;
            } 

        }
      j--;
    }
    
 
    float playerPosX = jugador->getBody()->getPosicion()[0];
    float playerPosY = jugador->getBody()->getPosicion()[1];

    view.setCenter(playerPosX,playerPosY); 
    if( playerPosX < view.getSize().x/2) {
      view.setCenter(view.getSize().x/2, playerPosY);
    }
    if( playerPosY > dimensiones[1]-view.getSize().y/2){
      view.setCenter(view.getCenter().x, dimensiones[1]-view.getSize().y/2);
    }
    if( playerPosX>dimensiones[3]-view.getSize().x/2) {
      view.setCenter(dimensiones[3]-view.getSize().x/2, view.getCenter().y);
    }
    if( playerPosY < view.getSize().y/2){
      view.setCenter(view.getCenter().x, view.getSize().y/2);
    }


    m->getVentana()->setView(view); 
    Hud->setMarcador( view.getCenter().x , view.getCenter().y);
    for(int i = 0; i < numEmenigos; i++){
      if(enemies[i]==NULL) continue;
      enemies[i]->update(jugador , deltaTime);
      enemies[i]->updateHitbox(); 
      if(enemies[i]->muerto){ 
        matarEnemigo(enemies[i]);
      }
   
      if(enemies[i] != nullptr){
        Centinela* casteadoCent = dynamic_cast<Centinela*>(enemies[i]);
        Nube* casteadoNube = dynamic_cast<Nube*>(enemies[i]);
        Boss* casteadoBoss = dynamic_cast<Boss*>(enemies[i]); 
      
        if(casteadoCent != nullptr){

          if(casteadoCent->getShoot()){

            for(int j = 0; j < maxBullets;j++){

              if(bulletEnemies[j] == NULL)
                bulletEnemies[j] = casteadoCent->disparar();

            }

          }

        }  

        if(casteadoNube != nullptr){

          if(casteadoNube->getShoot()){

            for(int j = 0; j < maxBullets;j++){

              if(bulletNube[j] == NULL)
                bulletNube[j] = casteadoNube->disparar();

            }

          }

        }

        if(casteadoBoss != nullptr){
          if(!casteadoBoss->getPegado()){
            if(jugador->getVidas() <= 0)
              matarJugador();
          }
          
          if(casteadoBoss->getShoot()){
            for(int j = 0; j < maxBullets;j++){
              if(bulletBoss[j] == NULL)
                bulletBoss[j] = casteadoBoss->disparar();
            }
          }
        }
        
      }      
    }
    jugador->updateHitbox(); 
    
    comprobarPasarNivel();

}

void Juego::colisionPlayerMundo(float deltaTime){

    hud * Hud = hud::instance();
    Cuerpo ** objetos = mundo->getObjetos();
  
    float posobjY;
    bool pararse=false;
    bool aux = false;

      for(int i=0 ; i<  mundo->getNumObjetos(); i++){
        if(jugador->getColiAbajo()->getIntersect(*objetos[i]->getGlobalBounds())){
          posobjY = objetos[i]->getPosicion()[1];
          jugador->suelo(
            jugador->getBody()->getPosicion()[0],
            posobjY - jugador->getBody()->getOriginY() - jugador->getColiAbajo()->getHeight() + 5
          );
          pararse=true;
          i = mundo->getNumObjetos(); 
          jugador->setSaltos( Hud->getDoblesalto() ? 2 : 1);
        } 
        
        if(!pararse){

          jugador->caer();
          if(jugador->getColiArriba()->getIntersect(*objetos[i]->getGlobalBounds())){ 
            jugador->setJumpSpeed(0);
          }
        }

      
    }
}


void Juego::colisionPlayerObstaculos(float deltaTime){
    Cuerpo ** obstaculos = mundo->getObstaculos();
    hud * Hud = hud::instance();

    bool morir = false;
    bool salir = false;
    timerObstaculos -= deltaTime;
    for(int i=0 ; i<  mundo->getNumObstaculos() && !salir; i++){
      if(obstaculos[i]!= nullptr){
        if(jugador->getColiAbajo()->getIntersect(*obstaculos[i]->getGlobalBounds())){
          if(obstaculos[i]->getTipo() == 1 && timerObstaculos <= 0){
            if(jugador->getModoDios() == false){
              morir = Hud->restarVidas();
              if(morir == true){
                matarJugador();
                salir = true;
              }
            }
            jugador->setSaltos( Hud->getDoblesalto() ? 2 : 1);
            jugador->saltar(); 
        
            timerObstaculos = 1;
          }else if(obstaculos[i]->getTipo() == 2){
            if(jugador->getModoDios() == false){
              matarJugador();
              salir = true;
            }
          }
        } 
      }
    }
}

void Juego::colisionMeleeEnemigo(){
    Rectangulo melee = jugador->getMelee();
    hud * Hud = hud::instance();
    if(jugador->getAtacandoMelee() > 0){
      for(int i=0 ; i<numEmenigos; i++){
        if(enemies[i]==NULL) continue;
        if(enemies[i]->getCuerpo()==NULL) continue;
        if( enemies[i]->getCuerpo()->getGlobalBounds()->getIntersect(melee) ){
          enemies[i]->restarVida(1);
          
          if(enemies[i]->muerto == true){
            matarEnemigo(enemies[i]);
            Hud->sumarPuntos(50);
          }
        }
      }
    }
    
}

void Juego::render(float porcentaje){ 
    Motor* motor  = Motor::instance();


    hud * Hud = hud::instance();
    mundo->render();
    for(unsigned i = 0; i < maxBullets;i++){
      if(bulletPlayer[i]==NULL) continue;
      bulletPlayer[i]->render(porcentaje); 

    }

    
    
    

    jugador->render(porcentaje);
    
    int i = 0;
    int j = 0;
    while(enemies[i] != nullptr && i < numEmenigos){
      enemies[i]->render(porcentaje);
      i++;
    }

    while(objetos[j] != nullptr && j < numObjetos){
     
      objetos[j]->render(porcentaje);
      j++;
    }
    
    j=0;
    while(mundo->getMonedasLlaves()[j] != nullptr && j < mundo->getNumMonedasLlaves()){
      mundo->getMonedasLlaves()[j]->render(porcentaje);
      j++;
    }
    for(unsigned i = 0; i < maxBullets;i++){
      if(bulletEnemies[i] != nullptr){bulletEnemies[i]->render(porcentaje);}
    }

    for(unsigned i = 0; i < maxBullets;i++){      
      if(bulletNube[i] != nullptr){bulletNube[i]->render(porcentaje);}
    } 

    for(unsigned i = 0; i < maxBullets;i++){ 
      if(bulletBoss[i] != nullptr){bulletBoss[i]->render(porcentaje);}
    }
    mundo->render2();
    Hud->render();
   

    portal->render();
    
}


void Juego::crearObjetos(){ 
 
  
 
  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(3);
  
  numObjetos = posicion.size();
  objetos = new Objeto *[posicion.size()]; 

  for(unsigned i = 0; i < posicion.size();i++){
    Objeto *objeto1 = new Objeto(posicion[i][0],posicion[i][1] ,posicion[i][2] );
    objetos[i] =  objeto1;
  }
}

void Juego::destruirObjetos(Objeto* enem){ 
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


void Juego::crearEnemigos(){ 

  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(1);
  numEmenigos = posicion.size();
  enemies = new Enemigo *[posicion.size()]; 
  for(unsigned i = 0; i < posicion.size();i++){
    float posx =  posicion[i][0];
    float posy =  posicion[i][1];
    if(posicion[i][2] == 1){
        Murcielago * murcielago = new Murcielago(posx, posy);
        enemies[i] = (Enemigo *) murcielago;
    }else if(posicion[i][2] == 2){
        Centinela * centinela = new Centinela(posx, posy,1);
        enemies[i] = (Enemigo *) centinela;
    }else if(posicion[i][2] == 3){
        Centinela* centinela = new Centinela(posx,posy,0);
        enemies[i] = (Enemigo *) centinela;
    }
    else if(posicion[i][2] == 4){
        Pajaro * pajaro = new Pajaro(posx, posy);
        enemies[i] = (Enemigo *) pajaro;
    }
    else if(posicion[i][2] == 5){
        Nube * nube = new Nube(posx, posy); 
        enemies[i] = (Enemigo *) nube;
    }
    else if(posicion[i][2] == 6){
        Boss * boss = new Boss(posx, posy); 
        enemies[i] = (Enemigo *) boss;
    }

  }
  
}

void Juego::matarEnemigo(Enemigo* enem){ 
  hud * Hud = hud::instance();
  for (int i = 0; i < numEmenigos; i++){
    if(enemies[i] == enem){
      for(int j = i; j < numEmenigos; j++){
        if(j+1 < numEmenigos){
          enemies[j] = enemies[j+1]; 
        }       
      }
      enemies[numEmenigos] = NULL;
      numEmenigos--;
    }
  }
}

void Juego::matarJugador(){ //está nice
  hud * Hud = hud::instance();
  nivelactual = niveles[nivel].c_str();
  nivel = 0;
  delete mundo;
  mundo = new Mundo();
  mundo->cargarmapa(niveles[nivel].c_str());
  mundo->crearSprites();
  mundo->cargarObjectGroups();
  mundo->crearObjetos();
  mundo->cargarPosicionPlayer_Puerta(4);
  mundo->crearObstaculos();
  mundo->crearMonedasLlaves();
  vector<float> posP = mundo->cargarPosicionPlayer_Puerta(2);
  jugador = new Player(posP[0], posP[1]);
  Hud->setDobleSalto(false);
  Hud->setVelocidad(false);
  Hud->setIVelocidad(250);
  Hud->setSlow(false);
  Hud->restablecerVidas();
  Hud->reiniciarTiempo();
  if(jugador->getBody()->getPosicion()[1]<0){
    jugador->getBody()->posicionamiento(posP[0], posP[1]);
  }
  crearObjetos();
  crearEnemigos();
  view.setSize(1024,720);
    
  for(int i = 0 ; i < maxBullets ; i++){
       bulletPlayer[i]=NULL;
  }

  for(int i = 0; i < maxBullets;i++){

      bulletEnemies[i] = NULL;

  }
  for(int i = 0; i < maxBullets;i++){

      bulletNube[i] = NULL;

  }
  for(int i = 0; i < maxBullets;i++){

      bulletBoss[i] = NULL;

  }

}


void Juego::disparar(float deltaTime){ 
  hud * Hud = hud::instance();
  for(int i=0 ; i<maxBullets ; i++){
    if(bulletPlayer[i]==NULL && jugador->getCooldownDisparo()<=0 ){
      if(jugador->getArma() == 1){
          bulletPlayer[i]=new Bullet( jugador->getBody()->getPosicion()[0] , jugador->getBody()->getPosicion()[1], jugador->getFacing() , 1 , 0);
          jugador->setCooldownDisparo(1);
          break;
      }
      if(jugador->getArma() == 2){
          bulletPlayer[i]=new Bullet( jugador->getBody()->getPosicion()[0] , jugador->getBody()->getPosicion()[1], jugador->getFacing() , 1 , 0);
          jugador->setCooldownDisparo(0.2);
          break;
      }
       

    }
  }
    
}


void Juego::colisionBulletMundo(){
    Cuerpo ** objetos = mundo->getObjetos();
  for(unsigned int i=0 ; i<maxBullets ; i++){
    for(int j=0 ; j<mundo->getNumObjetos(); j++){
      if(objetos[j]==NULL) continue;

      if(bulletPlayer[i]!=NULL && objetos[j]->getGlobalBounds()->getIntersect(*bulletPlayer[i]->getBody()->getGlobalBounds())){
        delete bulletPlayer[i];
        bulletPlayer[i]=NULL;
      }
      if(bulletEnemies[i]!=NULL && objetos[j]->getGlobalBounds()->getIntersect(*bulletEnemies[i]->getBody()->getGlobalBounds())){
        delete bulletEnemies[i];
        bulletEnemies[i]=NULL;
      }
      if(bulletBoss[i]!=NULL && objetos[j]->getGlobalBounds()->getIntersect(*bulletBoss[i]->getBody()->getGlobalBounds())){
        delete bulletBoss[i];
        bulletBoss[i]=NULL;
      }
      if(bulletNube[i]!=NULL && objetos[j]->getGlobalBounds()->getIntersect(*bulletNube[i]->getBody()->getGlobalBounds())){
        delete bulletNube[i];
        bulletNube[i]=NULL;
      }
    }
  }
}

void Juego::colisionBulletJugador(){
  hud * Hud = hud::instance();
  bool morir = false;
  for(unsigned int i = 0; i < maxBullets; i++){

    if(bulletEnemies[i] != NULL){

      if(jugador->getBody()->getGlobalBounds()->getIntersect(*bulletEnemies[i]->getBody()->getGlobalBounds())){
        morir = Hud->restarVidas();
        delete bulletEnemies[i];
        bulletEnemies[i] = NULL;
        if(morir == true){
          matarJugador();
        }
      }
    }

    if(bulletNube[i] != NULL){

      if(jugador->getBody()->getGlobalBounds()->getIntersect(*bulletNube[i]->getBody()->getGlobalBounds())){

        morir = Hud->restarVidas();
        delete bulletNube[i];
        bulletNube[i] = NULL;
        if(morir == true){
          matarJugador();
        }
      }
    }

    if(bulletBoss[i] != NULL){

     
      if(jugador->getBody()->getGlobalBounds()->getIntersect(*bulletBoss[i]->getBody()->getGlobalBounds())){
        morir = jugador->setVidas(jugador->getVidas()-2);

        std::cout << "Vidas del jugador: " << jugador->getVidas() << "\n";
        delete bulletBoss[i];
        bulletBoss[i] = NULL;
        
        if(morir == true){
          matarJugador();
        }
      }
    }

  }
  
}

void Juego::colisionBulletEnemigo(){//WIP fachada
  bool morir = false;
  hud * Hud = hud::instance();
  for(unsigned int i=0 ; i < maxBullets ; i++){
    for(int j=0 ; j<numEmenigos ; j++){
      if(bulletPlayer[i]==NULL) continue;
      if(enemies[j]==NULL)      continue;

      if(enemies[j]->getCuerpo()->getGlobalBounds()->getIntersect( *bulletPlayer[i]->getBody()->getGlobalBounds() )){
        delete bulletPlayer[i];
        bulletPlayer[i]=NULL;
        
        if(jugador->getArma()-1 >= 0){
          enemies[j]->restarVida(Hud->getArma()[jugador->getArma()-1]);
        }
        
        if(enemies[j]->muerto == true){
          for (int index = j; index < numEmenigos; index++){
            enemies[index] = enemies[index+1];
          }
          enemies[numEmenigos] = NULL;
          numEmenigos--;
          Hud->sumarPuntos(50);
        }

      }
    }
  }
}


void Juego::cargarMusica(){
   sf::String ss1 = "resources/Sonidos/musica1.ogg";
   sf::String ss2 = "resources/Sonidos/Archer-Bow.ogg";
   sf::String ss3 = "resources/Sonidos/Doom-Pausa.ogg";
   sf::String ss4 = "resources/Sonidos/FireBall.ogg";
   sf::String ss5 = "resources/Sonidos/JUMP.ogg";
   sf::String ss6 = "resources/Sonidos/Male-Hit.ogg";
   sf::String ss7 = "resources/Sonidos/Transicion.ogg";
  
  so = new musica *[7];
    
  so[0] = new musica(ss1);
  so[1] = new musica(ss2);
  so[2] = new musica(ss3);
  so[3] = new musica(ss4);
  so[4] = new musica(ss5);
  so[5] = new musica(ss6);
  so[6] = new musica(ss7);

  so[0]->reproducirMusica();
}

void Juego::comprobarPasarNivel(){
 if( mundo->getPuerta()->getGlobalBounds()->getIntersect(*jugador->getBody()->getGlobalBounds())){
   nextLevel(-1);
 }
}

void Juego::nextLevel(int n){
    Manejador* man = Manejador::instancia();
    Transicion* trans = Transicion::instancia();
    Final* final = Final::instancia();

    if(n == -1){nivel++;} else nivel = n;

    if(nivel < maxniveles){
      delete mundo;
      hud * Hud = hud::instance();
      mundo = new Mundo();
      mundo->cargarmapa(niveles[nivel].c_str());
      mundo->crearSprites();
      mundo->cargarObjectGroups();
      mundo->crearObjetos();
      mundo->cargarPosicionPlayer_Puerta(4);//Puerta
      mundo->crearObstaculos();
      mundo->crearMonedasLlaves();
      vector<float> posP = mundo->cargarPosicionPlayer_Puerta(2);//Player
      jugador->getBody()->posicionamiento(posP[0], posP[1]);
      if(nivel % 4 == 0){
          Hud->setDobleSalto(false);
          Hud->setVelocidad(false);
          Hud->setIVelocidad(250);
          Hud->setSlow(false);
      }
      Hud->reiniciarTiempo();
      crearObjetos();
      crearEnemigos();
      view.setSize(1024,720);
        
      for(int i = 0 ; i < maxBullets ; i++){
          bulletPlayer[i]=NULL;
      }

      for(int i = 0; i < maxBullets;i++){
          bulletEnemies[i] = NULL;
      }

      for(int i = 0; i < maxBullets;i++){
          bulletNube[i] = NULL;
      }

      
      for(int i = 0; i < maxBullets;i++){
          bulletBoss[i] = NULL;
      }

      trans->reset();
      man->cambiarEstado(trans);
    }
    else{
      final->reset();
      man->cambiarEstado(final);
    }
    

    jugador->caer();
}


void Juego::inicializarNiveles(){
  
  niveles = new string[maxniveles];
  niveles[0] = "Mundo1-1.tmx";
  niveles[1] = "Mundo1-2.tmx";
  niveles[2] = "Mundo1-3.tmx";
  niveles[3] = "Mundo1-4.tmx";
  niveles[4] = "Mundo2-1.tmx";
  niveles[5] = "Mundo2-2.tmx";
  niveles[6] = "Mundo2-3.tmx";
  niveles[7] = "Mundo2-4.tmx";
  niveles[8] = "Mundo3-1.tmx";
  niveles[9] = "Mundo3-2.tmx";
  niveles[10] = "Mundo3-3.tmx";
  niveles[11] = "Mundo3-4.tmx";
  niveles[12] = "Mundo4-1.tmx";
  niveles[13] = "Mundo4-2.tmx";
  niveles[14] = "Mundo4-3.tmx";
  niveles[15] = "Mundo4-4.tmx";
  niveles[16] = "Mundo5.tmx";
}
void Juego::nivelSeleccionado(string n){
  int aux = -1;
    for(int i = 0; i < maxniveles; i++){
      if(niveles[i].compare(n) == 0){
       
        aux = i;
        break;
      }
    }
    nextLevel(aux);

}

void Juego::pausa(){
  Manejador* man = Manejador::instancia();
  menu_pausa* menuPau = menu_pausa::instance();
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::P )){
  man->cambiarEstado(menuPau);
  menuPau->resetSelectedItem();
  }
    
}


void Juego::setVolumen(int i, float x){
    so[i]->setVolumen(x);
}

float Juego::getVolumen(int i){
    return so[i]->getVolumen();
}

void Juego::pausarMusica(int i){
  so[i]->pausarMusica();
}

void Juego::reproducirMusica(int i){
  so[i]->reproducirMusica();
}

void Juego::ponerBucleMusica(int i){
  so[i]->ponerBucle();
}
