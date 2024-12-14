#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include <sstream>


using namespace std;

//Our files
#include "game_objects.h"
#include "level_manager.h"

//SFML files
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <SFML/Audio.hpp> 
#include <SFML/System/Clock.hpp> 

//SFML namespace
using namespace sf;

//file out function
void saveData(string player_name,int levelHere, int timeOn) {
    string path = "playerStats.txt";
    ofstream writer;
    writer.open(path);
    if(writer.is_open())
    {
       
        writer << player_name << "," << levelHere << "," << timeOn;
                    
    }
    else
    {
        cout << "error reading from file" << endl;
    }

}

void delete_save() {
    string path = "playerStats.txt";
    string name , line;
    int level, seconds;
    string level_string, seconds_string;
    ifstream reader; // Open file in truncate mode
    reader.open(path);
    if (reader.is_open()) {
        while (getline(reader, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, level_string, ',');
            stringstream level_stream(level_string);
            level_stream >> level;
            getline(ss, seconds_string, ',');
            stringstream seconds_stream(seconds_string);
            seconds_stream >> seconds;
            reader.close();
        }
    }
    else {
        cout << "Could not find player in file." << endl;
    }
    ofstream writer;
    writer.open(path);
    if (writer.is_open()) {
        writer << name << ',' << 1  << ',' << seconds;
    }
}


