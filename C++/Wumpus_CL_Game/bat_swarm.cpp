#include "bat_swarm.hpp"


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

bat_swarm::bat_swarm() : event(symbol){}

char bat_swarm::get_debug_symbol() const{
     return this->symbol;
}

void bat_swarm::encounter(player& p) const{
     cout << endl << "You encounter a swarm of bats and don't know where you're going." << endl;
     p.set_is_confused(1); // sets player to confused so random movement next turn
}

void bat_swarm::percept() const{
     cout << endl << "You hear screeching." << endl; // if player is near
}