/*
Shawn Singharaj
Assignment 3 Program Description: 
Simulates a single pokémon battle where each trainer has two pokémon: either Charmander, Bulbasaur, Squirtle, or Pidgey. 
The trainers take turns attacking, using potions, or swapping pokemon until both of the pokemon runs out of HP, and a winner is declared.
*/

#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <cstdlib>

#include "startup.hpp"
#include "battle.hpp"
#include "pokemon.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main() {
  	srand(static_cast<unsigned>(time(0))); // initialize random seed

	string trainer_1_pokemon_choice_2, trainer_2_pokemon_choice_2;
	string trainer_1_pokemon_choice_1 = prompt_first_pokemon(); // trainer 1's pokemon is prompted
	pokemon pokemon1_1 = assign_pokemon(trainer_1_pokemon_choice_1); // trainer 1's pokemon is assigned and returned as pokemon object
	string trainer_2_pokemon_choice_1 = prompt_second_pokemon(trainer_1_pokemon_choice_1); // trainer 2's pokemon is prompted
	pokemon pokemon2_1 = assign_pokemon(trainer_2_pokemon_choice_1); // trainer 2's pokemon is assigned and return as a pokemon object
	// last two pokemon
	prompt_third_pokemon(trainer_1_pokemon_choice_1, trainer_2_pokemon_choice_1, &trainer_1_pokemon_choice_2, &trainer_2_pokemon_choice_2); 
	pokemon pokemon1_2 = assign_pokemon(trainer_1_pokemon_choice_2); // assign the last two pokemon from the previous function
	pokemon pokemon2_2 = assign_pokemon(trainer_2_pokemon_choice_2);

	battle b(pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2); // battle object declared using the 4 pokemon
	b.battle_loop(pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2); // start the pokemon battle

}
