#include<SFML/Audio.hpp>
#include <iostream>

class musica{
    public:  
        // CONSTRUCTOR, PASANDO UN STRING QUE TIENE LA DIRECCION DE EL ARCHIVO
        musica(sf::String x); 

        // REPRODUCE EL SONIDO
        void reproducirMusica();  

        // PARA EL SONIDO
        void pausarMusica();

        // PONE EN BUCLE EL SONIDO
        void ponerBucle();

        void setVolumen(float vol);

        float getVolumen();
    private:
        sf::SoundBuffer soundBuffer;
        sf::Sound sound;
};