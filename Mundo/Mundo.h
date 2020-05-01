#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include "tinyxml.h"

#include "../Textura/Textura.h"
#include "../Bloque/Bloque.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Motor/Motor.h"
using namespace sf;
using namespace std;

class Mundo{
    public:
        Mundo(); //Constructor
        ~Mundo(); //Destructor para liberar memoria

        //Método que carga el mapa creado con tiled del nivel que corresponda
        void cargarmapa(const char * f );
        
        //Método que asigna a todos los tiles del mapa con la textura que le corresponde
        void crearSprites();
        
        //Crea los rectangle shape para las colisiones de las paredes y suelos
        void crearObjetos();

        //Carga las posiciones de los enemigos y de los PowerUps y los coloca en esas posiciones.
        vector<vector<int>> cargarPosicionEnemigos_PowerUps(int i);
        
        //Carga la posición de los bordes del mapa para que el jugador no pueda salirse del mapa.
        vector<int>  cargarPosicionBordes();
        
        //Carga y guarda todos los grupos de objetos
        void cargarObjectGroups();

        //Carga las posiciones del jugador y del final del nivel y los coloca en esas posiciones, y devuelve 
        //la posicion correspondiente
        vector<float> cargarPosicionPlayer_Puerta(int i);

        //Renderiza todos los sprites
        void render();

        //Devuelve un puntero a los rectangleShapes de los objetos del mapa
        Cuerpo ** getObjetos();

        //Devuelve el numero de objetos
        int getNumObjetos();

        //Devuelve el rectangleshape que corresponde con el final del mapa llamado Puerta.
        Cuerpo * getPuerta();
        
    private:
        TiXmlDocument doc;
        TiXmlElement * map;
        VertexArray m_vertices;
        Textura m_tileset;
        int _activeLayer;
        int _width;
        int _height;
        int *_imgwidth;
        int *_imgheight;
        int * cambio;
        int _tileWidth;
        int _tileHeight;
        int _tileCount;
        int _numLayers = 0;
        int _numTilesets = 0;
        int ***_tilemap;
        Bloque ****_tilemapSprite;
        Textura *_tilesetTexture;
        TiXmlElement ** imagenes;



        //objetos
        int _widthObject;
        int _heightObject;
        int _x;
        int _y;
        int _numObjects = 0;
        Cuerpo ** objetos;
        TiXmlElement ** objects;

        //enemigos
        int _posX; 
        int _posY;
        int _tipo;
         TiXmlElement ** objectgroups;

         //bordes; 
         int _X; 
         int _Y; 
         int _Height;

         //puerta 
         Cuerpo * puerta;
         int _widthP;
         int _heightP;
};