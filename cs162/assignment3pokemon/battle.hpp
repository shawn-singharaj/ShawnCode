#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "pokemon.hpp"

#include <string>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class battle {
	private: // private member variables
	pokemon pokemon1_1;
	pokemon pokemon2_1;
	pokemon pokemon1_2;
	pokemon pokemon2_2;
	int current_turn = 1;
	bool is_dead;

	public:
	battle(); // default constructor

	battle(pokemon& pokemon1_1, pokemon& pokemon2_1, pokemon& pokemon1_2, pokemon& pokemon2_2); // non-default constructor

	// swap_pokemon
	// takes in current trainer's turn to see which pokemon is to be switched, and uses the current pokemon used and the other objects to then return
	// the pokemon to be swapped back to the battle loop function to replace the pokemon they were using
	pokemon* swap_pokemon(int current_turn, pokemon* current_poke, pokemon& pokemon1_1, pokemon& pokemon2_1, pokemon& pokemon1_2, pokemon& pokemon2_2);

	// battle_loop
	// Battle loop using the trainer's pokemon that uses the 4 pokemon the trainers choose
	void battle_loop(pokemon& pokemon1_1, pokemon& pokemon2_1, pokemon& pokemon1_2, pokemon& pokemon2_2);
	
};

#endif
