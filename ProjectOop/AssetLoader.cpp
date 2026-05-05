#include "AssetLoader.h"
#include <iostream>
#include <string>
int Assets::current_level = 1;
string Assets::name = "";
Texture Assets::player;
Texture Assets::run[4];
Texture Assets::walk[4];
Texture Assets::jump[6];
Texture Assets::death[7];
Texture Assets::push[3];
Texture Assets::idle[2];
Texture Assets::fall[1];
Texture Assets::throw_t[8];
Texture Assets::green_run[4], Assets::green_walk[3], Assets::green_jump[3], Assets::green_death[4], Assets::green_idle, Assets::green_fly[6];
Texture Assets::red_run[4], Assets::red_walk[3], Assets::red_death[5], Assets::red_idle, Assets::red_fly[5];
Texture Assets::start_t1;
Texture Assets::start_t2;
Texture Assets::lose_t;
Texture Assets::bg_t;
Texture Assets::tile_t;

Texture Assets::botom_t;

Texture Assets::tornado_death_t[9];
Texture Assets::tornado_run_t[3];
Texture Assets::tornado_knife_t;
Texture Assets::tornado_turn_t[2];
Texture Assets::tornado_free_t[3];
Texture Assets::tornado_idle_t;
Texture Assets::tornado_red_run[3], Assets::tornado_red_die[6], Assets::tornado_red_spin[4], Assets::tornado_red_idle, Assets::tornado_red_knife;

Texture Assets::FFF_hit_t[3];
Texture Assets::FFF_fall_t[3];
Texture Assets::FFF_fly_t[3];
Texture Assets::FFF_red_fly[2], Assets::FFF_red_hit[3], Assets::FFF_red_fall[3], Assets::FFF_red_idle;

Texture Assets::snow_attack_t;
Texture Assets::snow_explode[4];
Texture Assets::snow_frost[4];
Texture Assets::snow_power_roll[4];
Texture Assets::snow_roll[4];

Texture Assets::sushi[5];
Texture Assets::money_t;

Texture Assets::mogera_t;
Texture Assets::mogera_dead_t;
Texture Assets::mogera_flying_t;
Texture Assets::mogera_legs[2];

Texture Assets::gamakichi_t;
Texture Assets::gamakichi_arms[2];
Texture Assets::gamakichi_rocket_t;
Texture Assets::gamakichi_rocket_encased_t;

