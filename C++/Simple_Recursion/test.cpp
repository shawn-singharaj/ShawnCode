/*
 * Author: Shawn Singharaj
 * Email: singhars@oregonstate.edu
 * Description: Test script for ways_to_top() implementation
 */

#include <iostream>
using std::cout;
using std::endl;

#include "stairs.hpp"

/*********************************************************************
 ** Function: main()
 ** Description: outputs ways to the top of different sized staicases
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ********************************************************************/
int main() {
	cout << endl << "3-Step Staircase: " << ways_to_top(3) <<
		" ways" << endl; // Should prints "4 ways"

	cout << "4-Step Staircase: " << ways_to_top(4) << " ways" <<
		endl; // Should print "7 ways"

	cout << "5-Step Staircase: " << ways_to_top(5) << " ways" <<
		endl; // Should print "13 ways"

	cout << "6-Step Staircase: " << ways_to_top(6) << " ways" <<
		endl; // Should print "24 ways"

	cout << "7-Step Staircase: " << ways_to_top(7) << " ways" <<
		endl << endl; // Should print "44 ways"
}
