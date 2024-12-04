#pragma once
#include <iostream>
#include <string>
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
    int* current_level_size = nullptr;
    game_object*** current_level_array = nullptr;

    //Level 1 array
    int level_1_size = 2;
    //IMPORTANT: Player should always be the first element in a level!
    game_object** level_1 = new game_object * [level_1_size] {
        new player(320, 50, 50, 50, "Player", Color::Blue),
        new game_object(320, 610, 400, 100, "Platform", Color::Black)
    };

public:
    //Constructor (default)
	level_manager() = default;

    //Run update function for all objects in the current level
    void update_all_objects(Time delta, bool left_input, bool right_input, bool up_input) {
        for (int i = 0; i < *current_level_size; i++) {
            //Check if current object is player
            if (player* plyr = dynamic_cast<player*>(current_level_array[0][i]))
                //Call update movement function on player
                plyr->update_movement(delta.asMicroseconds() / static_cast<float>(1000000), left_input, right_input, up_input);

            //Call update function; convert microseconds to seconds
            current_level_array[0][i]->update(delta.asMicroseconds() / static_cast<float>(1000000));
        }
    }

    //Detects collisions between objects every frame
    void detect_collisions() {
        for (int i = 0; i < *current_level_size; i++) {
            //Check for collisions with player
            if (player* plyr = dynamic_cast<player*>(current_level_array[0][i])) {
                //(This loop assumes the player is always the first element of a level)
                plyr->reset_floor_count();
                for (int j = 1; j < *current_level_size; j++) {
                    if (plyr->get_shape().getGlobalBounds().intersects(current_level_array[0][j]->get_shape().getGlobalBounds())) {
                        //Call the on_collision function
                        plyr->on_collision(current_level_array[0][j]->get_type());
                    }
                }
            }
            //TODO: Check for collisions with enemies
        }
    }

    //Delete all of the levels. Called when the game is ended
    void delete_levels() {
        //Delete level arrays
        for (int i = 0; i < level_1_size; i++) {
            delete level_1[i];
        }
        delete[] level_1;
    }

    //Getters & Setters (Does not include level arrays and sizes, those should never be changed at runtime.)
    //Getters
    int get_current_level_size() {
        return *current_level_size;
    }
    game_object*** get_current_level_array() {
        return current_level_array;
    }
    //Setters
    void set_current_level(int level_id) {
        switch (level_id) {
        case 1:
            current_level_size = &level_1_size;
            current_level_array = &level_1;
            break;
        default:
            cout << "Invalid Level ID: " << level_id << endl;
            break;
        }
    }
};