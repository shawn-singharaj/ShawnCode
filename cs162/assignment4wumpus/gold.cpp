#include "gold.hpp"

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

gold::gold() : event(symbol){}

char gold::get_debug_symbol() const{
     return this->symbol;
}

void gold::encounter(player& p) const{ 
     cout << endl << "You have encountered the gold you were looking for, now lets get out of here!" << endl;
     p.set_has_gold(1);    // player picks up gold
}

void gold::percept() const{
     cout << endl << "You stub your toe on something heavy." << endl; // if player is near
}