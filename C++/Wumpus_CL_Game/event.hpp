#ifndef EVENT_HPP
#define EVENT_HPP

#include "player.hpp"

// Event interface
class event {
private:
    char symbol = ' ';
public:
    event(char symbol); // constructor

	// Virtual destructor for proper cleanup in derived classes
    virtual ~event();

    // Pure virtual function for percept (what the player perceives when nearby)
    virtual void percept() const = 0;

    // Pure virtual function for encounter (what happens when the player encounters the event)
    virtual void encounter(player& p) const = 0;

    // Pure virtual function to return a debug symbol for the event (for debug mode)
    virtual char get_debug_symbol() const = 0;
};

#endif
