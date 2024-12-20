#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "game_objects.h"

//SFML files
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
//SFML namespace
using namespace sf;

class level_manager {
private:
    //Current level pointer
    vector<game_object*>* current_level = nullptr;
    //screen size is 1400 by 800 (1400 wide, 800 tall). i recommend using desmos or geogebra to visualize how you want a level to look and then copy down the cords into the vector
    //Level 1 vector
    //IMPORTANT: Player should always be the first element in a level
    //travel distance = (platform it is on length - 50)/2, has to be spawned on the middle 
    vector<game_object*> level_1 = {

        new player(10, 650, 50, 50, "Player", Color::Transparent),
        new end_goal(1300, 600, 50, 50, "End Goal", Color::Transparent, 2),
        new game_object(0, 750, 250, 50, "Platform", Color::Black),
        new game_object(400, 650, 450, 150, "Platform", Color::Black),
        new game_object(1000, 650, 400, 150, "Platform", Color::Black),
        new ground_enemy(600, 400, 50, 50, "Enemy", Color::Transparent, 50, 200, false),


        

       
    };
    //Level 2 vector
    vector<game_object*> level_2 = {
        new player(320, 50, 50, 50, "Player", Color::Transparent),
        new game_object(320, 610, 400, 100, "Platform", Color::Black),
        new game_object(500, 610, 400, 100, "Platform", Color::Black),
        new ground_enemy(650, 400, 50, 50, "Enemy", Color::Transparent, 50, 200, false),
        new game_object(900, 410, 300, 100, "Platform", Color::Black),
         new end_goal(1100, 360, 50, 50, "End Goal", Color::Transparent, 3),
    };
    vector<game_object*> level_3 = {
       new player(10, 650, 50, 50, "Player", Color::Transparent),
        new game_object(0,750,250,50,"Platform",Color::Transparent),
        new game_object(350,650,250,50,"Platform",Color::Transparent),
        new ground_enemy(450, 600, 50, 50, "Enemy", Color::Transparent, 50, 100, false),
        new game_object(650,250,100,700,"Platform",Color::Transparent),
        new game_object(0,500,250,50,"Platform",Color::Transparent),
        new game_object(350,350,150,50,"Platform",Color::Transparent),
        new game_object(550,200,300,50,"Platform",Color::Transparent),
        new flying_enemy(675,100,50,50,"Enemy",Color::Transparent,150,200, false),
        new game_object(1000,500,300,50,"Platform",Color::Transparent),
        new end_goal(1150,450,50,50,"End Goal", Color::Transparent, 5),
    };
    //Level 4 vector
    vector<game_object*> level_4 = {
          new player(220, 50, 50, 50, "Player", Color::Transparent),
        new game_object(120, 110, 300, 100, "Platform", Color::Black),
        //new game_object(500, 710, 400, 100, "Platform", Color::Black),

        new game_object(700, -100, 100, 650, "Platform", Color::Black),
        new game_object(750, 650, 100, 400, "Platform", Color::Black),
         new game_object(850, 650, 300, 100, "Platform", Color::Black),
        new game_object(420, 110, 100, 700, "Platform", Color::Black),
         new flying_enemy(575, 250, 50, 50, "Enemy", Color::Transparent, 50, 250, false),
         new flying_enemy(550, 150, 50, 50, "Enemy", Color::Transparent, 50, 250, false),
         new flying_enemy(600, 350, 50, 50, "Enemy", Color::Transparent, 50, 250, false),
         new flying_enemy(625, 450, 50, 50, "Enemy", Color::Transparent, 50, 250, false),
       new flying_enemy(625, 650, 50, 50, "Enemy", Color::Transparent, 50, 250, false),
       new flying_enemy(600, 750, 50, 50, "Enemy", Color::Transparent, 50, 250, false),
       new flying_enemy(800, 500, 50, 50, "Enemy", Color::Transparent, 50, 150, false),
       new end_goal(950, 280, 50, 50, "End Goal", Color::Transparent, 4),
    };
    //Level 5 vector
    vector<game_object*> level_5 = {
        new player(10, 650, 50, 50, "Player", Color::Transparent),
        new game_object(0,750,250,50,"Platform",Color::Transparent),
        new game_object(350,650,50,50,"Platform",Color::Transparent),
        new game_object(550,650,50,50,"Platform",Color::Transparent),
        new game_object(750,650,50,50,"Platform",Color::Transparent),
        new game_object(950,650,50,50,"Platform",Color::Transparent),
        new game_object(1150,650,50,50,"Platform",Color::Transparent),
        new flying_enemy(750,550,50,50,"Enemy",Color::Transparent, 150, 200, false),
        new end_goal(1150,600,50,50,"End Goal", Color::Transparent, 6),
    };
    vector<game_object*> level_6 = {
          

         new player(10, 650, 50, 50, "Player", Color::Transparent),
        new end_goal(1300, 600, 50, 50, "End Goal", Color::Transparent, 7),

        //starting platform
        new game_object(0, 750, 250, 50, "Platform", Color::Transparent),
        //platform above the starting platform
        new game_object(0, 550, 250, 50, "Platform", Color::Transparent),
        
        new game_object(400, 650, 150, 150, "Platform", Color::Transparent),
        new flying_enemy(380, 400, 50, 50, "Enemy", Color::Transparent, -50, 400, false),
        new game_object(500, 300, 50, 450, "Platform", Color::Transparent),

        new flying_enemy(550, 300, 50, 50, "Enemy", Color::Transparent, 100, 200, false),
        new flying_enemy(350, 200, 50, 50, "Enemy", Color::Transparent, 50, 200, false),
        new flying_enemy(750, 350, 50, 50, "Enemy", Color::Transparent, 150, 200, false),

        new game_object(1000, 650, 400, 150, "Platform", Color::Transparent),
        new ground_enemy(450, 400, 50, 50, "Enemy", Color::Transparent, 50, 50, true),
    };
    //Level 7 vector
    vector<game_object*> level_7 = {
        new player(10, 650, 50, 50, "Player", Color::Transparent),
        new end_goal(1300, 600, 50, 50, "End Goal", Color::Transparent, 8),
        new game_object(0, 750, 250, 50, "Platform", Color::Transparent),
        new game_object(400, 650, 450, 150, "Platform", Color::Transparent),
        new game_object(1000, 650, 400, 150, "Platform", Color::Transparent),
        new speed_pickup(600, 600, 50, 50, "Pickup", Color::Transparent, 1000),
        new ground_enemy(600, 400, 50, 50, "Enemy", Color::Transparent, -50, 200, true),
    };
    vector<game_object*> level_8 = {
        new player(10, 650, 50, 50, "Player", Color::Transparent),
        new end_goal(1300, 600, 50, 50, "End Goal", Color::Transparent, 9),
        new game_object(0, 750, 250, 50, "Platform", Color::Transparent),
        new game_object(400, 650, 450, 150, "Platform", Color::Transparent),
        new game_object(1000, 650, 400, 150, "Platform", Color::Transparent),
        new ground_enemy(600, 400, 50, 50, "Enemy", Color::Transparent, 50, 200, false),
    };
    vector<game_object*> level_9 = {
       new player(150, 50, 50, 50, "Player", Color::Transparent),
        new game_object(100, 310, 200, 500, "Platform", Color::Black),
        new game_object(600, 610, 400, 100, "Platform", Color::Black),
         new game_object(375, 0, 100, 500, "Platform", Color::Black),
         new flying_enemy(600, 730, 50, 50, "Enemy", Color::Transparent, -50, 250, false),

         new flying_enemy(550, 200, 50, 50, "Enemy", Color::Transparent, 50, 250, false),
         new flying_enemy(500, 400, 50, 50, "Enemy", Color::Transparent, 50, 250, false),
         new flying_enemy(720, 500, 50, 50, "Enemy", Color::Transparent, 50, 250, false),
         new flying_enemy(800, 300, 50, 50, "Enemy", Color::Transparent, -50, 250, false),
         new end_goal(900, 60, 50, 50, "End Goal", Color::Transparent, 10),
         new game_object(875, 100, 100, 100, "Platform", Color::Black),
    };
    vector<game_object*> level_10 = {
        new player(25, 0, 50, 50, "Player", Color::Transparent),
        new game_object(0, 150, 100, 100, "Platform", Color::Transparent),

        new flying_enemy(325, 225, 50, 50, "Enemy", Color::Transparent, -300, 300, false),
        new game_object(400, 0, 100, 300, "Platform", Color::Transparent),
       new game_object(300, 300, 50, 50, "Platform", Color::Transparent),
       new game_object(10, 500, 100, 50, "Platform", Color::Transparent),
       new game_object(10, 500, 20, 250, "Platform", Color::Transparent),
       new game_object(10, 750, 70, 50, "Platform", Color::Transparent),
       new game_object(200, 580, 50, 50, "Platform", Color::Transparent),
       new speed_pickup(25, 700, 50, 50, "Pickup", Color::Transparent, 2000),
       new jump_pad(700, 750, 50, 50, "Jump Pad", Color::Transparent, 300),
       new game_object(800, 550, 50, 400, "Platform", Color::Transparent),
       new health_pickup(800, 500, 50, 50, "Pickup", Color::Transparent),
       new jump_pad(1100, 700, 100, 100, "Jump Pad", Color::Transparent, 500),
       new flying_enemy(1125, 500, 50, 50, "Enemy", Color::Transparent, -100, 225, false),
       new flying_enemy(1125, 350, 50, 50, "Enemy", Color::Transparent, -200, 225, false),
       new flying_enemy(1125, 200, 50, 50, "Enemy", Color::Transparent, -300, 225, false),
       new end_goal(1100, 100, 50, 50, "End Goal", Color::Transparent, 11),

    };
    vector<game_object*> end_screen = {
        new player(10, 650, 50, 50, "Player", Color::Transparent),
        new game_object(0,750,1400,50,"Platform",Color::Transparent),
        new game_object(300,200,150,50,"Platform",Color::Transparent),
        new game_object(300,250,50,150,"Platform",Color::Transparent),
        new game_object(350,300,50,50,"Platform",Color::Transparent),
        new game_object(300,400,150,50,"Platform",Color::Transparent),
        new game_object(500,200,50,250,"Platform",Color::Transparent),
        new game_object(550,250,50,50,"Platform",Color::Transparent),
        new game_object(600,300,50,50,"Platform",Color::Transparent),
        new game_object(650,350,50,50,"Platform",Color::Transparent),
        new game_object(700,200,50,250,"Platform",Color::Transparent),
        new game_object(800,200,50,250,"Platform",Color::Transparent),
        new game_object(850,200,50,50,"Platform",Color::Transparent),
        new game_object(900,250,50,150,"Platform",Color::Transparent),
        new game_object(850,400,50,50,"Platform",Color::Transparent),
    };


public:
    //Constructor (default)
    level_manager() = default;

