#include "musica.h"

musica::musica(sf::String x){
   //musica 
    if(!soundBuffer.loadFromFile(x)){
<<<<<<< HEAD
      std::cout<< "No se puede encontrar el audio.\n";
=======
      
>>>>>>> 9327cb369c65eb3bcc689ab962a4ffe6cc673392
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
