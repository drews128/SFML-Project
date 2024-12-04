#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "game_objects.h"

#include <vector>
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

    //Level 1 array
    
    //IMPORTANT: Player should always be the first element in a level!
    
    vector<game_object*> level_1 = {
        new player(320, 50, 50, 50, "Player", Color::Blue),
        new game_object(320, 610, 400, 100, "Platform", Color::Black)
    };
    int level_1_size = level_1.size();

  

public:
    //Constructor (default)
	level_manager() = default;

    //Run update function for all objects in the current level
    void update_all_objects(Time delta, bool left_input, bool right_input, bool up_input) {
        if (!current_level) return; // No level set

        for (auto obj : *current_level) {
            if (player* plyr = dynamic_cast<player*>(obj)) {
                // Update player movement
                plyr->update_movement(delta.asMicroseconds() / 1000000.0, left_input, right_input, up_input);
            }

            // Update the object
            obj->update(delta.asMicroseconds() / 1'000'000.0f);
        }
    }

    //Detects collisions between objects every frame
    void detect_collisions() {
        if (!current_level) return; // No level set

        for (size_t i = 0; i < current_level->size(); i++) {
            //Check for collisions with player
            if (player* plyr = dynamic_cast<player*>((*current_level)[i])) {
                // Reset floor count
                //(This loop assumes the player is always the first element of a level)
                plyr->reset_floor_count();

                // Check collisions with other objects
                for (size_t j = 0; j < current_level->size(); j++) {
                    if (i != j && plyr->get_shape().getGlobalBounds().intersects((*current_level)[j]->get_shape().getGlobalBounds())) {
                        //Call the on_collision function
                        plyr->on_collision((*current_level)[j]->get_type());
                    }
                }
            }
            //TODO: Check for collisions with enemies
        }
    }

    //Delete all of the levels. Called when the game is ended
    void delete_levels() {
        // Delete objects in level_1
        for (auto obj : level_1) {
            delete obj;
        }
        level_1.clear();
    }
    
    //Getters & Setters (Does not include level arrays and sizes, those should never be changed at runtime.)
    //Getters
    int get_current_level_size() {
        return level_1.size();
    }
    
    int get_current_level_size() const {
        return current_level ? current_level->size() : 0;
    }

    vector<game_object*>* get_current_level() const {
        return current_level;
    }

    //Setters
    void set_current_level(int level_id) {
        switch (level_id) {
        case 1:
            current_level = &level_1;
            break;
        default:
            cout << "Invalid Level ID: " << level_id << endl;
            current_level = nullptr;
            break;
        }
    }
};