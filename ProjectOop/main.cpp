#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemy_AI.h"
#include "InputHandler.h"
#include "Physics.h"
#include "LevelManager.h"
#include "Player.h"
#include "Animations.h"
#include "AuthManager.h"
#include "DataBase.h"
#include "characterChoiceScreen.h"
#include "EnemyFactory.h"
#include "Snowball.h"
#include "shop.h"
#include "Knife.h"
#include "levelCompleteUI.h"
#include "HUD.h"
#include "BossDefeatedUI.h"
#include "PauseMenu.h"
#include "GameOverUI.h"
#include "ArtilleryProjectile.h"
#include "Boss.h"
#include "characterChoiceUI.h"
#include "mainmenu.h"
#include "loginScreen.h"
#include "AssetLoader.h"
#include "spawnables.h"
#include "Mogera.h"
#include "MogeraChild.h"
#include "Gamakichi.h"
#include "LeaderboardUI.h"
using namespace std;
using namespace sf;

const int max_enemies = 50;
const int max_projectiles = 30;
const int max_spawnables = 20;

int main() {
    srand(static_cast<unsigned int>(time(0)));
    RenderWindow window(VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);

    //Instances and initialization
    Level_Manager manager;
    CharacterSelect select_screen;
    AuthManager auth;
    Mainmenu main_menu;
    PauseMenu pause_menu;
    HUD hud(true);
    Shop shop;
    LoginScreen login_scr;
    LoginScreen login_scr2;
    GameOverScreen game_over_scr;
    LevelCompleteScreen lev_comp_scr;
    Database db;
    LeaderboardUI leaderboard_ui;
    characterChoiceScreen choice_scr(false);

    Enemy* active_enemies[max_enemies];
    Projectile* active_projectiles[max_projectiles];
    int projectile_count = 0;
    int enemy_count = 0;
    spawnable* active_spawnables[max_spawnables];
    int spawnable_count = 0;

    string curr_user = "";
    string curr_user2 = "";
    bool p1_selected = false;
    int p1_char = 1, p2_char = 1;

    // Damage cooldowns for contact damage
    float p1_dmg_cooldown = 0.0f, p2_dmg_cooldown = 0.0f;
    const float DMG_COOLDOWN = 1.5f;

    Assets::load_all();
    login_scr.set_up();
    pause_menu.set_up();
    main_menu.set_up();
    shop.setup();
    lev_comp_scr.set_up();
    game_over_scr.setup();
    login_scr2.set_up();
    login_scr2.set_title("Player 2--Login");

    Sprite bg_s(Assets::bg_t);
    Sprite tile_s(Assets::tile_t);

    Player p1(200, 300, 1, 1), p2(600, 300, 2, 1);
    p1.set_x(200); p1.set_y(300);
    p1.set_vy(0);
    p1.set_hitbox(FloatRect(p1.get_x(), p1.get_y(), 30, 50));
    p2.set_x(600); p2.set_y(300);
    p2.set_vy(0);
    p2.set_hitbox(FloatRect(p2.get_x(), p2.get_y(), 30, 50));
    load_assets(p1);
    load_assets(p2);

    Clock time;
    Font font;
    if (!font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf")) {
        cout << "Rip";
        return 0;
    }

    Sprite start_s(Assets::start_t1);
    start_s.setScale(800.0f / Assets::start_t1.getSize().x, 600.0f / Assets::start_t1.getSize().y);
    float start_timer = 0.0f;
    int start_frame = 0;

    Sprite lose_s(Assets::lose_t);
    lose_s.setScale(800.0f / Assets::lose_t.getSize().x, 600.0f / Assets::lose_t.getSize().y);
    int current_bg_level = 0;

    bg_s.setTexture(Assets::bg_t);
    tile_s.setTexture(Assets::tile_t);
    leaderboard_ui.set_up();

    Assets::level_music.setLoop(true);
    Assets::boss_music.setLoop(true);

    while (window.isOpen()) {
        window.clear(Color::Black);
        float Time = time.restart().asSeconds();

        if (manager.get_start_screen()) {
            start_timer += Time;
            if (start_timer >= 0.5f) {
                start_timer = 0.0f;
                start_frame = 1 - start_frame;
                if (start_frame == 0) {
                    start_s.setTexture(Assets::start_t1);
                    start_s.setScale(800.0f / Assets::start_t1.getSize().x, 600.0f / Assets::start_t1.getSize().y);
                }
                else {
                    start_s.setTexture(Assets::start_t2);
                    start_s.setScale(800.0f / Assets::start_t2.getSize().x, 600.0f / Assets::start_t2.getSize().y);
                }
            }
        }
        Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed)
                window.close();

            if (manager.get_start_screen()) {
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Enter) {
                    manager.set_start_screen(false);
                    manager.set_login(true);
                }
            }
            else if (manager.get_login()) {
                bool login = (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Enter);
                login_scr.handle_input(ev, window);
                if (login_scr.get_is_logged_in() || login) {
                    string user = login_scr.get_logged_in_username();
                    if (!user.empty()) {
                        if (login) {
                            auth.registerUser(user, "pass");
                            if (!auth.loginUser(user, "pass")) return 0;
                        }
                        curr_user = user;
                        manager.set_login(false);
                        manager.set_main_menu(true);
                        int lvl, liv, gems, sc;
                        db.load_progress(curr_user, lvl, liv, gems, sc);
                        p1.set_lives(liv);
                        p1.set_score(sc);
                        p1.set_gemCount(gems);
                    }
                }
            }
            else if (manager.get_login2()) {
                login_scr2.handle_input(ev, window);
                if (login_scr2.get_is_logged_in()) {
                    string user2 = login_scr2.get_logged_in_username();
                    if (!user2.empty()) {
                        curr_user2 = user2;
                        manager.set_login2(false);
                        manager.set_character_select(true);
                        select_screen.set_up(2);
                        int lvl2, liv2, gems2, sc2;
                        db.load_progress(curr_user2, lvl2, liv2, gems2, sc2);
                        p2.set_lives(liv2);
                        p2.set_score(sc2);
                        p2.set_gemCount(gems2);
                    }
                }
            }
            else if (manager.get_main_menu()) {
                main_menu.handle_input(ev, window);
                manager.set_lev(0);
                current_bg_level = 0;
                p1.set_lives(3);
                p1.set_score(0);
                p1.set_gemCount(0);
                p1.setHP(2);
                if (!main_menu.get_is_single_player()) {
                    p2.set_lives(3);
                    p2.set_score(0);
                    p2.set_gemCount(0);
                    p2.setHP(2);
                }
                if (main_menu.get_choice() == 1) {
                    manager.set_main_menu(false);
                    if (!main_menu.get_is_single_player()) {
                        manager.set_login2(true);
                    }
                    else {
                        manager.set_character_select(true);
                        select_screen.set_up(1);
                    }
                }
                if (main_menu.get_choice() == 2) {//Continue logic
                    int lvl, liv, gems, sc;
                    db.load_progress(curr_user, lvl, liv, gems, sc);
                    if (lvl > 0) {
                        p1.set_lives(liv);
                        p1.set_score(sc);
                        p1.set_gemCount(gems);
                        manager.set_lev(lvl);
                        current_bg_level = lvl - 1;
                        manager.set_main_menu(false);
                        manager.set_character_select(true);
                        select_screen.set_up(1);
                    }
                }
                if (main_menu.get_choice() == 3) {  //Leaderboard
                    leaderboard_ui.load_data(db);
                    leaderboard_ui.set_open(true);
                    manager.set_main_menu(false);
                    manager.set_leaderboard(true);
                }
                if (main_menu.get_choice() == 4) {  //Exit
                    window.close();
                }
            }
            else if (manager.get_leaderboard()) {
                leaderboard_ui.handle_input(ev, window);
                if (!leaderboard_ui.get_is_open()) {
                    manager.set_leaderboard(false);
                    manager.set_main_menu(true);
                    main_menu.reset_choice();
                }
            }
            else if (manager.get_pause()) {
                pause_menu.handle_input(ev, window);
            }
            else if (manager.get_shop()) {
                shop.handleInput(ev, window, p1);
                if (!shop.getIsOpen()) {
                    manager.set_shop(false);
                    manager.set_pause(true);
                    pause_menu.open();
                }
            }
            else if (manager.get_character_select()) {
                select_screen.handle_input(ev, window);
                if (select_screen.get_selection_done()) {
                    if (!p1_selected) {
                        p1_char = select_screen.get_choice();
                        choice_scr.player1Select(p1_char);
                        p1_selected = true;
                        hud = HUD(false);
                        hud.setup();
                        if (!main_menu.get_is_single_player()) {
                            select_screen.set_up(1);
                            continue;
                        }
                        else {
                            p2_char = 1;
                            choice_scr.player2Select(p2_char);
                            choice_scr.confirmSelection();
                            int p1_lives = p1.get_lives(), p1_score = p1.get_score(), p1_gems = p1.get_gemCount();
                            p1 = Player(200, 300, 1, p1_char);
                            p1.set_lives(p1_lives); p1.set_score(p1_score); p1.set_gemCount(p1_gems);
                            p1.set_hitbox(FloatRect(200, 300, 30, 50));
                            load_assets(p1);
                            p1_selected = false;
                            hud = HUD(true);
                            hud.setup();
                            manager.set_character_select(false);
                            manager.set_play(true);
                            manager.set_next_level(true);
                            Assets::level_music.play();
                            game_over_scr = GameOverScreen();
                            game_over_scr.setup();
                        }
                    }
                    else {
                        p2_char = select_screen.get_choice();
                        choice_scr.player2Select(p2_char);
                        choice_scr.confirmSelection();
                        int p1_lives = p1.get_lives(), p1_score = p1.get_score(), p1_gems = p1.get_gemCount();
                        int p2_lives = p2.get_lives(), p2_score = p2.get_score(), p2_gems = p2.get_gemCount();
                        p1 = Player(200, 300, 1, p1_char);
                        p2 = Player(600, 300, 2, p2_char);
                        p1.set_lives(p1_lives); p1.set_score(p1_score); p1.set_gemCount(p1_gems);
                        p2.set_lives(p2_lives); p2.set_score(p2_score); p2.set_gemCount(p2_gems);
                        p1.set_hitbox(FloatRect(200, 300, 30, 50));
                        p2.set_hitbox(FloatRect(600, 300, 30, 50));
                        load_assets(p1);
                        load_assets(p2);
                        p1_selected = false;
                        manager.set_character_select(false);
                        manager.set_play(true);
                        manager.set_next_level(true);
                        Assets::level_music.play();
                        game_over_scr = GameOverScreen();
                        game_over_scr.setup();
                    }
                }
            }
            else if (manager.get_lose()) {
                game_over_scr.handleInput(ev, window);
            }
            else if (manager.get_win()) {
                lev_comp_scr.handle_input(ev, window);
            }
            else {
                Inputhandle(ev, manager, window, p1, p2, active_projectiles, projectile_count);
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::P) {
                    manager.set_pause(true);
                    manager.set_play(false);
                    pause_menu.open();
                }
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::T) {
                    manager.set_play(false);
                    manager.set_shop(true);
                    shop.opentheShop();
                }
            }
        }

        //HUD update
        int bossHP = 0, bossMaxHP = 100;
        bool bossActive = false;
        for (int i = 0; i < enemy_count; i++) {
            if (active_enemies[i] != nullptr && active_enemies[i]->get_enemy_type() >= 4) {
                bossHP = active_enemies[i]->getHP();
                bossMaxHP = active_enemies[i]->get_max_hp();
                bossActive = true;
                break;
            }
        }
        hud.setBossLevel(bossActive);
        hud.update(p1.get_score(), p1.get_lives(), p1.get_gemCount(),
            p2.get_score(), p2.get_lives(), p2.get_gemCount(),
            current_bg_level, 10, "", bossHP, bossMaxHP);

        //movement logic in game
        if (!manager.get_login() && !manager.get_login2() && !manager.get_character_select() && !manager.get_pause() &&
            !manager.get_shop() && !manager.get_main_menu() && !manager.get_leaderboard() && manager.get_play()) {

            if (Keyboard::isKeyPressed(Keyboard::A)) {
                p_move(p1, -p1.get_speed(), Time, true);
                p1.right_facing = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                p_move(p1, p1.get_speed(), Time, true);
                p1.right_facing = true;
            }
            if (!main_menu.get_is_single_player()) {
                if (Keyboard::isKeyPressed(Keyboard::Num4)) {
                    p_move(p2, -p2.get_speed(), Time, true);
                    p2.right_facing = false;
                }
                if (Keyboard::isKeyPressed(Keyboard::Num6)) {
                    p_move(p2, p2.get_speed(), Time, true);
                    p2.right_facing = true;
                }
            }

            // Update damage cooldowns
            if (p1_dmg_cooldown > 0) {
                p1_dmg_cooldown -= Time;
            }
            if (p2_dmg_cooldown > 0) {
                p2_dmg_cooldown -= Time;
            }

            // Checks for gameover
            if (manager.get_play() && !manager.get_lose()){
                bool p1_dead = (p1.get_lives() <= 0);
                bool p2_dead = main_menu.get_is_single_player() || (p2.get_lives() <= 0);

                if (p1_dead && p2_dead) {
                    manager.set_play(false);
                    manager.set_lose(true);
                    game_over_scr.setData(p1.get_score() + p2.get_score(), current_bg_level);
                    db.save_leaderboard(curr_user, p1.get_score(), current_bg_level);
                    if (!main_menu.get_is_single_player())
                        db.save_leaderboard(curr_user2, p2.get_score(), current_bg_level);
                }
            }

            //P1 Physics
            apply_gravity(p1, 980.0f, Time);
            position_change(p1, true, p1.get_vy(), Time, false);
            FloatRect h1 = p1.get_hitbox();
            h1.left = p1.get_x();
            h1.top = p1.get_y();
            p1.set_hitbox(h1);

            if (!main_menu.get_is_single_player()) {
                apply_gravity(p2, 980.0f, Time);
                position_change(p2, true, p2.get_vy(), Time, false);
                FloatRect h2 = p2.get_hitbox();
                h2.left = p2.get_x();
                h2.top = p2.get_y();
                p2.set_hitbox(h2);
            }

            //Player 1 Platform Collision
            p1.set_on_ground(false);
            if (manager.get_current_level() != nullptr) {
                float p1_bottom = p1.get_y() + p1.get_hitbox().height;
                for (int i = 0; i < manager.get_current_level()->num_platforms; i++) {
                    platform pt = manager.get_current_level()->platforms[i];
                    if (p1.get_vy() >= 0 && p1.get_hitbox().intersects(pt.collison)) {
                        if (p1_bottom - pt.y < 30.0f) {
                            Fix_collision(p1, pt.y);
                            p1.set_on_ground(true);
                            FloatRect h1_new = p1.get_hitbox();
                            h1_new.left = p1.get_x();
                            h1_new.top = p1.get_y();
                            p1.set_hitbox(h1_new);
                            break;
                        }
                    }
                }
            }
            if (p1.get_y() > 500) {
                p1.set_y(500);
                p1.set_vy(0);
                p1.set_on_ground(true);
            }

            //Player 2 Platform Collision
            if (!main_menu.get_is_single_player()) {
                p2.set_on_ground(false);
                if (manager.get_current_level() != nullptr) {
                    float p2_bottom = p2.get_y() + p2.get_hitbox().height;
                    for (int i = 0; i < manager.get_current_level()->num_platforms; i++) {
                        platform pt = manager.get_current_level()->platforms[i];
                        if (p2.get_vy() >= 0 && p2.get_hitbox().intersects(pt.collison)) {
                            if (p2_bottom - pt.y < 30.0f) {
                                Fix_collision(p2, pt.y);
                                p2.set_on_ground(true);
                                FloatRect h2_new = p2.get_hitbox();
                                h2_new.left = p2.get_x();
                                h2_new.top = p2.get_y();
                                p2.set_hitbox(h2_new);
                                break;
                            }
                        }
                    }
                }
                if (p2.get_y() > 500) {
                    p2.set_y(500);
                    p2.set_vy(0);
                    p2.set_on_ground(true);
                }
            }

            //Enemy Updates
            for (int i = 0; i < enemy_count; i++) {
                if (active_enemies[i] != nullptr) {
                    active_enemies[i]->curr_level_pt = manager.get_current_level();
                    active_enemies[i]->update(Time);
                    active_enemies[i]->check_platform_collision(manager.get_current_level());

                    // Contact damage
                    if (!active_enemies[i]->get_rolling() && !active_enemies[i]->get_encased()) {
                        if (p1_dmg_cooldown <= 0 && p1.get_hitbox().intersects(active_enemies[i]->getHitbox())) {
                            p1.takeDamage();
                            p1_dmg_cooldown = DMG_COOLDOWN;
                        }
                        if (!main_menu.get_is_single_player() && p2_dmg_cooldown <= 0 && p2.get_hitbox().intersects(active_enemies[i]->getHitbox())) {
                            p2.takeDamage();
                            p2_dmg_cooldown = DMG_COOLDOWN;
                        }
                    }

                    if (active_enemies[i]->spawn && enemy_count < max_enemies) {
                        float targetX = p1.get_x();
                        if (!main_menu.get_is_single_player()) {
                            if (abs(p2.get_x() - active_enemies[i]->getx()) < abs(p1.get_x() - active_enemies[i]->getx()))
                                targetX = p2.get_x();
                        }
                        Enemy* spawnedEnemy = EnemyFactory::e(active_enemies[i]->spawn_type, active_enemies[i]->spawn_x, active_enemies[i]->spawn_y, targetX);
                        if (spawnedEnemy != nullptr) {
                            active_enemies[enemy_count++] = spawnedEnemy;
                            spawnedEnemy->set_vy(active_enemies[i]->spawn_vy);
                            MogeraChild* mc = dynamic_cast<MogeraChild*>(spawnedEnemy);
                            if (mc) mc->set_direction_x(active_enemies[i]->spawn_vx > 0 ? 1.0f : -1.0f);
                        }
                        active_enemies[i]->spawn = false;
                    }

                    if (active_enemies[i]->projectile && projectile_count < max_projectiles) {
                        if (active_enemies[i]->projectileType == "Artillery") {
                            float tx = p1.get_x(), ty = p1.get_y();
                            if (!main_menu.get_is_single_player()) {
                                if (abs(p2.get_x() - active_enemies[i]->getx()) < abs(p1.get_x() - active_enemies[i]->getx())) {
                                    tx = p2.get_x(); ty = p2.get_y();
                                }
                            }
                            float dx = tx - active_enemies[i]->px;
                            float aimed_vx = (dx / 1.2f) + active_enemies[i]->pvx;
                            active_projectiles[projectile_count++] = new ArtilleryProjectile(
                                active_enemies[i]->px, active_enemies[i]->py,
                                aimed_vx, active_enemies[i]->pvy);
                        }
                        else if (active_enemies[i]->projectileType == "Knife") {
                            float tx = p1.get_x(), ty = p1.get_y();
                            if (!main_menu.get_is_single_player()) {
                                if (abs(p2.get_x() - active_enemies[i]->getx()) < abs(p1.get_x() - active_enemies[i]->getx())) {
                                    tx = p2.get_x(); ty = p2.get_y();
                                }
                            }
                            active_projectiles[projectile_count++] = new Knife(active_enemies[i]->px, active_enemies[i]->py, tx, ty);
                        }
                        active_enemies[i]->projectile = false;
                    }

                    // Kicking encased enemies
                    if (active_enemies[i]->get_encased() && !active_enemies[i]->get_rolling()) {
                        if (p1.get_hitbox().intersects(active_enemies[i]->getHitbox())) {
                            float kickDir = (p1.get_x() < active_enemies[i]->getx()) ? 400.0f : -400.0f;
                            active_enemies[i]->start_rolling(kickDir);
                        }
                        if (p2.get_hitbox().intersects(active_enemies[i]->getHitbox())) {
                            float kickDir = (p2.get_x() < active_enemies[i]->getx()) ? 400.0f : -400.0f;
                            active_enemies[i]->start_rolling(kickDir);
                        }
                    }

                    // Remove dead enemies
                    if (active_enemies[i]->getHP() <= 0) {
                        if (spawnable_count < max_spawnables) {
                            if (rand() % 100 < 60) {
                                if (rand() % 100 < 70)
                                    active_spawnables[spawnable_count++] = new money(active_enemies[i]->getx(), active_enemies[i]->gety());
                                else
                                    active_spawnables[spawnable_count++] = new powerup(active_enemies[i]->getx(), active_enemies[i]->gety(), rand() % 5);
                            }
                        }
                        delete active_enemies[i];
                        for (int j = i; j < enemy_count - 1; j++)
                            active_enemies[j] = active_enemies[j + 1];
                        enemy_count--;
                        i--;
                    }
                }
            }

            //Projectile Updates
            for (int i = 0; i < projectile_count; i++) {
                if (active_projectiles[i] != nullptr) {
                    active_projectiles[i]->update(Time);
                    for (int j = 0; j < enemy_count; j++) {
                        if (active_enemies[j] != nullptr) {
                            bool isSnowball = dynamic_cast<Snowball*>(active_projectiles[i]) != nullptr;
                            if (!isSnowball) continue;
                            if (active_projectiles[i]->getHitbox().intersects(active_enemies[j]->getHitbox())) {
                                active_enemies[j]->hit();
                                active_projectiles[i]->setisactive(false);
                                break;
                            }
                        }
                    }
                    // Enemy projectiles damage players
                    if (dynamic_cast<Snowball*>(active_projectiles[i]) == nullptr) {
                        FloatRect projHitbox = active_projectiles[i]->getHitbox();
                        if (projHitbox.intersects(p1.get_hitbox())) {
                            p1.takeDamage();
                            active_projectiles[i]->setisactive(false);
                        }
                        if (!main_menu.get_is_single_player() && projHitbox.intersects(p2.get_hitbox())) {
                            p2.takeDamage();
                            active_projectiles[i]->setisactive(false);
                        }
                    }
                    if (!active_projectiles[i]->getisactive()) {
                        delete active_projectiles[i];
                        for (int j = i; j < projectile_count - 1; j++)
                            active_projectiles[j] = active_projectiles[j + 1];
                        projectile_count--;
                        i--;
                    }
                }
            }

            //Snowball roll logic
            for (int i = 0; i < enemy_count; i++) {
                if (active_enemies[i] != nullptr && active_enemies[i]->get_rolling()) {
                    FloatRect Hitbox_SnowBall = active_enemies[i]->getHitbox();
                    for (int j = 0; j < enemy_count; j++) {
                        if (i == j || active_enemies[j] == nullptr) continue;
                        if (Hitbox_SnowBall.intersects(active_enemies[j]->getHitbox()))
                            active_enemies[j]->kill();
                    }
                }
            }

            //Spawnable Updates
            for (int i = 0; i < spawnable_count; i++) {
                if (active_spawnables[i] != nullptr) {
                    active_spawnables[i]->update(Time);
                    bool collected = false;
                    if (p1.get_hitbox().intersects(active_spawnables[i]->get_hitbox())) {
                        p1.set_score(p1.get_score() + 100);
                        if (dynamic_cast<powerup*>(active_spawnables[i])) p1.set_gemCount(p1.get_gemCount() + 1);
                        collected = true;
                    }
                    else if (!main_menu.get_is_single_player() && p2.get_hitbox().intersects(active_spawnables[i]->get_hitbox())) {
                        p2.set_score(p2.get_score() + 100);
                        if (dynamic_cast<powerup*>(active_spawnables[i])) p2.set_gemCount(p2.get_gemCount() + 1);
                        collected = true;
                    }
                    if (collected) {
                        delete active_spawnables[i];
                        for (int j = i; j < spawnable_count - 1; j++)
                            active_spawnables[j] = active_spawnables[j + 1];
                        spawnable_count--;
                        i--;
                    }
                }
            }

            // Boss defeat check
            bool boss_defeated = false;
            if (manager.get_boss()) {
                for (int i = 0; i < enemy_count; i++) {
                    Boss* b = dynamic_cast<Boss*>(active_enemies[i]);
                    if (b != nullptr && b->get_is_defeated()) {
                        boss_defeated = true;
                        for (int k = 0; k < enemy_count; k++)
                            if (active_enemies[k] != b) active_enemies[k]->kill();
                    }
                }
            }

            // Level clear
            if ((enemy_count == 0 || boss_defeated) && spawnable_count == 0 && manager.get_play() && !manager.get_next_level()) {
                manager.set_play(false);
                manager.set_win(true);
                lev_comp_scr.set_data(p1.get_score() + p2.get_score(), p1.get_gemCount() + p2.get_gemCount());
            }

            // Level up
            if (((enemy_count == 0 && spawnable_count == 0) || boss_defeated || manager.get_next_level()) && manager.get_play()) {
                manager.next_level();
                manager.set_next_level(false);
                current_bg_level++;
                if (current_bg_level > 10) current_bg_level = 1;

                string new_bg = "SnowBrosAssets/Level" + to_string(current_bg_level) + "/bg.png";
                string new_tile = "SnowBrosAssets/Level" + to_string(current_bg_level) + "/tile.png";
                if (Assets::bg_t.loadFromFile(new_bg)) {
                    bg_s.setTexture(Assets::bg_t, true);
                    bg_s.setScale(800.0f / Assets::bg_t.getSize().x, 600.0f / Assets::bg_t.getSize().y);
                }
                if (Assets::tile_t.loadFromFile(new_tile))
                    tile_s.setTexture(Assets::tile_t, true);

                if (manager.get_boss()) {
                    Assets::level_music.stop();
                    Assets::boss_music.play();
                }
                else {
                    Assets::boss_music.stop();
                    if (Assets::level_music.getStatus() != Music::Playing) Assets::level_music.play();
                }

                level* current_lvl = manager.get_current_level();
                if (current_lvl != nullptr && current_lvl->num_enemies > 0) {
                    for (int i = 0; i < current_lvl->num_enemies; i++) {
                        enemy_spawn es = current_lvl->enemies[i];
                        Enemy* ne = EnemyFactory::e(es.type, es.x, es.y);
                        if (ne != nullptr) {
                            if (current_bg_level > 5) {
                                ne->variant = true;
                            }
                            active_enemies[enemy_count++] = ne;
                        }
                    }
                }
            }
        }

        //=======All Draws======
        if (manager.get_start_screen()) {
            window.draw(start_s);
        }
        else if (manager.get_login()) {
            login_scr.draw(window);
        }
        else if (manager.get_login2()) {
            login_scr2.draw(window);
        }
        else if (manager.get_main_menu()) {
            main_menu.draw(window);
        }
        else if (manager.get_leaderboard()) {
            leaderboard_ui.draw(window);
        }
        else if (manager.get_character_select()) {
            select_screen.draw(window);
        }
        else if (manager.get_pause()) {
            pause_menu.draw(window);
            if (pause_menu.get_choice() == 1) {
                manager.set_pause(false);
                manager.set_play(true);
                pause_menu.close();
                pause_menu.reset_choice();
            }
            if (pause_menu.get_choice() == 2) {
                manager.set_pause(false);
                manager.set_shop(true);
                shop.opentheShop();
                pause_menu.close();
                pause_menu.reset_choice();
            }
            if (pause_menu.get_choice() == 3) {
                db.save_progress(curr_user, current_bg_level, p1.get_lives(), p1.get_gemCount(), p1.get_score());
                db.save_leaderboard(curr_user, p1.get_score(), current_bg_level);
                if (!main_menu.get_is_single_player()) {
                    db.save_progress(curr_user2, current_bg_level, p2.get_lives(), p2.get_gemCount(), p2.get_score());
                    db.save_leaderboard(curr_user2, p2.get_score(), current_bg_level);
                }
                pause_menu.reset_choice();
            }
            if (pause_menu.get_choice() == 4) {
                db.save_progress(curr_user, current_bg_level, p1.get_lives(), p1.get_gemCount(), p1.get_score());
                manager.set_pause(false);
                manager.set_play(false);
                login_scr = LoginScreen();
                login_scr.set_up();
                manager.set_login(true);
                p1_selected = false;
                main_menu.reset_choice();
                pause_menu.close();
                pause_menu.reset_choice();
                curr_user = "";
            }
            if (pause_menu.get_choice() == 5) {
                db.save_progress(curr_user, current_bg_level, p1.get_lives(), p1.get_gemCount(), p1.get_score());
                if (!main_menu.get_is_single_player())
                    db.save_progress(curr_user2, current_bg_level, p2.get_lives(), p2.get_gemCount(), p2.get_score());
                manager.set_pause(false);
                manager.set_play(false);
                manager.set_main_menu(true);
                p1_selected = false;
                main_menu.reset_choice();
                pause_menu.close();
                pause_menu.reset_choice();
            }
        }
        else if (manager.get_shop()) {
            shop.draw(window, p1);
        }
        else if (manager.get_win()) {
            lev_comp_scr.draw(window);
            if (lev_comp_scr.get_choice() == 1) {
                lev_comp_scr = LevelCompleteScreen();
                lev_comp_scr.set_up();
                manager.set_win(false);
                manager.set_play(true);
                manager.set_next_level(true);
            }
        }
        else if (manager.get_lose()) {
            game_over_scr.draw(window);
            if (game_over_scr.getChoice() == 1) { //retry incase
                // Reset enemies and projectiles
                for (int i = 0; i < enemy_count; i++) {
                    delete active_enemies[i]; 
                    active_enemies[i] = nullptr;
                }
                for (int i = 0; i < projectile_count; i++) { 
                    delete active_projectiles[i]; 
                    active_projectiles[i] = nullptr;
                }
                for (int i = 0; i < spawnable_count; i++) { delete active_spawnables[i]; active_spawnables[i] = nullptr; }
                enemy_count = 0; projectile_count = 0; spawnable_count = 0;
                p1.setHP(2);
                p1.set_lives(3);
                manager.set_lev(0);
                current_bg_level = 0;
                manager.set_lose(false);
                manager.set_play(true);
                manager.set_next_level(true);
                game_over_scr = GameOverScreen();
                game_over_scr.setup();
            }
            if (game_over_scr.getChoice() == 2) { //Main Menu
                for (int i = 0; i < enemy_count; i++) { delete active_enemies[i]; active_enemies[i] = nullptr; }
                for (int i = 0; i < projectile_count; i++) { delete active_projectiles[i]; active_projectiles[i] = nullptr; }
                for (int i = 0; i < spawnable_count; i++) { delete active_spawnables[i]; active_spawnables[i] = nullptr; }
                enemy_count = 0; projectile_count = 0; spawnable_count = 0;
                Assets::level_music.stop();
                Assets::boss_music.stop();
                manager.set_lev(0);        
                current_bg_level = 0;       
                p1.set_lives(3);           
                p1.setHP(2);
                manager.set_lose(false);
                manager.set_main_menu(true);
                main_menu.reset_choice();
                game_over_scr = GameOverScreen();
                game_over_scr.setup();
            }
        }
        else {
            window.draw(bg_s);
            if (manager.get_current_level() != nullptr) {
                for (int i = 0; i < manager.get_current_level()->num_platforms; i++) {
                    platform& plt = manager.get_current_level()->platforms[i];
                    tile_s.setScale(static_cast<float>(plt.w) / Assets::tile_t.getSize().x, static_cast<float>(plt.h) / Assets::tile_t.getSize().y);
                    tile_s.setPosition(plt.x, plt.y);
                    window.draw(tile_s);
                }
            }
            update_animations(p1, Time, !p1.right_facing, p1.right_facing);
            window.draw(p1.get_sprite());
            if (!main_menu.get_is_single_player()) {
                update_animations(p2, Time, !p2.right_facing, p2.right_facing);
                window.draw(p2.get_sprite());
            }
            for (int i = 0; i < enemy_count; i++)
                if (active_enemies[i] != nullptr) active_enemies[i]->draw(window);
            for (int i = 0; i < projectile_count; i++)
                if (active_projectiles[i] != nullptr) active_projectiles[i]->draw(window);
            for (int i = 0; i < spawnable_count; i++)
                if (active_spawnables[i] != nullptr) active_spawnables[i]->draw(window);

            if (manager.get_current_level() != nullptr) {
                debug_view(manager, p1.get_hitbox(), manager.get_current_level()->platforms, manager.get_current_level()->num_platforms, window);
                debug_view(manager, p2.get_hitbox(), manager.get_current_level()->platforms, 0, window);
                if (manager.get_debug()) {
                    for (int i = 0; i < enemy_count; i++)
                        if (active_enemies[i] != nullptr) draw_debug_box(window, active_enemies[i]->getHitbox(), Color::Red);
                    for (int i = 0; i < projectile_count; i++)
                        if (active_projectiles[i] != nullptr) draw_debug_box(window, active_projectiles[i]->getHitbox(), Color::Yellow);
                }
            }
            if (manager.get_lose()) window.draw(lose_s);
        }

        if (manager.get_play() || manager.get_pause() || manager.get_shop())
            hud.draw(window);
        window.display();
    }
    return 0;
}