Font Assets::font;
Music Assets::level_music;
Music Assets::boss_music;
Music Assets::theme[2];
bool Assets::load_all() {
    start_t1.loadFromFile("SnowBrosAssets/Start/start1.png");
    start_t2.loadFromFile("SnowBrosAssets/Start/start2.png");
    lose_t.loadFromFile("SnowBrosAssets/Start/lose1.png");
    font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf");
    level_music.openFromFile("SnowBrosAssets/Sounds/snow_bros_level.ogg");
    boss_music.openFromFile("SnowBrosAssets/Sounds/final_boss_snow_bros.ogg");
    for (int i = 0; i < 6; i++) {
        jump[i].loadFromFile("SnowBrosAssets/Nick_sprites/jump_0" + to_string(i+1) + ".png");
    }
    for (int i = 0; i < 4; i++) {
        run[i].loadFromFile("SnowBrosAssets/Nick_sprites/run_0" + to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 4; i++) {
        walk[i].loadFromFile("SnowBrosAssets/Nick_sprites/walk_0" + to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 3; i++) {
        push[i].loadFromFile("SnowBrosAssets/Nick_sprites/push_0" + to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 7; i++) {
        death[i].loadFromFile("SnowBrosAssets/Nick_sprites/death_0" + to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 8; i++) {
        throw_t[i].loadFromFile("SnowBrosAssets/Nick_sprites/throw_0" + to_string(i + 1) + ".png");
    }

    idle[0].loadFromFile("SnowBrosAssets/Nick_sprites/idle_01.png");
    idle[1].loadFromFile("SnowBrosAssets/Nick_sprites/idle_02.png");
    fall[0].loadFromFile("SnowBrosAssets/Nick_sprites/fall_01.png");

    // Load Green Player
    for (int i = 0; i < 4; i++) green_run[i].loadFromFile("SnowBrosAssets/player_green/run_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 3; i++) green_walk[i].loadFromFile("SnowBrosAssets/player_green/walk_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 3; i++) green_jump[i].loadFromFile("SnowBrosAssets/player_green/jump_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 4; i++) green_death[i].loadFromFile("SnowBrosAssets/player_green/death_0" + to_string(i + 2) + ".png"); // starts from 02
    for (int i = 0; i < 6; i++) green_fly[i].loadFromFile("SnowBrosAssets/player_green/fly_0" + to_string(i + 1) + ".png");
    green_idle.loadFromFile("SnowBrosAssets/player_green/idle.png");

    // Load Red Player
    for (int i = 0; i < 4; i++) red_run[i].loadFromFile("SnowBrosAssets/player_red/run_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 3; i++) red_walk[i].loadFromFile("SnowBrosAssets/player_red/walk_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 5; i++) red_death[i].loadFromFile("SnowBrosAssets/player_red/death_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 5; i++) red_fly[i].loadFromFile("SnowBrosAssets/player_red/fly_0" + to_string(i + 1) + ".png");
    red_idle.loadFromFile("SnowBrosAssets/player_red/idle.png");
    tile_t.loadFromFile("SnowBrosAssets/Level1/tile.png");
    bg_t.loadFromFile("SnowBrosAssets/Level1/bg.png");

    botom_t.loadFromFile("SnowBrosAssets/EnemySprites/Botom.png");
    //tornado
    for (int i = 0; i < 9; i++) {
        tornado_death_t[i].loadFromFile("SnowBrosAssets/Blue_Tornado/death_0" + to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 3; i++) {
        tornado_free_t[i].loadFromFile("SnowBrosAssets/Blue_Tornado/free_0" + to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 3; i++) {
        tornado_run_t[i].loadFromFile("SnowBrosAssets/Blue_Tornado/run_0" + to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 2; i++) {
        tornado_turn_t[i].loadFromFile("SnowBrosAssets/Blue_Tornado/turn_0" + to_string(i + 1) + ".png");
    }
    tornado_idle_t.loadFromFile("SnowBrosAssets/Blue_Tornado/idle.png");
    // Red Tornado
    for (int i = 0; i < 3; i++) tornado_red_run[i].loadFromFile("SnowBrosAssets/tornado_red/run_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 6; i++) tornado_red_die[i].loadFromFile("SnowBrosAssets/tornado_red/die_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 4; i++) tornado_red_spin[i].loadFromFile("SnowBrosAssets/tornado_red/spin_0" + to_string(i + 1) + ".png");
    tornado_red_idle.loadFromFile("SnowBrosAssets/tornado_red/idle.png");
    tornado_red_knife.loadFromFile("SnowBrosAssets/tornado_red/knife.png");
    //fff.
    for (int i = 0; i < 3; i++) {
        FFF_hit_t[i].loadFromFile("SnowBrosAssets/Blue_FFF/Hit_0" + to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 3; i++) {
        FFF_fall_t[i].loadFromFile("SnowBrosAssets/Blue_FFF/Fall_0" + to_string(i + 1) + ".png");
    }
    for (int i = 0; i < 3; i++) {
        FFF_fly_t[i].loadFromFile("SnowBrosAssets/Blue_FFF/fly_0" + to_string(i + 1) + ".png");
    }
    // Red FFF
    for (int i = 0; i < 2; i++) FFF_red_fly[i].loadFromFile("SnowBrosAssets/FFF_red/fly_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 3; i++) FFF_red_hit[i].loadFromFile("SnowBrosAssets/FFF_red/hit_0" + to_string(i + 1) + ".png");
    for (int i = 0; i < 3; i++) FFF_red_fall[i].loadFromFile("SnowBrosAssets/FFF_red/fall_0" + to_string(i + 1) + ".png");
    FFF_red_idle.loadFromFile("SnowBrosAssets/FFF_red/idle.png");



    //Attacks
    tornado_knife_t.loadFromFile("SnowBrosAssets/Blue_Tornado/Knife.png");
    snow_attack_t.loadFromFile("SnowBrosAssets/Nick_sprites/Snow_01.png");
    mogera_t.loadFromFile("SnowBrosAssets/BossSprites/Mogera_01.png");
    gamakichi_t.loadFromFile("SnowBrosAssets/BossSprites/Gamakichi_01.png");

    // Snowball effects
    for (int i = 0; i < 4; i++) {
        snow_explode[i].loadFromFile("SnowBrosAssets/Snowball/Snow_Ball_explode_0" + to_string(i + 1) + ".png");
        snow_frost[i].loadFromFile("SnowBrosAssets/Snowball/frost_0" + to_string(i + 1) + ".png");
        snow_power_roll[i].loadFromFile("SnowBrosAssets/Snowball/power_roll_0" + to_string(i + 1) + ".png");
        snow_roll[i].loadFromFile("SnowBrosAssets/Snowball/roll_0" + to_string(i + 1) + ".png");
    }

    // Sushi
    for (int i = 0; i < 5; i++) {
        sushi[i].loadFromFile("SnowBrosAssets/Sushi/sushi" + to_string(i + 1) + ".png");
    }

    // Items
    money_t.loadFromFile("SnowBrosAssets/items/money.png");

    // More Boss variants
    mogera_dead_t.loadFromFile("SnowBrosAssets/BossSprites/mogera_dead.png");
    mogera_flying_t.loadFromFile("SnowBrosAssets/BossSprites/mogera_flying.png");
    mogera_legs[0].loadFromFile("SnowBrosAssets/BossSprites/mogera_legs_01.png");
    mogera_legs[1].loadFromFile("SnowBrosAssets/BossSprites/mogera_legs_02.png");

    gamakichi_arms[0].loadFromFile("SnowBrosAssets/BossSprites/gamakichi_leftArm.png");
    gamakichi_arms[1].loadFromFile("SnowBrosAssets/BossSprites/gamakichi_rightArm.png");
    gamakichi_rocket_t.loadFromFile("SnowBrosAssets/BossSprites/gamakich_rocket.png");
    gamakichi_rocket_encased_t.loadFromFile("SnowBrosAssets/BossSprites/gamakichi_rocketEncased.png");

    // More Sounds
    theme[0].openFromFile("SnowBrosAssets/Sounds/snow_bros_theme_01.ogg");
    theme[1].openFromFile("SnowBrosAssets/Sounds/snow_bros_theme_02.ogg");

    return true;
}
void Assets::next_level() {
    current_level++;
    tile_t.loadFromFile("SnowBrosAssets/Level" + to_string(current_level) + "/tile.png");
    bg_t.loadFromFile("SnowBrosAssets/Level" + to_string(current_level) + "/bg.png");
}
