/*
Shawn Singharaj
CS162
Assignment 4: Hunt the Wumpus
The user guides an adventurer through a cave set up in a grid system. The goal is to find the randomly placed gold
and escape to avoid dying to the Wumpus or falling into a bottomless pit.  There will be five random events possible: 
picking up an arrow, finding gold, falling into a pit, running into bats, or running into Wumpus. 
The player wins when they retrieve the gold and use an escape rope or to shoot the Wumpus with an arrow by guessing the room it is in.
*/



#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.hpp"
#include "player.hpp"

using std::cout;
using std::cin;
using std::endl;

/*
 * Function: get_width
 * Description: Prompts the user for the game board width (# of columns)
 * Returns (int): Valid width supplied by user
 */
int get_width() {
	int width;
	bool first = true;
	do {
		if (!first) {
			cout << endl << "Invalid width!" << endl <<
				endl;
		}
		first = false;
		cout << "Enter the game board width between 4 and 30: ";
		cin >> width;
	} while(width < 4 || width > 30);
	return width;
}

/*
 * Function: get_height
 * Description: Prompts the user for the game board height (# of columns)
 * Returns (int): Valid height supplied by user
 */
int get_height() {
	int height;
	bool first = true;
	do {
		if (!first) {
			cout << endl << "Invalid height!" << endl <<
				endl;
		}
		first = false;
		cout << "Enter the game board height between 4 and 30: ";
		cin >> height;
	} while(height < 4 || height > 30);
	return height;
}

/*
 * Function: get_debug
 * Description: Prompts the user whether they want to play in debug mode
 * Returns (bool): True if the user wants to play in debug mode. False
 * 		otherwise.
 */
bool get_debug() {
	int debug_input;
	bool first = true;
	do {
		if (!first) {
			cout << endl << "Invalid input!" << endl <<
				endl;
		}
		first = false;
		cout << "Would you like to play in debug mode? (1-yes, 0-no): ";
		cin >> debug_input;
	} while(debug_input != 0 && debug_input != 1);
	return debug_input == 1;
}

int main()
{
	// Set the random seed
	srand(time(nullptr));
	
	// Ask user for width and height of game board
	int width = get_width();
	int height = get_height();

	// Ask user whether they want debug mode
	bool debug = get_debug();

	// generate random spot for player to start
	int rand_x = rand() % (width - 1);
	int rand_y = rand() % (height - 1);
	player p(rand_x, rand_y);
	
	// Construct game object
	game g(width, height, debug, p);

	//Play game
	g.play_game();

	return 0;
}
