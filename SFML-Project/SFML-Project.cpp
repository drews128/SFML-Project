#include <iostream>
#include <string>
using namespace std;

//SFML files
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
//SFML namespace
using namespace sf;

int main()
{
    //Variables
    string player_name;
    int user_seleciton;
    int current_level = 0;

    //Inital message
    cout << "Welcome to [GAME TITLE GOES HERE]!" << endl;
    //New game or continue
    cout << "1. Start New Game" << endl << "2. Continue From Existing Save File" << endl;
    //Get user selection
    cin >> user_seleciton;
    switch(user_seleciton){
    case 1:
        //New game
        cout << endl << "Enter Your Name:" << endl;
        cin >> player_name;

        //TODO: Save player name to save file

        current_level = 0;

        break;
    case 2:
        //Continue

        //TODO: Add continuing from save file

        break;
    default:
        //Invalid input handling
        cout << endl << "Invalid input!" << endl;
        return -1;
        break;
    }

    //Some of the following code is based on the offical SFML documentation example (https://www.sfml-dev.org/documentation/2.6.2/)
    //Create window with SFML
    RenderWindow window(VideoMode(1440, 810), "Game Title", Style::Titlebar | Style::Close);
    //SFML input detection
    Event input_event;

    //Main game loop -- exits when the window is closed
    while (window.isOpen()) {
        //Detect user inputs
        while (window.pollEvent(input_event)) {

            //TODO: Detect user input

            //Close the window if the close window button is pressed or the escape button is pressed
            if (input_event.type == Event::Closed || input_event.type == Event::KeyPressed && input_event.key.code == Keyboard::Escape)
                //Close the window
                window.close();
        }

        //TODO: Main game logic goes here

        //Render
        //Clear the previous frame
        window.clear();

        //TODO: Main game rendering (drawing all of the objects) goes ehre

        //Display the new frame
        window.display();
    }

    return 1;
}