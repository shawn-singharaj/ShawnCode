#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>

#include "game.hpp"
#include "gold.hpp"
#include "bat_swarm.hpp"
#include "bottomless_pit.hpp"
#include "wumpus.hpp"
#include "escape_rope.hpp"
#include "arrow.hpp"
#include "room.hpp"
#include "player.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// game implementation

game::game(int width, int height, bool debug, player& p) : width(width), height(height), debug(debug), p(p), cave(height, vector<room>(width)) {
	int rand_x, rand_y;
	int num_events = 0;
	
	// escape rope at player's starting location
	cave.at(p.get_location_x()).at(p.get_location_y()).set_event(new escape_rope);

	// assign 1 wumpus to random room
	while(num_events < 1){
		rand_x = rand() % (width);
		rand_y = rand() % (height);
		if(cave.at(rand_x).at(rand_y).get_event() == nullptr){
			cave.at(rand_x).at(rand_y).set_event(new wumpus);
			num_events++;
		}
	}

	// assign 1 gold to random room
	num_events = 0;
	while(num_events < 1){
		rand_x = rand() % (width);
		rand_y = rand() % (height);
		if(cave.at(rand_x).at(rand_y).get_event() == nullptr){
			cave.at(rand_x).at(rand_y).set_event(new gold);
			num_events++;
		}
	}

	// assign 2 bottomless pits to random rooms
	num_events = 0;
	while(num_events < 2){
		rand_x = rand() % (width);
		rand_y = rand() % (height);
		if(cave.at(rand_x).at(rand_y).get_event() == nullptr){
			cave.at(rand_x).at(rand_y).set_event(new bottomless_pit);
			num_events++;
		}
	}

	// assign 2 bat swarms to random rooms
	num_events = 0;
	while(num_events < 2){
		rand_x = rand() % (width);
		rand_y = rand() % (height);
		if(cave.at(rand_x).at(rand_y).get_event() == nullptr){
			cave.at(rand_x).at(rand_y).set_event(new bat_swarm);
			num_events++;
		}
	}

	// assign 2 arrows to random rooms
	num_events = 0;
	while(num_events < 2){
		rand_x = rand() % (width);
		rand_y = rand() % (height);
		if(cave.at(rand_x).at(rand_y).get_event() == nullptr){
			cave.at(rand_x).at(rand_y).set_event(new arrow);
			num_events++;
		}
	}

}

void game::display_game() const{
	cout << endl << endl;
	cout << "Arrows remaining: " << p.get_num_arrows() << endl;

	string row_border = "--";
	for (int i = 0; i < this->width; ++i) {
		row_border += "-----";
	}

	cout << row_border << endl;
	for (int i = 0; i < this->height; ++i) {
		cout << "||";
		for (int j = 0; j < this->width; ++j) {
		
			if(p.get_location_x() == i && p.get_location_y() == j) // print player symbol
			{	
				cout << " *";
			}
			else if(this->debug && cave.at(i).at(j).get_event() != nullptr){
				cout << " " << cave.at(i).at(j).get_event()->get_debug_symbol(); // print symbol from event class
			}
			else{
				cout << "  "; 
			}

			cout << " ||";
		}
		cout << endl;
		cout << row_border << endl;
	}
}

bool game::is_direction(char c) { // return valid user input for direction
	return c == 'w' ||
		c == 'a' ||
		c == 's' ||
		c == 'd';
}

char game::to_lower(char direction) { // lowercase
	if (direction >= 'A' && direction <= 'Z') {
		return direction + ('a' - 'A');
	}
	return direction;
}

bool game::can_move_in_direction(char direction, player& p) {
	
	if((p.get_location_x() == 0 && direction == 'w')) // if player is at the top and tries to move up
		{
			return false;
		} 

	if((p.get_location_x() == width - 1 && direction == 's')){ // if player is at bottom and tries to move down
		return false;
	}	

	if((p.get_location_y() == 0 && direction == 'a')){ // if player is at the left border and tries to move left
		return false;
	}
	
	if((p.get_location_y() == height - 1 && direction == 'd')){ // if player is at the right border and tries to move right
		return false;
	}

	return true;
}

