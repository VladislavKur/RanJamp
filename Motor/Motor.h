#pragma once
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
            void dibujo(sf::Shape* entrada);
            void dibujo(sf::RectangleShape & cuerpo);
            void dibujo(sf::Sprite entrada);
            void dibujo( sf::Text  entrada);
            bool cargarSprite(sf::Texture& entrada, std::string fichero);
            bool cargarSprite(sf::Texture& entrada, std::string fichero, bool x);
            void setOrigin(sf::Sprite &entrada, int ancho, int largo);
            void recorte(sf::Sprite &entrada, int xi, int yi, int lengthX, int lengthY);
            void recorte(sf::RectangleShape &entrada, int xi, int yi, int lengthX, int lengthY);
            void setTamanyoCuerpo(sf::RectangleShape& cuerpo,sf::Vector2f entrada);
            void setTextura(sf::RectangleShape& cuerpo, sf::Texture entrada);
            void setTextura(sf::Sprite* cuerpo, sf::Texture* entrada);
            void posicionar(sf::RectangleShape& entrada, float x, float y);
            void posicionar(sf::Sprite& entrada, float x, float y);
            void recorte(sf::Shape* entrada, int xi, int yi, int lengthX, int lengthY);
            void setTamanyoCuerpo(sf::Shape* cuerpo,sf::Vector2f entrada);
            void setTextura(sf::Shape* cuerpo, sf::Texture* entrada);
            void posicionar(sf::Shape* entrada, float x, float y);
            void mover(sf::Shape* cuerpo, float x, float y);
            void posicionarOrigen(sf::Shape* cuerpo, float ancho, float altura);
            void setScale(sf::Shape* cuerpo, float escalaX, float escalaY);
            bool compararColision(sf::Shape* cuerpo1, sf::Shape* cuerpo2);


            
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
        
            sf::View Camara(sf::Vector2f sad);
            sf::View getCamara();

    };


#endif