    //Run update function for all objects in the current level
    void update_all_objects(Time delta, bool left_input, bool right_input, bool up_input, bool down_input) {
        if (!current_level) return; // No level set

        for (auto obj : *current_level) {
            if (player* plyr = dynamic_cast<player*>(obj) ) {
                // Update player movement
                plyr->update_movement(delta.asMicroseconds() / 1'000'000.0f, left_input, right_input, up_input, down_input);
                
                
            }
            else if (ground_enemy* enmy = dynamic_cast<ground_enemy*>(obj)) {
                enmy->update_movement(delta.asMicroseconds() / 1'000'000.0f);
                
            }
            else if (flying_enemy* fly_enmy = dynamic_cast<flying_enemy*>(obj)) {
                fly_enmy->update_movement(delta.asMicroseconds() / 1'000'000.0f);

            }
            
            obj->update(delta.asMicroseconds() / 1'000'000.0f);
            
            
        }
        
    }

    //Detects collisions between objects every frame
    void detect_collisions(Time delta) {
        if (!current_level) return; // No level set

        for (size_t i = 0; i < current_level->size(); i++) {
            //Check if our current selection is the player
            if (player* plyr = dynamic_cast<player*>((*current_level)[i])) {
                // Reset floor count
                plyr->reset_collision_counts();
                

                // Check collisions with every other object
                for (size_t j = 0; j < current_level->size(); j++) {
                    
                    //Make sure we aren't currently trying to check the player with itself
                    if (i != j) {
                        //Check if the object's shape is intersecting the player's shape
                        if (plyr->get_shape().getGlobalBounds().intersects((*current_level)[j]->get_shape().getGlobalBounds())) {
                            //Call the on_collision function
                            
                            if (plyr->on_collision((*current_level)[j]->get_type(), (*current_level)[j]->get_shape().getPosition(), (*current_level)[j]->get_shape().getSize()) == 0) {
                                //sounds[2].play();
                                reset_level();
                            }
                            else if (plyr->on_collision((*current_level)[j]->get_type(), (*current_level)[j]->get_shape().getPosition(), (*current_level)[j]->get_shape().getSize()) == 2) {
                                if (jump_pad* jmp_pd = dynamic_cast<jump_pad*>((*current_level)[j])) {

                                    plyr->set_jump_force(plyr->get_default_jump_force() - jmp_pd->get_bounce());
                                   
                                }
                            }
                            if (health_pickup* hlth_pickup = dynamic_cast<health_pickup*>((*current_level)[j])) {
                                plyr->add_health(1);
                                hlth_pickup->set_position(2000, 2000);
                            }
                            else if (speed_pickup* spd_pickup = dynamic_cast<speed_pickup*>((*current_level)[j])) {
                                plyr->boost_move_speed();
                                spd_pickup->set_position(2000, 2000);
                                int duration = spd_pickup->get_duration();
                                
                                plyr->set_power_up_duration(duration);
                                
                            }
                            //Check if object is the end goal
                            if (end_goal* goal = dynamic_cast<end_goal*>((*current_level)[j])) {
                                set_current_level(goal->get_level_to_load());
                            }
                            
                        }
                    }
                }

                //Check if the player is currently out of bounds
                if (plyr->get_y_position() > 1000) {
                    
                    reset_level();
                }
            }
            else if (ground_enemy * enmy = dynamic_cast<ground_enemy*>((*current_level)[i])) {
                enmy->reset_collision_counts();

                for (size_t j = 0; j < current_level->size(); j++) {
                    //Make sure we aren't currently trying to check the enemy with itself
                    if (i != j) {
                        //Check if the object's shape is intersecting the enemies shape
                        if (enmy->get_shape().getGlobalBounds().intersects((*current_level)[j]->get_shape().getGlobalBounds())) {
                            //Call the on_collision function


                            if (enmy->on_collision((*current_level)[j]->get_type(), (*current_level)[j]->get_shape().getPosition(), (*current_level)[j]->get_shape().getSize())) {
                                reset_level();
                            }
                            
                            
                            
                        }
                    }
                }
                /*
                * //i had to comment this out because when the player would kill an enemy, then die the killed enemies would not respawn because they were removed
                //Check if the enemy is out of bounds and remove them from the vector
                if (enmy->get_y_position() > 1000) {
                   //remove the j-ith index of the vector
                    current_level->erase(current_level->begin() + i);

                    // 
                    i--;
                }
                */
            }
            else if (flying_enemy* fly_enmy = dynamic_cast<flying_enemy*>((*current_level)[i])) {
                

                for (size_t j = 0; j < current_level->size(); j++) {
                    //Make sure we aren't currently trying to check the enemy with itself
                    if (i != j) {
                        //Check if the object's shape is intersecting the enemies shape
                        if (fly_enmy->get_shape().getGlobalBounds().intersects((*current_level)[j]->get_shape().getGlobalBounds())) {
                            //Call the on_collision function


                            if (fly_enmy->on_collision((*current_level)[j]->get_type(), (*current_level)[j]->get_shape().getPosition(), (*current_level)[j]->get_shape().getSize())) {
                                reset_level();
                            }

  

                        }
                    }
                }
                /*
                * //i had to comment this out because when the player would kill an enemy, then die the killed enemies would not respawn becase they were removed
                //Check if the enemy is out of bounds and remove them from the vector
                if (fly_enmy->get_y_position() > 1000) {
                    //remove the j-ith index of the vector
                    current_level->erase(current_level->begin() + i);

                    // 
                    i--;
                }
                */
            }

        }
    }

