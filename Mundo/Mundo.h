#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include "tinyxml.h"

#include "../Motor/Motor.h"
using namespace sf;
using namespace std;

class Mundo{
    public:
        Mundo();
        ~Mundo();
        void cargarmapa(const char * f ); 
        void crearSprites();
        void crearObjetos();
        vector<vector<int>> cargarPosicionEnemigos_PowerUps(int i);
        vector<int>  cargarPosicionBordes();
        void cargarObjectGroups();
        Vector2f cargarPosicionPlayer_Puerta(int i);
        void render();
        RectangleShape ** getObjetos();
        int getNumObjetos();
        RectangleShape * getPuerta();
    private:
        TiXmlDocument doc;
        TiXmlElement * map;
        VertexArray m_vertices;
        Texture m_tileset;
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
        Sprite ****_tilemapSprite;
        Texture *_tilesetTexture;
        TiXmlElement ** imagenes;



        //objetos
        int _widthObject;
        int _heightObject;
        int _x;
        int _y;
        int _numObjects = 0;
        RectangleShape ** objetos;
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
         RectangleShape * puerta;
};