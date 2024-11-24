#include "bottomless_pit.hpp"

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

bottomless_pit::bottomless_pit() : event(symbol){}

char bottomless_pit::get_debug_symbol() const{
     return this->symbol;
}

void bottomless_pit::encounter(player& p) const{
     int rand_num = rand() % 100;

     if(rand_num <= 49){ // 50 percent chance player loses
          cout << endl << "Oh no! You've fallen into a bottomless pit never to be seen again." << endl;
          p.set_check_loss(1);
     }
     else{
          cout << endl << "You almost fell into a bottomless pit, whew!" << endl;
     }
  
}

void bottomless_pit::percept() const{ // if player is near
     cout << endl << "You feel a breeze." << endl;
}