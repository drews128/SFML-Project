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

	virtual ~game_object() {}

	//Called every frame (delta is the time between frame in seconds)
	virtual void update(float delta) {}

	//Called every time a collision is detected by the level manager
	virtual void on_collision(string type_of_other_object, Vector2f other_position, Vector2f other_size) {}

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
	int left_wall_count = 0;
	int right_wall_count = 0;
	int ceiling_count = 0;
	float move_speed = 300; //Movement speed
	float jump_force = -1950; //Jump force
	float y_velocity = 0; //Y velocity
public:
	//Constructor
	player(float x_position, float y_position, float width, float height, string type, Color color) : game_object(x_position,y_position,width,height,type,color)  {}

	//Override update function
	void update(float delta) override {

		//Apply y velocity (jump)
		shape.move(0,y_velocity * delta);

		//Reduce y velocity (make the jump go down)
		if (y_velocity < 0)
			y_velocity += 98;
		else
			y_velocity = 0;

		//Apply gravity only if the player isn't touching the ground
		if (get_floor_count() < 1)
			apply_gravity(delta);
	}

	//Update player's movement
	void update_movement(float delta, bool left, bool right, bool up) {
		//Left pressed and not colliding with a wall
		if (left && get_right_wall_count() < 1)
			//Move player
			shape.move(-1 * get_move_speed() * delta,0);
		//Right pressed and not colliding with a wall
		if (right && get_left_wall_count() < 1)
			//Move player
			shape.move(1 * get_move_speed() * delta, 0);
		//Jump pressed and on a floor
		if (get_floor_count() >= 1 && up)
			//Set y velocity to the jump_force
			y_velocity = jump_force;
	}

	//Override on collision function
	void on_collision(string type_of_other_object, Vector2f other_position, Vector2f other_size) override{
		//Check if other object is a platform
		if (type_of_other_object == "Platform") {
			//Colliding with a wall on the left side of the platform
			if (get_x_position() < other_position.x && get_y_position() > other_position.y - (get_height() - 10)) {
				set_left_wall_count(get_left_wall_count() + 1);
			}
			//Colliding with a wall on the right side of the platform
			else if (get_x_position() + get_width() > other_position.x + other_size.x && get_y_position() > other_position.y - (get_height() - 10)) {
				set_right_wall_count(get_right_wall_count() + 1);
			}
			//Colliding with the floor of a platform
			else if (get_y_position() + get_height() < other_position.y + 10) {
				set_floor_count(get_floor_count() + 1);
			}
			//Colliding with the ceiling of a platform
			else if (get_y_position() > other_position.y) {
				y_velocity = 0;
			}
		}
		
	}

	//Sets the collision counts to 0. Called at the beginning of the player's detect_collisions loop in the level manager
	void reset_collision_counts() {
		set_floor_count(0);
		set_left_wall_count(0);
		set_right_wall_count(0);
		set_ceiling_count(0);
	}

	//Getters
	int get_floor_count() {
		return floor_count;
	}
	
	int get_left_wall_count() {
		return left_wall_count;
	}
	int get_right_wall_count() {
		return right_wall_count;
	}

	int get_ceiling_count() {
		return ceiling_count;
	}
	float get_move_speed() {
		return move_speed;
	}
	//Setters
	void set_floor_count(int new_floor_count) {
		floor_count = new_floor_count;
	}
	void set_left_wall_count(int new_num) {
		left_wall_count = new_num;
	}
	void set_right_wall_count(int new_num) {
		right_wall_count = new_num;
	}
	void set_ceiling_count(int new_num) {
		ceiling_count = new_num;
	}
	void set_move_speed(float new_move_speed) {
		move_speed = new_move_speed;
	}
};

class enemy : public game_object {
protected:

	
	//the speed is how fast the enemy is, but if we don't want to try to make enemies move we can just set this to 0 or delete it
	int speed;


	int floor_count = 0; //Keeps track of the number of floors the player is currently in contact with
	int left_wall_count = 0;
	int right_wall_count = 0;

	float y_velocity = 0; //Y velocity

	float move_speed = 50; //Movement speed
	
	void set_move_speed(float move_speed) {
		this->move_speed = move_speed;
	}
	void set_speed(int speed) {
		this->speed = speed;
	}
public:


	void change_Directions() {
		this->speed = speed * -1;
	}

	int get_Speed() {
		return speed;
	}
	

	void on_collision(string type_of_other_object, Vector2f other_position, Vector2f other_size) {
		
		//Check if other object is an enemy
		if (type_of_other_object == "Enemy") {
			//Colliding with a wall on the left side of the platform
			if (get_x_position() < other_position.x && get_y_position() > other_position.y - (get_height() - 10)) {
				set_left_wall_count(get_left_wall_count() + 1);
			}
			//Colliding with a wall on the right side of the platform
			else if (get_x_position() + get_width() > other_position.x + other_size.x && get_y_position() > other_position.y - (get_height() - 10)) {
				set_right_wall_count(get_right_wall_count() + 1);
			}
			//Colliding with the floor of a platform
			else if (get_y_position() + get_height() < other_position.y + 10) {
				set_floor_count(get_floor_count() + 1);
			}

		}
	}
	void reset_collision_counts() {
		set_floor_count(0);
		set_left_wall_count(0);
		set_right_wall_count(0);
	}

	int get_floor_count() {
		return floor_count;
	}
	void set_floor_count(int new_floor_count) {
		floor_count = new_floor_count;
	}
	int get_left_wall_count() {
		return left_wall_count;
	}
	int get_right_wall_count() {
		return right_wall_count;
	}
	void set_left_wall_count(int new_num) {
		left_wall_count = new_num;
	}
	void set_right_wall_count(int new_num) {
		right_wall_count = new_num;
	}
	float get_move_speed() {
		return move_speed;
	}
	
	void change_direction() {
		if (get_move_speed() > 0) {
			set_move_speed(get_move_speed() * -1);
		}
	}

	//Enemy constructor
	enemy(int speed, float x_position, float y_position, float width, float height, string type, Color color) : game_object(x_position, y_position, width, height, type, color) {
		set_speed(speed);
	}
	//Default constructor
	enemy() = default;
	//Destructor
	~enemy() {};
};


	



	
	

	


class ground_enemy: public enemy {

public:

	void update_movement(float delta) {
		shape.move(get_move_speed() * delta, 0);
	}


	void update(float delta) override {

		//Apply y velocity (jump)
		shape.move(0, y_velocity * delta);

		//Reduce y velocity (make the jump go down)
		if (y_velocity < 0)
			y_velocity += 98;
		else
			y_velocity = 0;

		//Apply gravity only if the player isn't touching the ground
		if (get_floor_count() < 1)
			apply_gravity(delta);
	}

	//Ground enemy constructor
	ground_enemy(float x_position, float y_position, float width, float height, string type, Color color) : game_object(x_position, y_position, width, height, type, color) {}
	//Destructor
	~ground_enemy() {};
	
};
	

class flying_enemy: public enemy{


public:
	//Flying enemy constructor
	flying_enemy(float x_position, float y_position, float width, float height, string type, Color color) : game_object(x_position, y_position, width, height, type, color) {};
	//Destructor
	~flying_enemy() {};
};


class end_goal : public game_object {
protected:
	int level_to_load = 1;
public:
	end_goal(float x_position, float y_position, float width, float height, string type, Color color, int level) : game_object(x_position,y_position,width,height,type,color) {
		set_level_to_load(level);
	}

	//Getter(s)
	int get_level_to_load() {return level_to_load;}
	//Setter(s)
	void set_level_to_load(int new_level) { level_to_load = new_level; }
};