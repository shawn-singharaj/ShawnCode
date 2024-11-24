#ifndef BOTTOMLESS_PIT_HPP
#define BOTTOMLESS_PIT_HPP

#include "event.hpp"

class bottomless_pit:public event{
   private:
   char symbol = 'P';

   public:
   bottomless_pit();
   

   
   // Pure virtual function to warn player of event
   void percept() const;

   // Pure virtual function for encounter 
   void encounter(player& p) const;

   // Pure virtual function to return a debug symbol for the event (for debug mode)
   char get_debug_symbol() const;

};
#endif
