#ifndef ARROW_HPP
#define ARROW_HPP

#include "event.hpp"

class arrow:public event{
   private:
   char symbol = 'A';

   public:
   arrow(); // constructor

   // Pure virtual function to warn player of event
   void percept() const;

   // Pure virtual function for encounter 
   void encounter(player& p) const;

   // Pure virtual function to return a debug symbol for the event (for debug mode)
   char get_debug_symbol() const;

};
#endif
