#include <iostream>
using namespace std;

#include "SFML/Graphics.hpp"

int main()
{
    //Test code
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

<<<<<<< Updated upstream
        window.clear();
        window.draw(shape);
=======


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
        }

        //Display the new frame
>>>>>>> Stashed changes
        window.display();
    }

    //Test

    //Testing testing 123

    return 1;
}