#ifndef STARTUP_HPP
#define STARTUP_HPP

#include <string>
#include "pokemon.hpp"
using std::string;

/*
 * Function: prompt_first_pokemon
 * Description: Prompts trainer 1 for their pokemon of choice. Loops until
 * 	user supplies valid choice value.
 * Returns (string): returns pokemon name
 */
string prompt_first_pokemon();

/*
 * Function: prompt_second_pokemon
 * Description: Prompts trainer 2 for their pokemon of choice. Loops until
 * 	user supplies valid choice value. Does not allow user to choose
 * 	the blacklisted pokemon (which should be the numeric code for the
 * 	pokemon chosen by trainer 1)
 * Parameters:
 * 	blacklisted_pokemon (string): the first trainer's pokemon choice
 * Returns (string): pokemon name
 */
string prompt_second_pokemon(string bp1);

// prompt_third_pokemon
// Takes the previous two choices, and two pointers representing the third and fourth pokemon
// and outputs a menu to prompt the first trainer to choose their second pokemon and the fourth
// pokemon is automatically assigned to the second trainer
void prompt_third_pokemon(string bp1, string bp2, string* p1_2, string* p2_2);


// assign_pokemon
// takes the string from above functions and initializes objects, returns the pokemon object with the
// movesets initialized to implement into the battle object
pokemon assign_pokemon(string choice);

#endif
