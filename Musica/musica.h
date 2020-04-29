#include<SFML/Audio.hpp>
#include <iostream>

class musica{
    public: 
        musica(sf::String x);
        void reproducirMusica();
        void pausarMusica();
        void ponerBucle();
    private:
        sf::SoundBuffer soundBuffer;
        sf::Sound sound;
};