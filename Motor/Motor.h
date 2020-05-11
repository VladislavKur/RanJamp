#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



#ifndef MOTOR_H
#define MOTOR_H
    
    class Motor{
        //Clase amiga animación.
        friend class Animacion;

        private:
            //La ventana en la que se trabaja.
            sf::RenderWindow * ventana;
            //Se mira si la ventana se encuentra instanciada o no.
            bool instanced;
            //Reloj interno de actualización del juego.
            sf::Clock updateClock;
            //Dirección de memoria de instancia singleton.
            static Motor* pinstance;
        
        protected:
            //Constructor de motor.
            Motor();

        public:
            //Destructor de motor.
            ~Motor();
            //Devuelve la instancia de motor.
            static Motor *instance();
            //Dibuja un Shape en la ventana.
            void dibujo(sf::Shape* entrada);
            //Dibuja un RectangleShape en la ventana.
            void dibujo(sf::RectangleShape & cuerpo);
            //Dibuja un Sprite en la ventana.
            void dibujo(sf::Sprite entrada);
            //Dibuja texto de SFML en la ventana.
            void dibujo( sf::Text  entrada);
            //Carga una textura desde un fichero en la carpeta resources.
            bool cargarSprite(sf::Texture& entrada, std::string fichero);
            //Carga una textura desde un fichero en la carpeta resources.
            bool cargarSprite(sf::Texture& entrada, std::string fichero, bool x);
            //Cambia el origen del sprite.
            void setOrigin(sf::Sprite &entrada, int ancho, int largo);
            //Cambia el origen del sprite.
            void setOrigin2(sf::Sprite &entrada, int ancho, int largo);
            //Recorta la textura en el sprite según los parámetros.
            void recorte(sf::Sprite &entrada, int xi, int yi, int lengthX, int lengthY);
            //Recorta la textura en el sprite según los parámetros.
            void recorte(sf::RectangleShape &entrada, int xi, int yi, int lengthX, int lengthY);
            //Cambia el tamaño del cuerpo.
            void setTamanyoCuerpo(sf::RectangleShape& cuerpo,sf::Vector2f entrada);
            //Asigna una textura a un rectangleshape.
            void setTextura(sf::RectangleShape& cuerpo, sf::Texture entrada);
            //Asigna una textura a un rectangleshape.
            void setTextura(sf::Sprite* cuerpo, sf::Texture* entrada);
            //Posiciona un rectangleshape según los parámetros.
            void posicionar(sf::RectangleShape& entrada, float x, float y);
            //Posiciona un sprite según los parámetros.
            void posicionar(sf::Sprite& entrada, float x, float y);
            //Recorta la textura en el Shape según los parámetros.
            void recorte(sf::Shape* entrada, int xi, int yi, int lengthX, int lengthY);
            //Recorta la textura en el Shape según los parámetros.
            void recorteAnim(sf::Shape* cuerpo,  int xi, int yi, int lengthX, int lengthY);
            //Modifica el tamaño del cuerpo según los parámetros.
            void setTamanyoCuerpo(sf::Shape* cuerpo,sf::Vector2f entrada);
            //Asigna una textura a un shape.
            void setTextura(sf::Shape* cuerpo, sf::Texture* entrada);
            //Posiciona un shape según los parámetros.
            void posicionar(sf::Shape* entrada, float x, float y);
            //Posiciona el origen del shape según los parámetros.
            void posicionarOrigen(sf::Shape* cuerpo, float ancho, float altura);
            //Cambia la escala del Shape según los parámetros.
            void setScale(sf::Shape* cuerpo, float escalaX, float escalaY);
            //Comprueba si dos Shape colisionan.
            bool compararColision(sf::Shape* cuerpo1, sf::Shape* cuerpo2);
            //Se rota un Shape según el ángulo indicado.
            void rotate(sf::Shape* body, float angle);
            
            //Se obtiene el updateClock en segundos.
            float getReloj();
            //Se obtiene el updateClock en milisegundos.
            int getRelojM();
            //Se reinicia el reloj y se devuelve su valor en segundos.
            float restartReloj();
            //Se reinicia el reloj y se devuelve su valor en milisegundos.
            int restartRelojM();
            //Se cierra la ventana.
            void close();
            //Se limpia la ventana.
            void limpieza();
            //Se muestra los elementos que se encuentran en la ventana.
            void mostrar();
            //Devuelve si la ventana se encuentra cerrada o no.
            bool getOpen();
            //Se leen los eventos de teclado.
            char readEventTeclado();
            //Se obtiene la ventana.
            sf::RenderWindow* getVentana(){return ventana;}
            //Se coloca la vista de la cámara.
            sf::View Camara(sf::Vector2f sad);
            //Se obtiene la vista de la cámara.
            sf::View getCamara();

    };


#endif