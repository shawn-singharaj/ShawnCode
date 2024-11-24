#include "wumpus.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

wumpus::wumpus() : event(symbol){}

char wumpus::get_debug_symbol() const{ // returns 'W'
     return this->symbol;
}

void wumpus::encounter(player& p) const{
     cout << endl << "Uh oh, you're dead." << endl;
     p.set_check_loss(1); // player loses
    
}

void wumpus::percept() const{
     cout << endl << "The hairs stand up on the back of your neck." << endl; // if player is close
}


