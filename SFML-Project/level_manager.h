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

    //Level 1 vector
    //IMPORTANT: Player should always be the first element in a level
    //travel distance = (platform it is on length - 50)/2, has to be spawned on the middle 
    vector<game_object*> level_1 = {
       new player(10, 650, 50, 50, "Player", Color::Transparent),
        new end_goal(1300, 600, 50, 50, "End Goal", Color::Transparent, 2),
        new game_object(0, 750, 250, 50, "Platform", Color::Black),
        new game_object(400, 650, 450, 150, "Platform", Color::Black),
        new game_object(1000, 650, 400, 150, "Platform", Color::Black),
        new ground_enemy(600, 400, 50, 50, "Enemy", Color::Transparent, 50, 200),
         

        
    };
    //Level 2 vector
    vector<game_object*> level_2 = {
        
        

        new player(320, 50, 50, 50, "Player", Color::Transparent),
        new game_object(320, 610, 400, 100, "Platform", Color::Black),
        new game_object(500, 610, 400, 100, "Platform", Color::Black),
        new ground_enemy(650, 400, 50, 50, "Enemy", Color::Transparent, 50, 200),
        new game_object(900, 410, 300, 100, "Platform", Color::Black),
         new end_goal(1100, 360, 50, 50, "End Goal", Color::Transparent, 3),
    };
    vector<game_object*> level_3 = {
        
        

        

    };
    vector<game_object*> level_4 = {
        new player(320, 50, 50, 50, "Player", Color::Transparent),
        new game_object(320, 610, 400, 100, "Platform", Color::Black),
        new game_object(500, 610, 400, 100, "Platform", Color::Black)
    };

public:
    //Constructor (default)
    level_manager() = default;

    //Run update function for all objects in the current level
    void update_all_objects(Time delta, bool left_input, bool right_input, bool up_input) {
        if (!current_level) return; // No level set

        for (auto obj : *current_level) {
            if (player* plyr = dynamic_cast<player*>(obj) ) {
                // Update player movement
                plyr->update_movement(delta.asMicroseconds() / 1'000'000.0f, left_input, right_input, up_input);
                
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
    void detect_collisions() {
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
                            
                            if (plyr->on_collision((*current_level)[j]->get_type(), (*current_level)[j]->get_shape().getPosition(), (*current_level)[j]->get_shape().getSize())) {
                                //sounds[2].play();
                                reset_level();
                            }

                            //Check if object is the end goal
                            if (end_goal* goal = dynamic_cast<end_goal*>((*current_level)[j]))
                                set_current_level(goal->get_level_to_load());
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
        }
    }

    //Delete all of the levels. Called when the game is ended
    void delete_levels() {
        level_1.clear();
        level_2.clear();
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
        default:
            cout << "Invalid Level ID: setting to 1 " << endl;
            current_level = nullptr;
            set_current_level(1);
            break;
        }
    }
};