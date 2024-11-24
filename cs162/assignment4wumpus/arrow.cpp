#include "arrow.hpp"

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

arrow::arrow() : event(symbol){}

char arrow::get_debug_symbol() const{ // returns 'A'
     return this->symbol;
}

void arrow::encounter(player& p) const{
     cout << endl << "I found an arrow." << endl;
     p.set_num_arrows(p.get_num_arrows() + 1); // increase player arrow count by 1
}


void arrow::percept() const{ // no percept
     
}