    //Reset the positions of all objects in the level
    void reset_level() {
        for (size_t i = 0; i < current_level->size(); i++) {
            (*current_level)[i]->reset_position();
            //resets the direction an enemy is traveling 
            if (enemy* enmy = dynamic_cast<enemy*>((*current_level)[i]) ) {
                 enmy->reset_move_speed();
            }
            else if (player* plyr = dynamic_cast<player*>((*current_level)[i])) {
                plyr->loose_heart();
                plyr->normal_move_speed();
            }
        }
    }

    //Delete all of the levels. Called when the game is ended
    void delete_levels() {
        level_1.clear();
        level_2.clear();
        level_3.clear();
        level_4.clear();
        level_5.clear();
        level_6.clear();
        level_7.clear();
        level_8.clear();
        level_9.clear();
        level_10.clear();
        end_screen.clear();
    }

    //Getters & Setters
    //Getters
    int get_current_level_size() {
        return (int)level_1.size();
    }
    int get_current_level_size() const {
        return current_level ? (int)current_level->size() : 0;
    }
    vector<game_object*>* get_current_level() const {
        return current_level;
    }
    int get_current_level_id() {
        if (current_level == &level_1) {
            return 1;
        }
        else if (current_level == &level_2) {
            return 2;
        }
        else if (current_level == &level_3) {
            return 3;
        }
        else if (current_level == &level_4) {
            return 4;
        }
        else if (current_level == &level_5) {
            return 5;
        }
        else if (current_level == &level_6) {
            return 6;
        }
        else if (current_level == &level_7) {
            return 7;
        }
        else if (current_level == &level_8) {
            return 8;
        }
        else if (current_level == &level_9) {
            return 9;
        }
        else if (current_level == &level_10) {
            return 10;
        }
        return 1;
    }
    //Setters
    void set_current_level(int level_id) {
        switch (level_id) {
        case 1:
            current_level = &level_1;
            break;
        case 2:
            current_level = &level_2;
            break;
        case 3:
            current_level = &level_3;
            break;
        case 4:
            current_level = &level_4;
            break;
        case 5:
            current_level = &level_5;
            break;
        case 6:
            current_level = &level_6;
            break;
        case 7:
            current_level = &level_7;
            break;
        case 8:
            current_level = &level_8;
            break;
        case 9:
            current_level = &level_9;
            break;
        case 10:
            current_level = &level_10;
            break;
        case 11:
            current_level = &end_screen;
            break;

        default:
            cout << "Invalid Level ID: setting to 1 " << endl;
            current_level = &level_1;
            break;
        }
    }
};