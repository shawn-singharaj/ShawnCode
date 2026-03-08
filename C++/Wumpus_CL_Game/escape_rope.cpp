#include "escape_rope.hpp"

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

escape_rope::escape_rope() : event(symbol){}

char escape_rope::get_debug_symbol() const{
     return this->symbol;
}

void escape_rope::encounter(player& p) const{
     cout << endl << "Here is the escape rope I used to enter." << endl;
     if(p.get_has_gold()){
          cout << "Looks like we are making it out rich!" << endl;
          p.set_check_win(1); // player wins if they already have gold
     }
     else{
          cout << "I can't leave without something, I gotta go back in." << endl; // nothing happens if they dont have gold
     }    
}

void escape_rope::percept() const{

}

