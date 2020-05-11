#include "musica.h"

musica::musica(sf::String x){
   //musica 
   std::cout << "estoy en cargar musica " << std::endl;
    if(!soundBuffer.loadFromFile(x)){
      std::cout<<"No se puede encontrar el audio" << std::endl;
    }
    sound.setBuffer(soundBuffer);
    sound.setVolume(50);
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

void musica::setVolumen(float x){
    sound.setVolume(x);
}

float musica::getVolumen(){
    return sound.getVolume();
}