bool game::is_valid_action(char action) {	// check if user input is good
	if (this->is_direction(action)) { 
		char direction = action;
		return this->can_move_in_direction(direction, p);
	} else if (action == 'f') {
		return p.get_num_arrows() > 0;
	}
	return false;
}

void game::print_action_error(char action) { // print if user can move in direction or out of arrows
	if (this->is_direction(action)) {
		cout << "You can't move in that direction!" << endl <<
			endl;
	} else if (action == 'f') {
		cout << "You're out of arrows!" << endl << endl;
	} else {
		cout << endl << "That's an invalid input!" << endl
			<< endl;
	}
}

char game::get_player_action() { // print menu
	char action;
	bool first = true;
	do {
		if (!first) {
			char previous_action = action;
			this->print_action_error(previous_action);
		}
		first = false;

		cout << endl << endl << "What would you like to do?" <<
			endl << endl;
		cout << "w: move up" << endl;
		cout << "a: move left" << endl;
		cout << "s: move down" << endl;
		cout << "d: move right" << endl;
		cout << "f: fire an arrow" << endl;

		cin >> action;
		action = this->to_lower(action);
	} while (!this->is_valid_action(action));

	return action;
}

char game::get_arrow_fire_direction() { // arrow menu
	char direction;
	bool first = true;
	do {
		if (!first) {
			cout << endl << "That's an invalid input!" <<
				endl << endl;
		}
		first = false;

		cout << endl << endl <<
			"What direction would you like to fire the arrow?" << endl <<
			endl;
		cout << "w: up" << endl;
		cout << "a: left" << endl;
		cout << "s: down" << endl;
		cout << "d: right" << endl;

		cin >> direction;
		direction = this->to_lower(direction);
	} while (!this->is_direction(direction));

	return direction;
}

void game::move(char direction, player& p) { // moves the player
		
		if(p.get_is_confused()){ // if user has gone into a bat swarm the turn before
			cout << endl << "You are confused and walk in a random direction." << endl;
			bool valid = false;
			int rand_direction; 
			do{
				rand_direction = rand() % 4; // generate random numbers 0-3
				if(p.get_location_x() == 0 && rand_direction == 0){ // if player is at top and direction is up
					continue;
				}
				if(p.get_location_x() == width - 1 && rand_direction == 2){ // if player is at bottom and direciton is down
					continue;
				}
				if(p.get_location_y() == 0 && rand_direction == 1){ // if player is at left and direction is left
					continue;
				}
				if(p.get_location_y() == height - 1 && rand_direction == 3){ // if player is at right and direction is right
					continue;
				}
				else{ // if the direction doesnt go out of bounds
					valid = true;	
				}
								
			}while(!valid); // if one of the three if statements are true, generate a new number until it is valid

			switch(rand_direction){ // assign the random number to keybinds
               case 0: 
                    direction = 'w'; 
                    break;
               case 1:                   
                    direction = 'a';
                    break;
               case 2:                    
                    direction = 's';
                    break;
               default:                    
                    direction = 'd';
                    break;
			}
			p.set_is_confused(0);// player is no longer confused
		}
		
	// move the player in the direction	
	if (direction == 'w') {
		p.move_up();
	} else if (direction == 'a') {
		p.move_left();
	} else if (direction == 'd') {
		p.move_right();
	} else {
		p.move_down();
	}
}

void game::move_wumpus(){
	int num_events = 0;
	int rand_x, rand_y;

	for (int i = 0; i < this->height; ++i) {
		for (int j = 0; j < this->width; ++j) {
			if(cave.at(i).at(j).get_event() != nullptr &&  // if the spot in the cave has an event and wumpus, delete it
			cave.at(i).at(j).get_event()->get_debug_symbol() == 'W'){
				delete cave.at(i).at(j).get_event(); 
				cave.at(i).at(j).set_event(nullptr);
			}	
		}
	}	

	while(num_events < 1){ // loop until find empty room
		rand_x = rand() % (width); // generate random numbers for placement 
		rand_y = rand() % (height);
		if(cave.at(rand_x).at(rand_y).get_event() == nullptr &&  // if the random room is empty and not where the player is
		(rand_x != p.get_location_x() && rand_y != p.get_location_y())){
			cave.at(rand_x).at(rand_y).set_event(new wumpus); // allocate new wumpus event in that room
			num_events++;
		}
	}
}

