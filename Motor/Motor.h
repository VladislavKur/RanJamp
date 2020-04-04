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
            bool dibujo(sf::RectangleShape entrada);
            bool dibujo(sf::Sprite entrada);
            bool dibujo(sf::CircleShape entrada);
            bool cargarSprite(sf::Texture& entrada, std::string fichero);//wip
            void recorte(sf::RectangleShape &entrada, int xi, int yi, int lengthX, int lengthY);
            void setTamanyoCuerpo(sf::RectangleShape& cuerpo,sf::Vector2f entrada);
            void setTextura(sf::RectangleShape& cuerpo, sf::Texture entrada);
            void posicionar(sf::RectangleShape& entrada, float x, float y);
            //bool crearVentana();
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

    };


#endif