#include "room.hpp"

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::string;

room::room(): e(nullptr){
}

void room::set_event(event* e){
    this->e = e;
}

event* room::get_event() const{
    return this->e;
}