void game::fire_arrow_up() {
	int num_rooms = 1;
	// loops until the arrow either hits a wall or goes through three rooms
	while (p.get_location_x() - num_rooms >= 0 && num_rooms <= 3) { 
		if (cave.at(p.get_location_x() - num_rooms).at(p.get_location_y()).get_event() != nullptr) { // if the room has an event
			if (cave.at(p.get_location_x() - num_rooms).at(p.get_location_y()).get_event()->get_debug_symbol() == 'W') { // if the event is wumpus
				cout << "The Wumpus has been slain!" << endl;
				p.set_check_win(1); // player wins
				break;
			}
		}
   		num_rooms++;  // Move to the next room
	}

	num_rooms--;
	if(!p.get_check_win()){ // if the arrow doesnt hit the wumpus, move the wumpus 
		cout << endl << "I think I missed, the Wumpus might have moved off somewhere..." << endl;
		if(cave.at(p.get_location_x() - num_rooms).at(p.get_location_y()).get_event() == nullptr){
			cave.at(p.get_location_x() - num_rooms).at(p.get_location_y()).set_event(new arrow); // assign arrow to the room it landed in
		}
		move_wumpus();
	}

}

void game::fire_arrow_down() {
	int num_rooms = 1;
	// loops until the arrow either hits a wall or goes through three rooms
	while (p.get_location_x() + num_rooms < height && num_rooms <= 3) {
		if (cave.at(p.get_location_x() + num_rooms).at(p.get_location_y()).get_event() != nullptr) { // if the room has an event
			if (cave.at(p.get_location_x() + num_rooms).at(p.get_location_y()).get_event()->get_debug_symbol() == 'W') { // if the event is wumpus
				cout << "The Wumpus has been slain!" << endl;
				p.set_check_win(1); // player wins
				break;
			}
		}
   		num_rooms++;  // Move to the next room
	}

	num_rooms--;
	if(!p.get_check_win()){ // if the arrow doesnt hit the wumpus, move the wumpus 
		cout << endl << "I think I missed, the Wumpus might have moved off somewhere..." << endl;
		if(cave.at(p.get_location_x() + num_rooms).at(p.get_location_y()).get_event() == nullptr){
			cave.at(p.get_location_x() + num_rooms).at(p.get_location_y()).set_event(new arrow); // assign arrow to the room it landed in
		}
		move_wumpus();
	}
}

void game::fire_arrow_left() {
	int num_rooms = 1;
	// loops until the arrow either hits a wall or goes through three rooms
	while (p.get_location_y() - num_rooms >= 0 && num_rooms <= 3) {
		if (cave.at(p.get_location_x()).at(p.get_location_y() - num_rooms).get_event() != nullptr) { // if the room has an event
			if (cave.at(p.get_location_x()).at(p.get_location_y() - num_rooms).get_event()->get_debug_symbol() == 'W') { // if the event is wumpus
				cout << "The Wumpus has been slain!" << endl;
				p.set_check_win(1);
				break;
			}
		}
   		num_rooms++;  // Move to the next room
	}

	num_rooms--;
	if(!p.get_check_win()){ // if the arrow doesnt hit the wumpus, move the wumpus 
		cout << endl << "I think I missed, the Wumpus might have moved off somewhere..." << endl;
		if(cave.at(p.get_location_x()).at(p.get_location_y() - num_rooms).get_event() == nullptr){
			cave.at(p.get_location_x()).at(p.get_location_y() - num_rooms).set_event(new arrow); // assign arrow to the room it landed in
		}
		move_wumpus();
	}
		
}

