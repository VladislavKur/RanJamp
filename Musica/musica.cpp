#include "musica.h"

musica::musica(sf::String x){
   //musica 
   std::cout << "estoy en cargar musica " << std::endl;
    if(!soundBuffer.loadFromFile(x)){
      std::cout<<"No se puede encontrar el audio" << std::endl;
    }
    sound.setBuffer(soundBuffer);
}

void musica::reproducirMusica(){
    sound.play();
}

void musica::pausarMusica(){
    sound.stop();
}

void musica::ponerBucle(){
    sound.setLoop(true);
}
