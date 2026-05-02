#include "AssetLoader.h"
#include <iostream>
#include <string>
int Assets::current_level = 1;
string Assets::name = "";
Texture Assets::player;
Texture Assets::run[4];
Texture Assets::walk[4];
Texture Assets::jump[6];
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
    idle.loadFromFile("SnowBrosAssets/Nick_sprites/walk_01.png");
    fall[0].loadFromFile("SnowBrosAssets/Nick_sprites/fall_01.png");
    tile_t.loadFromFile("SnowBrosAssets/Level1/tile.png");
    bg_t.loadFromFile("SnowBrosAssets/Level1/bg.png");
    botom_t.loadFromFile("SnowBrosAssets/EnemySprites//Botom.png");
    flyng_t.loadFromFile("SnowBrosAssets/EnemySprites/FFF.png");
    tornado_t.loadFromFile("SnowBrosAssets/EnemySprites/Tornado.png");
    mogera_t.loadFromFile("SnowBrosAssets/BossSprites/Mogera_01.png");
    gamakichi_t.loadFromFile("SnowBrosAssets/BossSprites/Gamakichi_01.png");
    return true;
}
void Assets::next_level() {
    current_level++;
    tile_t.loadFromFile("SnowBrosAssets/Level" + to_string(current_level) + "/tile.png");
    bg_t.loadFromFile("SnowBrosAssets/Level" + to_string(current_level) + "/bg.png");
}
