#pragma once
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
    int* current_level_size;
    game_object*** current_level_array;

    //Level 1 array
    int level_1_size = 2;
    game_object** level_1 = new game_object * [level_1_size] {
        new player(320, 50, 50, 50, "Player", Color::Blue),
        new game_object(320, 610, 400, 100, "Platform", Color::Black)
    };
public:
    //Constructor (default)
	level_manager() = default;


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
    int* get_current_level_size_ptr() {
        return current_level_size;
    }
    game_object*** get_current_level_array_ptr() {
        return current_level_array;
    }
    //Setters
    void set_current_level_size_ptr(int &level_size) {
        current_level_size = &level_size;
    }
    void set_current_level_array_ptr(game_object** &level) {
        current_level_array = &level;
    }
};