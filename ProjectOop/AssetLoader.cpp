#include "AssetLoader.h"
#include <iostream>
#include <string>
int Assets::current_level = 1;
string Assets::name = "";
Texture Assets::player;
Texture Assets::run[4];
Texture Assets::walk[4];
Texture Assets::jump[6];
Texture Assets::death[4];
Texture Assets::push[4];
Texture Assets::idle;
Texture Assets::fall[1];
Texture Assets::start_t1;
Texture Assets::start_t2;
Texture Assets::lose_t;
Texture Assets::bg_t;
Texture Assets::tile_t;
Texture Assets::botom_t;
Texture Assets::flyng_t;
Texture Assets::tornado_t;
Texture Assets::flyng_anim[4];
Texture Assets::tornado_anim[4];
Texture Assets::knife_t;
Texture Assets::snow_attack_t;
Texture Assets::mogera_t;
Texture Assets::gamakichi_t;
Font Assets::font;
Music Assets::level_music;
Music Assets::boss_music;
bool Assets::loadAll() {
    start_t1.loadFromFile("SnowBrosAssets/start/start1.png");
    start_t2.loadFromFile("SnowBrosAssets/start/start2.png");
    lose_t.loadFromFile("SnowBrosAssets/start/lose1.png");
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
    for (int i = 0; i < 4; i++) {
        string frameNum = "0" + to_string(i + 1);
        if (!push[i].loadFromFile("SnowBrosAssets/Nick_sprites/push_" + frameNum + ".png")) {
            if (!push[i].loadFromFile("SnowBrosAssets/Nick_sprites/push_snowball_" + frameNum + ".png")) {
                push[i].loadFromFile("SnowBrosAssets/Nick_sprites/walk_" + frameNum + ".png");
            }
        }
        if (!death[i].loadFromFile("SnowBrosAssets/Nick_sprites/death_" + frameNum + ".png")) {
            if (!death[i].loadFromFile("SnowBrosAssets/Nick_sprites/die_" + frameNum + ".png")) {
                death[i].loadFromFile("SnowBrosAssets/Nick_sprites/fall_01.png");
            }
        }
    }
    idle.loadFromFile("SnowBrosAssets/Nick_sprites/walk_01.png");
    fall[0].loadFromFile("SnowBrosAssets/Nick_sprites/fall_01.png");
    tile_t.loadFromFile("SnowBrosAssets/Level1/tile.png");
    bg_t.loadFromFile("SnowBrosAssets/Level1/bg.png");
    botom_t.loadFromFile("SnowBrosAssets/EnemySprites//Botom.png");
    if (!flyng_t.loadFromFile("SnowBrosAssets/Images/FlyingFoogaFoog_Blue.png")) {
        flyng_t.loadFromFile("SnowBrosAssets/EnemySprites/FFF.png");
    }
    if (!tornado_t.loadFromFile("SnowBrosAssets/Images/Tornado_Blue.png")) {
        tornado_t.loadFromFile("SnowBrosAssets/EnemySprites/Tornado.png");
    }
    for (int i = 0; i < 4; i++) {
        string frameNum = "0" + to_string(i + 1);
        if (!flyng_anim[i].loadFromFile("SnowBrosAssets/EnemySprites/FlyingFoogaFoog_Blue_" + frameNum + ".png")) {
            if (!flyng_anim[i].loadFromFile("SnowBrosAssets/Images/FlyingFoogaFoog_Blue_" + frameNum + ".png")) {
                if (!flyng_anim[i].loadFromFile("SnowBrosAssets/EnemySprites/FFF_" + frameNum + ".png")) {
                    flyng_anim[i].loadFromFile("SnowBrosAssets/Images/FlyingFoogaFoog_Blue.png");
                }
            }
        }
        if (!tornado_anim[i].loadFromFile("SnowBrosAssets/EnemySprites/Tornado_Blue_" + frameNum + ".png")) {
            if (!tornado_anim[i].loadFromFile("SnowBrosAssets/Images/Tornado_Blue_" + frameNum + ".png")) {
                if (!tornado_anim[i].loadFromFile("SnowBrosAssets/EnemySprites/Tornado_" + frameNum + ".png")) {
                    tornado_anim[i].loadFromFile("SnowBrosAssets/Images/Tornado_Blue.png");
                }
            }
        }
    }
    knife_t.loadFromFile("SnowBrosAssets/Images/Knife_Tornado_Blue.png");
    snow_attack_t.loadFromFile("SnowBrosAssets/Images/Snow_Attack_Nick.png");
    mogera_t.loadFromFile("SnowBrosAssets/BossSprites/Mogera_01.png");
    gamakichi_t.loadFromFile("SnowBrosAssets/BossSprites/Gamakichi_01.png");
    return true;
}
void Assets::next_level() {
    current_level++;
    tile_t.loadFromFile("SnowBrosAssets/Level" + to_string(current_level) + "/tile.png");
    bg_t.loadFromFile("SnowBrosAssets/Level" + to_string(current_level) + "/bg.png");
}
