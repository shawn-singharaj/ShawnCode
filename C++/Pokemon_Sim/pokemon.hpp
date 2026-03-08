#ifndef POKEMON_HPP
#define POKEMON_HPP

#include "move.hpp"

#include <string>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class pokemon {
	private: // private member variables
	string name;
	string type;
	int hp = 0;
	int max_hp = 0;
	int attack = 0;
	int defense = 0;
	move *Moves; // array of move objects
	int num_moves = 0;

	public:
	pokemon(); // default constructor

	// non-default constructor
	pokemon(string n, string t, int h, int a, int d, int nm);

	// destructor for Moves array
	~pokemon();

	// copy constructor
	pokemon(const pokemon& p);

	// assignment overload operator
	pokemon& operator=(const pokemon& p);

	// Allocates memory for Moves array and returns pointer for it. 
	// It allocates memory bsed off the pokemon's number of moves and assigns the two move objects to it
	move* set_Move(int nm, move move1, move move2);

	// getters
	string get_name() const;
	string get_type() const;
	int get_hp() const;
	int get_max_hp() const;
	int get_defense() const;
	move* get_Moves(int idx) const;

	// setter
	void set_hp(int hp);
	
	// type_interact
	// Takes parameters for the opposing pokemon to get it's type and the user's move choice
	// and takes the move's type and returns a double that is the damage multiplier based off type interaction
	double type_interact(pokemon opp_poke, int choice);

	// damage_calc
	// Takes the type interaction above, the random multiplier generated, the random critical hit chance generated, the
	// user's move choice and the opposing pokemon and returns the calculated damage from the document
	int damage_calc(double ti, double rm, int rc, int choice, pokemon opp_poke);

	// use_move
	// Prompts the user to use one of the moves and calls damage_calc then calls the poke_attack to get the new HP value of the
	// opposing pokemon
	void use_move(pokemon &opp_poke);

	// heal
	// Adds 10 to the pokemon's HP
	void heal(int hp);

	// poke_attack
	// Takes the damage number and subtracts it to the opposing pokemon's HP
	void poke_attack(pokemon &opp_poke, int damage);
};

#endif
