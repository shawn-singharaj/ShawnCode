#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class move {
	private: // private memebr functions for each move
	string name;
	string type;
	int base_damage = 0;
	int num_uses = 0;

	public:
	move(); // default constructor

	// non-default constructor
	move(string name, string type, int base_damage, int num_uses);

	// getters
	string get_name() const;
	string get_type() const;
	int get_damage() const;
	int get_num_uses() const;

	// setters
	void set_num_uses(int num_uses);
};

#endif
