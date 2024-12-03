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
	Vector2f inital_position; //The inital position of the object. Used to reset the objects position
	string type; //The type of object ("Enemy", "Player", etc.)
	RectangleShape shape; //The object's shape
public:
	//Constructor
	game_object(float x_position, float y_position, float width, float height, string type, Color color) {
		set_inital_position(x_position, y_position);
		set_position(x_position, y_position);
		set_size(width,height);
		set_type(type);
		set_color(color);
	}

	//Called every frame (delta is the time between frame in seconds)
	virtual void update(float delta) {}

	//Called every time a collision is detected by the level manager
	virtual void on_collision(string type_of_other_object) {}

	//Resets the position of the object
	void reset_position() {
		shape.setPosition(inital_position);
	}

	//Applys gravity to an object. Should only be called if an object should have gravity applied to it
	virtual void apply_gravity(float delta) {
		float fall_speed = 50;
		shape.move(0, 9.8 * fall_speed * delta);
	}

	//Getters
	Vector2f get_inital_position() { return inital_position; };
	float get_x_position() { return shape.getPosition().x; };
	float get_y_position() { return shape.getPosition().y; };
	float get_width() { return shape.getSize().x; };
	float get_height() { return shape.getSize().y; };
	string get_type() {return type;}
	RectangleShape get_shape() { return shape; };
	Color get_color() { return shape.getFillColor(); };
	//Setters
	void set_inital_position(float x_position, float y_position) { inital_position.x = x_position; inital_position.y = y_position; };
	void set_position(float x_position, float y_position) { shape.setPosition(Vector2f(x_position,y_position)); };
	void set_size(float width, float height) { shape.setSize(Vector2f(width, height)); };
	void set_type(string type) { this->type = type; };
	void set_color(Color color) { shape.setFillColor(color); };
};

class player : public game_object {
protected:
	int floor_count = 0; //Keeps track of the number of floors the player is currently in contact with
	float move_speed = 250;
public:
	//Constructor
	player(float x_position, float y_position, float width, float height, string type, Color color) : game_object(x_position,y_position,width,height,type,color)  {
		//TODO: Player variables need to be set here
	}

	//Override update function
	void update(float delta) override {
		//Apply gravity only if the current floor count is less than 1 (0)
		if (get_floor_count() < 1)
			apply_gravity(delta);
	}

	void update_movement(float delta, bool left, bool right, bool up) {
		if (left)
			shape.move(-1 * get_move_speed() * delta,0);
		if (right)
			shape.move(1 * get_move_speed() * delta, 0);
	}

	//Override on collision function
	void on_collision(string type_of_other_object) override{
		if (type_of_other_object == "Platform") {
			//Increase the floor count by one
			set_floor_count(get_floor_count() + 1);
		}
	}

	//Sets the floor count to 0. Called at the beginning of the player's detect_collisions loop in the level manager
	void reset_floor_count() {
		set_floor_count(0);
	}

	//Getters
	int get_floor_count() {
		return floor_count;
	}
	float get_move_speed() {
		return move_speed;
	}
	//Setters
	void set_floor_count(int new_floor_count) {
		floor_count = new_floor_count;
	}
	void set_move_speed(float new_move_speed) {
		move_speed = new_move_speed;
	}
};