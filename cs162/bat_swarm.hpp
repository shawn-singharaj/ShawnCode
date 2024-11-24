#ifndef BAT_SWARM_HPP
#define BAT_SWARM_HPP

#include "event.hpp"

class bat_swarm:public event{
    private:
    char symbol = 'B';

    public:
    bat_swarm();

    

    // Pure virtual function to warn player of event
    void percept() const;

    // Pure virtual function for encounter 
    void encounter(player& p) const;

    // Pure virtual function to return a debug symbol for the event (for debug mode)
    char get_debug_symbol() const;

};


#endif
