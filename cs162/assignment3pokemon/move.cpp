#include "move.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
    // default constructor
    move::move():name(""), type(""), base_damage(0), num_uses(0)
    {
    }
    
    // non-default constructor
	move::move(string name, string type, int base_damage, int num_uses):
    name(name), type(type), base_damage(base_damage), num_uses(num_uses)
    {
    }
    
    // getters
	string move::get_name() const{
        return this->name;
    }
	string move::get_type() const{
        return this->type;
    }
	int move::get_damage() const{
        return this->base_damage;
    }
	int move::get_num_uses() const{
        return this->num_uses;
    }

    // setter
    void move::set_num_uses(int num_uses){
        this->num_uses = num_uses;
    }