int main()
{
    //Variables
    string player_name;
    int user_selection;
    //Player input variables
    bool is_left_pressed = false;
    bool is_right_pressed = false;
    bool is_jump_pressed = false;
    //file variables
    string userOn;
    int levelOn, timeOn;






    // get data from file



    string path = "playerStats.txt";
    ifstream reader;
    reader.open(path);
    if (reader.is_open())
    {

        string name_s, level_i, time_i;
        double level, time;

        getline(reader, name_s, ',');
        getline(reader, level_i, ',');
        try {

            level = stoi(level_i);

        }
        catch (const out_of_range&) {
            level = 1;
            cout << "out of range error reverting to 0" << endl;
        }
        catch (const invalid_argument& e) {
            level = 1;
            cout << "out of range error reverting to 0" << endl;
        }


        getline(reader, time_i);
        try {

            time = stoi(time_i);
            if (time < 0)
            {
                time = 0; cout << "reverting time to 0" << endl;
            }
        }
        catch (const out_of_range&) {
            time = 0;
            cout << "overflow error reverting to 0" << endl;
        }



        userOn = name_s;
        levelOn = level;
        timeOn = time;
    }
    else {
        cout << "failed to read from file" << endl;
    }
    reader.close();
    //cout << userOn<<" "<< levelOn<<" " << timeOn << endl; //debug



        //SOUND

    vector<string> audioFiles = {
       "jump.wav",   //jump                          0    keycodes for calling sound
       "pop.wav",  //complete level                  1
       "explode.wav", //death                        2
       "click.wav",  //click                         3
       "notify.wav", //notification ping             4
       "background.wav"//background music            5
    };
    vector<SoundBuffer> soundBuffers(audioFiles.size()); //storing sound buffers
    vector<Sound> sounds(audioFiles.size());

    //creating loop to set each sound to each buffer
    for (int i = 0; i < audioFiles.size(); ++i) {
        if (!soundBuffers[i].loadFromFile(audioFiles[i])) {
            cout << "Error loading sound file: " << audioFiles[i] << endl;
            return -1;
        }
        sounds[i].setBuffer(soundBuffers[i]);
    }

    sounds[5].setPitch(0.75f); //speed modifier and pitch
    sounds[5].setLoop(true); //loops forever
    sounds[5].setVolume(90.0f); //100 is default and max
    sounds[5].play();

    //Tracking time

    Clock clock;


    Time time1 = clock.getElapsedTime();
    Time time2 = clock.restart();


    int hours = timeOn / 3600;
    int smallMinutes = timeOn / 60;
    int smallSeconds = timeOn;
    while (smallMinutes >= 60)
    {
        smallMinutes -= 60;
    }
    while (smallSeconds > 60)
    {
        smallSeconds -= 60;
    }





    //Level manager
    level_manager levels = level_manager();




    //Inital message
    cout << "Welcome to SFML.SLIME!" << endl;
    //New game or continue
    cout << "1. Start New Game" << endl << "2. Continue From Existing Save File" << endl;
    //Get user selection
    cin >> user_selection;
    switch (user_selection) {
    case 1:
        //New game
        cout << endl << "Enter Your Name:" << endl;
        cin >> player_name;



        levels.set_current_level(1);

        break;
    case 2:




        player_name = userOn;
        //     cout << timeOn<<endl<<" h "<<hours << " m " << smallMinutes << " s "  <<smallSeconds<<endl;

         //Code for testing only, should be setting it to whatever the saved level id is
        levels.set_current_level(levelOn);
        cout << "Welcome back " << player_name << "!" << endl;
        cout << "Current Playtime " << hours << ":" << smallMinutes << ":" << smallSeconds << endl;


        break;
    default:

        cout << endl << "Invalid input!" << endl;
        return -1;
        break;
    }

    //Some of the following code is based on the offical SFML documentation (https://www.sfml-dev.org/documentation/2.6.2/)
    //Create window with SFML
    RenderWindow window(VideoMode(1400, 800), "Game Title", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60); //Set the framerate limit to 60fps
    //SFML input detection
    Event input_event;
    //Clock that records the time between each frame
    Clock delta_clock;
    //Time between each frame
    //IMPORTANT: Make sure to mutliply any movement by delta so that it is frame independant!
    Time delta;









    //Main game loop -- exits when the window is closed
    while (window.isOpen()) {
        //reset player forced jump if not on jump pad, otherwise force a jump
        game_object* firstObject = levels.get_current_level()->at(0);
        if (player* plyr = dynamic_cast<player*>(firstObject)) {
            
            if (!plyr->get_force_bounce()) {
                is_jump_pressed = false;
            }
            else {
                is_jump_pressed = true;
            }
            if (plyr->get_health() <= 0) {
                window.close();
                delete_save();
                cout << "GAME OVER" << endl;
            }
        }
        
        
        //Detect user inputs
        while (window.pollEvent(input_event)) {
            
            //Check if inputs pressed down
            if (input_event.type == Event::KeyPressed) {
                //Left
                if (input_event.key.code == Keyboard::A || input_event.key.code == Keyboard::Left) {
                    is_left_pressed = true;

                }
                //Right
                if (input_event.key.code == Keyboard::D || input_event.key.code == Keyboard::Right) {
                    is_right_pressed = true;
                }
                //Jump
                if (input_event.key.code == Keyboard::W || input_event.key.code == Keyboard::Space || input_event.key.code == Keyboard::Up) {
                    is_jump_pressed = true;

                    sounds[0].play(); //can be pressed forever


                }
            }
            //Check if inputs are released 
            else if (input_event.type == Event::KeyReleased) {
                
                //Left
                if (input_event.key.code == Keyboard::A || input_event.key.code == Keyboard::Left) {
                    is_left_pressed = false;
                }
                //Right
                if (input_event.key.code == Keyboard::D || input_event.key.code == Keyboard::Right) {
                    is_right_pressed = false;
                }
                //Jump
                if (input_event.key.code == Keyboard::W || input_event.key.code == Keyboard::Space || input_event.key.code == Keyboard::Up) {
                    if (levels.get_current_level()->at(0)) {
                        
                        //reference the first element in the condition, which is always the player

                        if (player* plyr = dynamic_cast<player*>(firstObject)) {
                            if ((plyr->get_default_jump_force() == plyr->get_jump_force())) {
                                // can only release jump if the player does not have the boost of a jump pad
                                is_jump_pressed = false;
                            }
                        }

                    }


                }
                
            }
            
            //Close the window if the close window button is pressed or the escape button is pressed
            if (input_event.type == Event::Closed || (input_event.type == Event::KeyPressed && input_event.key.code == Keyboard::Escape)) {

                //Close the window
                sounds[2].play();
                int levelHere = levels.get_current_level_id();

                Time elapsed = clock.getElapsedTime(); //gets current time since program launch
                int seconds = static_cast<int>(elapsed.asSeconds()); //sets it in seconds
                timeOn += seconds;

                saveData(player_name, levelHere, timeOn);

                window.close();
            }
        }



        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        //Main game logic

        //Run the update function for every object in the current level
        levels.update_all_objects(delta, is_left_pressed, is_right_pressed, is_jump_pressed);

        //Check for collisions between all objects
        levels.detect_collisions();

        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-



        //Render
        //Clear the previous frame and color the background with light blue
        window.clear(Color(147, 248, 250));

        //Draw every object in the level
        for (auto obj : *levels.get_current_level()) {
            window.draw(obj->get_shape());
            window.draw(obj->get_sprite());
        }

        //Display the new frame
        window.display();

        //Returns the time elapsed from the last restart (time between each frame)
        delta = delta_clock.restart();
    }

    //Delete the level arrays
    levels.delete_levels();

    return 1;
    
}