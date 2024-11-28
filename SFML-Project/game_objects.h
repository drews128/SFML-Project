#pragma once
#include <iostream>
#include <string>
using namespace std;

//SFML files
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
//SFML namespace
using namespace sf;

class game_object {
protected:
	string type; //The type of object ("Enemy", "Player", etc.)
	RectangleShape shape; //The object's shape
public:
	game_object(float x_position, float y_position, float width, float height, string type, Color color) {
		set_position(x_position, y_position);
		set_size(width,height);
		set_type(type);
		set_color(color);
	}

	virtual void update(int delta) {
		//Called every frame
	}

	//Getters
	float get_x_position() { return shape.getPosition().x; };
	float get_y_position() { return shape.getPosition().y; };
	float get_width() { return shape.getSize().x; };
	float get_height() { return shape.getSize().y; };
	string get_type() {return type;}
	RectangleShape get_shape() { return shape; };
	Color get_color() { return shape.getFillColor(); };
	//Setters
	void set_position(float x_position, float y_position) { shape.setPosition(Vector2f(x_position,y_position)); };
	void set_size(float width, float height) { shape.setSize(Vector2f(width, height)); };
	void set_type(string type) { this->type = type; };
	void set_color(Color color) { shape.setFillColor(color); };
};