void game::fire_arrow_right() {
	int num_rooms = 1;
	// loops until the arrow either hits a wall or goes through three rooms
	while (p.get_location_y() + num_rooms < width && num_rooms <= 3) {
		if (cave.at(p.get_location_x()).at(p.get_location_y() + num_rooms).get_event() != nullptr) { // if the room has an event
			if (cave.at(p.get_location_x()).at(p.get_location_y() + num_rooms).get_event()->get_debug_symbol() == 'W') { // if the event is wumpus
				cout << "The Wumpus has been slain!" << endl;
				p.set_check_win(1);
				break;
			}
		}
   		num_rooms++;  // Move to the next room
	}

	num_rooms--;
	if(!p.get_check_win()){ // if the arrow doesnt hit the wumpus, move the wumpus 
		cout << endl << "I think I missed, the Wumpus might have moved off somewhere..." << endl;
		if(cave.at(p.get_location_x()).at(p.get_location_y() + num_rooms).get_event() == nullptr){ 
			cave.at(p.get_location_x()).at(p.get_location_y() + num_rooms).set_event(new arrow); // assign arrow to the room it landed in
		}
		move_wumpus();
	}
}

void game::fire_arrow(char direction, player& p) { 
	if (direction == 'w') {
		this->fire_arrow_up();
	} else if (direction == 'a') {
		this->fire_arrow_left();
	} else if (direction == 'd') {
		this->fire_arrow_right();
	} else {
		this->fire_arrow_down();
	}

	p.set_num_arrows(p.get_num_arrows() - 1);
}


void game::play_game(){
		// loop until player loses or wins
		while (!p.get_check_win() && !p.get_check_loss()) {
		// Print game board
		this->display_game();
		
		// percepts
		// check up
		if(p.get_location_x() > 0 && cave.at(p.get_location_x() - 1).at(p.get_location_y()).get_event() != nullptr){
			cave.at(p.get_location_x() - 1).at(p.get_location_y()).get_event()->percept();
		}
		
		// check down
		else if((p.get_location_x() < width - 1) && cave.at(p.get_location_x() + 1).at(p.get_location_y()).get_event() != nullptr){
			cave.at(p.get_location_x() + 1).at(p.get_location_y()).get_event()->percept();
		}

		// check left
		else if((p.get_location_y() > 0) && cave.at(p.get_location_x()).at(p.get_location_y() - 1).get_event() != nullptr){
			cave.at(p.get_location_x()).at(p.get_location_y() - 1).get_event()->percept();
		}

		// check right
		else if((p.get_location_y() < height - 1) && cave.at(p.get_location_x()).at(p.get_location_y() + 1).get_event() != nullptr){
			cave.at(p.get_location_x()).at(p.get_location_y() + 1).get_event()->percept();
		}

		// Ask player for their action
		char action = this->get_player_action();

		// Process action
		if (this->is_direction(action)) {
			// W/A/S/D = move player
			char direction = action;
			this->move(direction, p);
		} else {
			// F = prompt for arrow fire direction and fire arrow
			char direction = this->get_arrow_fire_direction();
			this->fire_arrow(direction, p);
		}

		// if the player enters a room with an event
		if(cave.at(p.get_location_x()).at(p.get_location_y()).get_event() != nullptr){
			// call the event's encounter function
			cave.at(p.get_location_x()).at(p.get_location_y()).get_event()->encounter(p);
			
			// if the player enters a room that is gold or arrow, remove the event once the player leaves
			if(cave.at(p.get_location_x()).at(p.get_location_y()).get_event()->get_debug_symbol() == 'A'||
				cave.at(p.get_location_x()).at(p.get_location_y()).get_event()->get_debug_symbol() == 'G'){

					delete cave.at(p.get_location_x()).at(p.get_location_y()).get_event(); 
					cave.at(p.get_location_x()).at(p.get_location_y()).set_event(nullptr);
			}
		}
	}
	// outcome outputs
	if(p.get_check_loss()){
		cout << endl << "Game over, you died." << endl;
	}
	else{
		cout << endl << "You win!" << endl;
	}

	// free memory
	for (int i = 0; i < this->height; ++i) {
		for (int j = 0; j < this->width; ++j) {
			if(cave.at(i).at(j).get_event() != nullptr){
				delete cave.at(i).at(j).get_event(); 
				cave.at(i).at(j).set_event(nullptr);
			}	
		}
	}	
}
