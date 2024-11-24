#ifndef ROOM_HPP
#define ROOM_HPP

#include "event.hpp"

// Room interface
class room {
private: 
	event* e = nullptr; // the event pointer
	
public:
	room(); // constructor

	void set_event(event* e); // setter
	event* get_event() const; // getter
		
};

#endif
