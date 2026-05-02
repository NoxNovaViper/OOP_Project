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
#include"shop.h"
#include "Knife.h"
#include "levelCompleteUI.h"
#include "HUD.h"
#include "BossDefeatedUI.h"
#include "PauseMenu.h"
#include "GameOverUI.h"
#include "characterChoiceUI.h"
#include "mainmenu.h"
#include "loginScreen.h"
#include "AssetLoader.h"
using namespace std;
using namespace sf;
//constantss
const int max_enemies = 50;
const int max_projectiles = 30;
int main(){
	//start video rendering
    RenderWindow window(VideoMode(800, 600), "Snow Bros");
    window.setFramerateLimit(60);
	//==========Instances and initialization and declerations===========
    Level_Manager manager;
    CharacterSelect select_screen;
    AuthManager auth;
    Mainmenu main_menu;
    PauseMenu pause_menu;
    HUD hud(true);
    Shop shop;
    LoginScreen loginScreen;
    GameOverScreen gameOverScreen;
    LevelCompleteScreen levelCompleteScreen;
    Database db;
	characterChoiceScreen choiceScreen(false);//false for 2 player mode, true for single player
	string currentUser = "";//variable to hold the current logged in user
    Enemy* active_enemies[max_enemies];
    Projectile* active_projectiles[max_projectiles];
    int projectile_count = 0;
    int enemy_count = 0;
    LoginScreen loginScreen2;
    string currentUser2 = "";
    bool showLeaderboard = false;
    Assets::loadAll();
    loginScreen.setup();
    pause_menu.setup();
    main_menu.setup();
    shop.setup();
    levelCompleteScreen.setup();
    gameOverScreen.setup();
    loginScreen2.setup();
  
    loginScreen2.setTitle("Player 2--Login");
    bool p1Selected = false;
    Sprite bg_s(Assets::bg_t);
    Sprite tile_s(Assets::tile_t);
    Player p1(200, 300, 1, 1), p2(600, 300, 2, 1);
	//============P1 Initialization==============
    p1.set_x(200); p1.set_y(300);
    p1.set_vy(0);
    p1.set_hitbox(FloatRect(p1.get_x(), p1.get_y(), 30, 50));
    //============P2 Initialization==============
    p2.set_x(600); p2.set_y(300);
    p2.set_vy(0);
    p2.set_hitbox(FloatRect(p2.get_x(), p2.get_y(), 30, 50));
    load_assets(p1);
    load_assets(p2);
   //=============Clock for delta time===========
    Clock time;
    //==========font for text===============
	Font font;
    if (!font.loadFromFile("SnowBrosAssets/Fonts/Starborn.ttf")) {
        cout << "Rip";
        return 0;
    }

    

    //Starting screen sprites
    Sprite start_s(Assets::start_t1);
    start_s.setScale(800.0f / Assets::start_t1.getSize().x, 600.0f / Assets::start_t1.getSize().y);
    float start_timer = 0.0f;
    int start_frame = 0;

    //Losing screen sprite
    Sprite lose_s(Assets::lose_t);
    lose_s.setScale(800.0f / Assets::lose_t.getSize().x, 600.0f / Assets::lose_t.getSize().y);
    int current_bg_level = 0;

    //Initial back ground setup
    bg_s.setTexture(Assets::bg_t);
    tile_s.setTexture(Assets::tile_t);

    //==================Music Setup======================
    Assets::level_music.setLoop(true);
    Assets::boss_music.setLoop(true);
    while (window.isOpen()){
        window.clear(Color::Black);
        float deltaTime = time.restart().asSeconds();
        //plays animation at 1fps of the start screen
        if (manager.get_start_screen()) {
            start_timer += deltaTime;
            if (start_timer >= 0.5f) {
                start_timer = 0.0f;
                start_frame = 1 - start_frame;//switch b/w img 0 and img 1
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
        Event ev;//event handler
		//Event polling and handling
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
                window.close();

            if (manager.get_start_screen()) {
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Enter) {
                    manager.set_start_screen(false);
                    manager.set_login(true);
                }
            }
            else if (manager.get_login()) {
                bool login = (((ev.type) == (Event::KeyPressed)) && ((ev.key.code) == (Keyboard::Enter)));
                loginScreen.handleInput(ev, window);
                if ((loginScreen.getIsLoggedIn()) || (login)) {
                    string user = loginScreen.getLoggedInUsername();
                        if (!user.empty()) {
                            if (login) {
                                auth.registerUser(user, "pass");
                                if (!auth.loginUser(user, "pass")) {
                                    return 0;
                                }
                            }
                        currentUser = user;
                        manager.set_login(false);
                        manager.set_main_menu(true);
                        int lvl, liv, gems, sc;
                        db.loadProgress(currentUser, lvl, liv, gems, sc);
                        p1.set_lives(liv);
                        p1.set_score(sc);
                        p1.set_gemCount(gems);
                    }
                }
            }
            else if (manager.get_login2()) {
                loginScreen2.handleInput(ev, window);
                if (loginScreen2.getIsLoggedIn()) {
                    string user2 = loginScreen2.getLoggedInUsername();
                    if (!user2.empty()) {
                        currentUser2 = user2;
                        manager.set_login2(false);
                        manager.set_character_select(true);
                        select_screen.setup(2);
                        // load P2 progress
                        int lvl2, liv2, gems2, sc2;
                        db.loadProgress(currentUser2, lvl2, liv2, gems2, sc2);
                        p2.set_lives(liv2);
                        p2.set_score(sc2);
                        p2.set_gemCount(gems2);
                    }
                }
            }
            else if (manager.get_main_menu()) {
                main_menu.handleInput(ev, window);
            if (main_menu.getChoice() == 1) 
                manager.set_main_menu(false);
                if (!main_menu.getIsSinglePlayer()) {
                    manager.set_login2(true);
                }
                else {
                    manager.set_character_select(true);
                    select_screen.setup(1);
                }
                if (main_menu.getChoice() == 2) {  // Continue
                    
                        int lvl, liv, gems, sc;
                        db.loadProgress(currentUser, lvl, liv, gems, sc);
                        if (lvl == 0) {
                            // no save found, do nothing
                        }
                        else {
                            p1.set_lives(liv);
                            p1.set_score(sc);
                            p1.set_gemCount(gems);
                            manager.set_main_menu(false);
                            manager.set_character_select(true);
                            select_screen.setup(1);
                        }
                    
                }
                if (main_menu.getChoice() == 3) {  // Leaderboard
                    db.displayLeaderboard();  // prints to console for now
                    showLeaderboard = true;
                    manager.set_main_menu(false);
                }
                if (main_menu.getChoice() == 4) {  // Exit
                    window.close();
                }
            }

            else if (manager.get_pause())
            {
                pause_menu.handleInput(ev, window);


            }
            else if (manager.get_shop()) {
                shop.handleInput(ev, window, p1);  

                if (!shop.getIsOpen()) {  
                    manager.set_shop(false);
                    manager.set_pause(true);  //back to pause menu
                    pause_menu.open();
                }
            }
            else if (manager.get_character_select()) {
                select_screen.handleInput(ev, window);

                if (select_screen.getSelectionDone()) {
                    if (!p1Selected) {
                        choiceScreen.player1Select(select_screen.getChoice());
                        p1Selected = true;
                        hud = HUD(false);  
                        hud.setup();       
                        if (!main_menu.getIsSinglePlayer()) {
                            select_screen.setup(1);
                            continue;
                        }
                        else {
                            choiceScreen.player2Select(1);
                            choiceScreen.confirmSelection();
                            p1Selected = false;
                            hud = HUD(true);   
                            hud.setup();
                            manager.set_character_select(false);
                            manager.set_play(true);
                            manager.set_next_level(true);
                            Assets::level_music.play();
                        }
                    }
                    else {
                        choiceScreen.player2Select(select_screen.getChoice());
                        choiceScreen.confirmSelection();
                        p1Selected = false;
                        manager.set_character_select(false);
                        manager.set_play(true);
                        manager.set_next_level(true);
                        Assets::level_music.play();
                    }
                }
            }
            else {
                Inputhandle(ev, manager, window, p1, p2, active_projectiles, projectile_count);
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::P) {
                    manager.set_pause(true);
                    manager.set_play(false);
                    pause_menu.open();
                }
            
            }
        }
       
       //HUD update
        hud.update(p1.get_score(), p1.get_lives(), p1.get_gemCount(),
            p2.get_score(), p2.get_lives(), p2.get_gemCount(),
            current_bg_level, 10, "", 0, 100);

        //movement logic in game
        if (!manager.get_login() && !manager.get_login2() && !manager.get_character_select() && !manager.get_pause() && 
            !manager.get_shop() && !manager.get_main_menu() && manager.get_play()) {
            if (Keyboard::isKeyPressed(Keyboard::A)) {
                p_move(p1, -p1.get_speed(), deltaTime, true);
                p1.right_facing = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::D)) {
                p_move(p1, p1.get_speed(), deltaTime, true);
                p1.right_facing = true;
            }

            //chwcks for gameover
            if (p1.getHP() <= 0 && p2.getHP() <= 0) {
                manager.set_play(false);
                manager.set_lose(true);
                gameOverScreen.setData(p1.get_score() + p2.get_score(), current_bg_level);
            }
            if (!main_menu.getIsSinglePlayer())
            {
                if (Keyboard::isKeyPressed(Keyboard::Num4)) {
                    p_move(p2, -p2.get_speed(), deltaTime, true);
                    p2.right_facing = false;
                }
                if (Keyboard::isKeyPressed(Keyboard::Num6)) {
                    p_move(p2, p2.get_speed(), deltaTime, true);
                    p2.right_facing = true;
                }
            }
            //P1 Physics
            Gravity(p1, 980.0f, deltaTime);
            Position_change(p1, true, p1.get_vy(), deltaTime, false);
            //Hitbox update for P1
            FloatRect h1 = p1.get_hitbox();
            h1.left = p1.get_x();
            h1.top = p1.get_y();
            p1.set_hitbox(h1);
            //P2 Physics
            if (!main_menu.getIsSinglePlayer()) {
                Gravity(p2, 980.0f, deltaTime);
                Position_change(p2, true, p2.get_vy(), deltaTime, false);
                //Hitbox update for P2
                FloatRect h2 = p2.get_hitbox();
                h2.left = p2.get_x();
                h2.top = p2.get_y();
                p2.set_hitbox(h2);
            }
            //Player 1 Platform Collision
            p1.set_on_ground(false);
            if (manager.get_current_level() != nullptr) {
                float p1_bottom = p1.get_y() + p1.get_hitbox().height;
                for (int i = 0; i < manager.get_current_level()->num_platforms; i++) {//check each platform
                    platform pt = manager.get_current_level()->platforms[i];//get platform
                    if (p1.get_vy() >= 0 && p1.get_hitbox().intersects(pt.collison)) {//check if player is falling and intersects platform
                        if (p1_bottom - pt.y < 30.0f) {//check if player is close enough to the top of the platform
                            Fix_collision(p1, pt.y);//adjust player position and velocity
                            p1.set_on_ground(true);//set on ground to true
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
            if (!main_menu.getIsSinglePlayer()) {
                p2.set_on_ground(false);
                if (manager.get_current_level() != nullptr) {
                    float p2_bottom = p2.get_y() + p2.get_hitbox().height;
                    for (int i = 0; i < manager.get_current_level()->num_platforms; i++) {//checks each platform
                        platform pt = manager.get_current_level()->platforms[i];//gets the right one
                        if (p2.get_vy() >= 0 && p2.get_hitbox().intersects(pt.collison)) {//checks if the falling player intersects with it
                            if (p2_bottom - pt.y < 30.0f) {//checks if the player is close enough to the top
                                Fix_collision(p2, pt.y);//adjusts player position and velocity
                                p2.set_on_ground(true);//set on ground to true
                                FloatRect h2_new = p2.get_hitbox();//update hitbox after collision fix
                                h2_new.left = p2.get_x();
                                h2_new.top = p2.get_y();
                                p2.set_hitbox(h2_new);
                                break;
                            }
                        }
                    }
                }
            }
            if (p2.get_y() > 500) {//fall out of world fix
                p2.set_y(500);//reset position to ground level
                p2.set_vy(0);
                p2.set_on_ground(true);
            }
            //Enemy Updates
            for (int i = 0; i < enemy_count; i++) {//updates each enemy
                if (active_enemies[i] != nullptr) {//check if the enemy even exists
                    active_enemies[i]->update(deltaTime);//updates that enemy's logic

                    if (active_enemies[i]->hasSpawnRequest && enemy_count < max_enemies) {
                        Enemy* spawnedEnemy = EnemyFactory::e(active_enemies[i]->spawnType, active_enemies[i]->spawnX, active_enemies[i]->spawnY);
                        if (spawnedEnemy != nullptr) {
                            active_enemies[enemy_count++] = spawnedEnemy;
                        }
                        active_enemies[i]->hasSpawnRequest = false;
                    }

                    //Kicking logic
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
                    //removal
                    if (active_enemies[i]->getHP() <= 0) {//if enemy is dead
                        delete active_enemies[i];//free memory
                        for (int j = i; j < enemy_count - 1; j++) {
                            active_enemies[j] = active_enemies[j + 1];//shifts the remaining enemies down in the array
                        }//decrements
                        enemy_count--;
                        i--;
                    }
                }
            }
            //Projectile Updates
            for (int i = 0; i < projectile_count; i++) {
                if (active_projectiles[i] != nullptr) {//check if projectile exists
                    active_projectiles[i]->update(deltaTime);
                    //Check for collisions with enemies
                    for (int j = 0; j < enemy_count; j++) {
                        if (active_enemies[j] != nullptr) {
                            FloatRect ballHitbox = active_projectiles[i]->getHitbox();
                            FloatRect enemyHitbox = active_enemies[j]->getHitbox();
                            if (ballHitbox.intersects(enemyHitbox)) {
                                active_enemies[j]->hit();
                                active_projectiles[i]->setisactive(false);
                                break;
                            }
                        }
                    }
                    if (!active_projectiles[i]->getisactive()) {
                        //remove if out of bounds or inactive
                        delete active_projectiles[i];//free memory
                        for (int j = i; j < projectile_count - 1; j++) {//shift remaining projectiles down in array
                            active_projectiles[j] = active_projectiles[j + 1];
                        }//decrements
                        projectile_count--;
                        i--;
                    }
                }
            }
            //Snowball roll logic
            for (int i = 0; i < enemy_count; i++) {
                if ((active_enemies[i] != nullptr) && (active_enemies[i]->get_rolling())) {
                    FloatRect Hitbox_SnowBall = active_enemies[i]->getHitbox();
                    for (int j = 0; j < enemy_count; j++) {
                        if ((i == j) || (active_enemies[j] == nullptr)) {
                            continue;
                        }
                        FloatRect Hitbox_target = active_enemies[j]->getHitbox();
                        if (Hitbox_SnowBall.intersects(Hitbox_target)) {
                            active_enemies[j]->kill();
                            active_enemies[i]->grow_rolling();
                        }
                    }
                }
            }

            //level clear check
            if (enemy_count == 0 && manager.get_play() && !manager.get_next_level() && !manager.get_boss()) {
                manager.set_play(false);
                manager.set_win(true);
                levelCompleteScreen.setData(p1.get_score() + p2.get_score(), p1.get_gemCount() + p2.get_gemCount());
            }
            //Levelup check
            if (((enemy_count == 0) || (manager.get_next_level())) && (manager.get_play())) {//if all enemies are cleared and still playing
                manager.next_level();
                manager.set_next_level(false);
                current_bg_level++;
                if (current_bg_level > 10) {
                    current_bg_level = 1;//loop back to level 1+ cant really happen since at 10 it ends but why not meri jaan :)
                }
                //new background and tile for the next level
                string new_bg = "SnowBrosAssets/Level" + to_string(current_bg_level) + "/bg.png";
                string new_tile = "SnowBrosAssets/Level" + to_string(current_bg_level) + "/tile.png";
                if (Assets::bg_t.loadFromFile(new_bg)) {
                    bg_s.setTexture(Assets::bg_t, true); // true to reset texture rect
                    bg_s.setScale(800.0f / Assets::bg_t.getSize().x, 600.0f / Assets::bg_t.getSize().y);//rescale bg to fit window
                }
                if (Assets::tile_t.loadFromFile(new_tile)) {//if new tile loads, sets it as the new sprite for tile_s
                    tile_s.setTexture(Assets::tile_t, true); // true to reset texture rect
                }
                //music handling for bosses
                if (manager.get_boss()) {
                    Assets::level_music.stop();
                    Assets::boss_music.play();
                }

                //file read to spawn mobs
                level* current_lvl = manager.get_current_level();
                if ((current_lvl != nullptr) && (current_lvl->num_enemies > 0)) {
                    for (int i = 0; i < current_lvl->num_enemies; i++) {
                        enemy_spawn es = current_lvl->enemies[i];
                        active_enemies[enemy_count++] = EnemyFactory::e(es.type, es.x, es.y);
                    }
                }
            }
        }
        //=======All Draws======
        if (manager.get_start_screen()) {
            window.draw(start_s);
        }
        else if (manager.get_login()) {
            loginScreen.draw(window);
        }
        else if (manager.get_login2()) {
            loginScreen2.draw(window);
        }
        else if (manager.get_main_menu()) {
            main_menu.draw(window);
        }
       
        else if (manager.get_character_select()) {
            select_screen.draw(window);
        }
         else if (manager.get_pause()) {
            pause_menu.draw(window);
            if (pause_menu.getChoice() == 1) {  // Resume
                manager.set_pause(false);
                manager.set_play(true);
                pause_menu.close();
                pause_menu.resetChoice();
            }
            if (pause_menu.getChoice() == 2) {  // shop
                
                manager.set_pause(false);
                manager.set_shop(true);
                shop.opentheShop();
                pause_menu.close();
                pause_menu.resetChoice();
            }
            if (pause_menu.getChoice() == 3) {  // Save
                db.saveProgress(currentUser, current_bg_level,
                    p1.get_lives(), p1.get_gemCount(), p1.get_score());
                db.saveLeaderboard(currentUser, p1.get_score(), current_bg_level);
                if (!main_menu.getIsSinglePlayer()) {
                    db.saveProgress(currentUser2, current_bg_level,
                        p2.get_lives(), p2.get_gemCount(), p2.get_score());
                    db.saveLeaderboard(currentUser2, p2.get_score(), current_bg_level);
                }
                pause_menu.resetChoice();
            }
            if (pause_menu.getChoice() == 4) {
                db.saveProgress(currentUser, current_bg_level,
                    p1.get_lives(), p1.get_gemCount(), p1.get_score());
                manager.set_pause(false);
                manager.set_play(false);
                loginScreen = LoginScreen();
                loginScreen.setup();
                manager.set_login(true);
                p1Selected = false;
                main_menu.resetChoice();
                pause_menu.close();
 
                pause_menu.resetChoice();
                currentUser = "";
            }
            if (pause_menu.getChoice() == 5) {
                db.saveProgress(currentUser, current_bg_level,
                    p1.get_lives(), p1.get_gemCount(), p1.get_score());
                if (!main_menu.getIsSinglePlayer()) {
                    db.saveProgress(currentUser2, current_bg_level,
                        p2.get_lives(), p2.get_gemCount(), p2.get_score());
                }
                manager.set_pause(false);
                manager.set_play(false);
                manager.set_main_menu(true);
                p1Selected = false;
                main_menu.resetChoice();
                pause_menu.close();
                pause_menu.resetChoice();
            }
           
        }
         else if (manager.get_shop())
        {
            shop.draw(window, p1);
        }

       

        else if (manager.get_win()) {
            levelCompleteScreen.draw(window);
            levelCompleteScreen.handleInput(ev, window);
            if (levelCompleteScreen.getChoice() == 1) {//next level
                manager.set_win(false);
                manager.set_play(true);
                manager.set_next_level(true);
            }
        }
        else if (manager.get_lose()) {
            gameOverScreen.draw(window);
            gameOverScreen.handleInput(ev, window);
            if (gameOverScreen.getChoice() == 1) {//Retry
                manager.set_lose(false);
                manager.set_play(true);
            }
        }
        else if (manager.get_shop()) {
            shop.draw(window,p1);
        }
        else {
            window.draw(bg_s);
            //Drawing tiles for platforms   
            if (manager.get_current_level() != nullptr) {
                for (int i = 0; i < manager.get_current_level()->num_platforms; i++) {
                    platform& plt = manager.get_current_level()->platforms[i];
                    tile_s.setScale(static_cast<float>(plt.w) /((Assets::tile_t.getSize().x)),  static_cast<float>(plt.h) / Assets::tile_t.getSize().y);
                    tile_s.setPosition(plt.x, plt.y);
                    window.draw(tile_s);
                }
            }
            //P1 and P2 drawn after the bg and platforms so they appear in front, with their updated positions
            update_animations(p1, deltaTime, !p1.right_facing, p1.right_facing);//update player animations based on movement
            window.draw(p1.get_sprite()); //draw player 1
            if (!main_menu.getIsSinglePlayer()) {
                update_animations(p2, deltaTime, !p2.right_facing, p2.right_facing);
                window.draw(p2.get_sprite());//draw player 2
            }
            //Draw Enemies
            for (int i = 0; i < enemy_count; i++) {
                if (active_enemies[i] != nullptr) {
                    active_enemies[i]->draw(window);
                }
            }
            //Draw Projectiles
            for (int i = 0; i < projectile_count; i++) {
                if (active_projectiles[i] != nullptr) {
                    active_projectiles[i]->draw(window);
                }
            }
            //Debug view to show hitboxes and platforms
            if (manager.get_current_level() != nullptr) {
                debug_view(manager, p1.get_hitbox(), manager.get_current_level()->platforms, manager.get_current_level()->num_platforms, window);
                debug_view(manager, p2.get_hitbox(), manager.get_current_level()->platforms, 0, window);
                if (manager.get_debug()) {
                    for (int i = 0; i < enemy_count; i++) {
                        if (active_enemies[i] != nullptr) {
                            draw_debug_box(window, active_enemies[i]->getHitbox(), Color::Red);
                        }
                    }
                    for (int i = 0; i < projectile_count; i++) {
                        if (active_projectiles[i] != nullptr) {
                            draw_debug_box(window, active_projectiles[i]->getHitbox(), Color::Yellow);
                        }
                    }
                }
            }
            //lose screen
            if (manager.get_lose()) {
                window.draw(lose_s);
            }
        }
        
       //HUD drawn
       if (manager.get_play() || manager.get_pause() || manager.get_shop()) {
           hud.draw(window);
       }
       window.display();
    }
    return 0;
}
