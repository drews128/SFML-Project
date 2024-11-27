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

    //Create window with SFML
    Window window(VideoMode(960, 720), "Game Title", Style::Titlebar | Style::Close);
    //SFML input detection
    Event input_event;

    //Main game loop -- exits when the window is closed
    while (window.isOpen()) {

    }

    return 1;
}