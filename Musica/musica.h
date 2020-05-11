#include<SFML/Audio.hpp>
#include <iostream>

class musica{
    class menu_vol;
    public:  
        // CONSTRUCTOR, PASANDO UN STRING QUE TIENE LA DIRECCION DE EL ARCHIVO
        musica(sf::String x);
        musica();
        ~musica();
        // REPRODUCE EL SONIDO
        void reproducirMusica();  

        // PARA EL SONIDO
        void pausarMusica();

        // PONE EN BUCLE EL SONIDO
        void ponerBucle();

        void setVolumen(float vol);

        float getVolumen();
        bool getMute(){return mute;}
        void setMute(bool aux ){mute = aux;}
    private:
        sf::SoundBuffer soundBuffer;
        sf::Sound sound;
        bool mute = false;
};