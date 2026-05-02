#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
class Assets {
public:
    static int current_level;
    static string name;
    //Player assets
    static Texture player;
    static Texture run[4];
    static Texture jump[6];
    static Texture walk[4];
    static Texture idle;
    static Texture fall[1];
    //UI screen assets
    static Texture start_t1, start_t2;
    static Texture lose_t;
    //Level Assets
    static Texture bg_t;
    static Texture tile_t;
    //Enemy Assets
    static Texture botom_t;
    static Texture flyng_t;
    static Texture tornado_t;
    static Texture mogera_t;
    static Texture gamakichi_t;
    //Font
    static Font font;
    //Music
    static Music level_music;
    static Music boss_music;

    static bool loadAll();
    static void next_level();
    Assets(int i);
};