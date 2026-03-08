#ifndef GOLD_HPP
#define GOLD_HPP

#include "event.hpp"

class gold:public event{
    private:
    char symbol = 'G';

    public:
    gold();

    // Pure virtual function to warn player of event
   void percept() const;

   // Pure virtual function for encounter 
   void encounter(player& p) const;

   // Pure virtual function to return a debug symbol for the event (for debug mode)
   char get_debug_symbol() const;

};

#endif
