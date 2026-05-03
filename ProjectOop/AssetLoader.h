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
    static Texture death[7];
    static Texture push[3];
    static Texture idle;
    static Texture fall[1];
    //UI screen assets
    static Texture start_t1, start_t2;
    static Texture lose_t;
    //Level Assets
    static Texture bg_t;
    static Texture tile_t;
    //botom Assets
    static Texture botom_t;
    //Tornado Assets
    static Texture tornado_death_t[9];
    static Texture tornado_run_t[3];
    static Texture tornado_knife_t;
    static Texture tornado_turn_t[2];
    static Texture tornado_free_t[3];
    static Texture tornado_idle_t;
    //FFF assets
    static Texture FFF_hit_t[3];
    static Texture FFF_fall_t[3];
    static Texture FFF_fly_t[3];


    static Texture snow_attack_t;
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