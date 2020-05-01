#include <SFML/Graphics.hpp>
#include <iostream>

#ifndef MOTOR_H
#define MOTOR_H

    class Motor{

        friend class Animacion;

        private:
             sf::RenderWindow * ventana;
             bool instanced;
             sf::Clock updateClock;
            static Motor* pinstance;
        
        
        protected:
            Motor();

        public:
            static Motor *instance();
            void dibujo(sf::RectangleShape entrada);
            void dibujo(sf::Sprite entrada);
            void dibujo(sf::CircleShape entrada);
            void dibujo( sf::Text  entrada);
            bool cargarSprite(sf::Texture& entrada, std::string fichero);
            bool cargarSprite(sf::Texture& entrada, const char * fichero);
            void setOrigin(sf::Sprite &entrada, int ancho, int largo);
            void recorte(sf::Sprite &entrada, int xi, int yi, int lengthX, int lengthY);
            void recorte(sf::RectangleShape &entrada, int xi, int yi, int lengthX, int lengthY);
            void setTamanyoCuerpo(sf::RectangleShape& cuerpo,sf::Vector2f entrada);
            void setTextura(sf::RectangleShape& cuerpo, sf::Texture entrada);
            void setTextura(sf::Sprite& cuerpo, sf::Texture entrada);
            void posicionar(sf::RectangleShape& entrada, float x, float y);
            void posicionar(sf::Sprite& entrada, float x, float y);
            float getReloj();
            int getRelojM();
            float restartReloj();
            int restartRelojM();
            void close();
            void limpieza();
            void mostrar();
            bool getOpen();
            char readEventTeclado();
            sf::RenderWindow* getVentana(){return ventana;}
        
            sf::View Camara(sf::Vector2f sad);

    };


#endif