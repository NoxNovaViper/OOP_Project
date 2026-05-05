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
    static Texture idle[2];
    static Texture fall[1];
    static Texture throw_t[8];
    //Player Green
    static Texture green_run[4], green_walk[3], green_jump[3], green_death[4], green_idle, green_fly[6];
    //Player Red
    static Texture red_run[4], red_walk[3], red_death[5], red_idle, red_fly[5];
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
    //Tornado Red
    static Texture tornado_red_run[3], tornado_red_die[6], tornado_red_spin[4], tornado_red_idle, tornado_red_knife;
    //FFF assets
    static Texture FFF_hit_t[3];
    static Texture FFF_fall_t[3];
    static Texture FFF_fly_t[3];
    //FFF Red
    static Texture FFF_red_fly[2], FFF_red_hit[3], FFF_red_fall[3], FFF_red_idle;
  
    static Texture snow_attack_t;
    static Texture snow_explode[4];
    static Texture snow_frost[4];
    static Texture snow_power_roll[4];
    static Texture snow_roll[4];

    static Texture sushi[5];
    static Texture money_t;

    static Texture mogera_t;
    static Texture mogera_dead_t;
    static Texture mogera_flying_t;
    static Texture mogera_legs[2];

    static Texture gamakichi_t;
    static Texture gamakichi_arms[2];
    static Texture gamakichi_rocket_t;
    static Texture gamakichi_rocket_encased_t;
    //Font
    static Font font;
    //Music
    static Music level_music;
    static Music boss_music;
    static Music theme[2];

    static bool load_all();
    static void next_level();
    Assets(int i);
};