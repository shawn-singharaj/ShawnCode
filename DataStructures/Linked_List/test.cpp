 /*
 * Author: Shawn Singharaj
 * Email: singhars@oregonstate.edu
 * Description: Test script for the implementation of the linked_list class
 */

/*
 * IMPORTANT: Do NOT modify this file (except to put your name and email above) unless
 * you complete the template extra credit. In that case, only modify it as
 * necessary to get the class template to work. The TAs will use a similar test
 * script to this one to grade your work. If you modify this one, then it will
 * no longer be reflective of what your actual grade will be, which may give you
 * a false sense of security.
 */

#include <iostream>
using std::cout;
using std::cin;


#include "linked_list.hpp"

/*********************************************************************
 ** Function: pause()
 ** Description: pauses program until the user presses enter
 ** Parameters: none
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ********************************************************************/
void pause() {
        cout << "\n\nPress <enter> to continue...";
        cin.clear();
        cin.ignore(256, '\n');
}

/*********************************************************************
 ** Function: main()
 ** Description: tests linked list functionality
 ** Parameters: int, char const *
 ** Pre-Conditions: none
 ** Post-Conditions: none
 ********************************************************************/
int main(int argc, char const *argv[]) {

	// constuct default list
	linked_list l;
	cout << "\n\nList successfully created!!\n\n";

	// test length of default (empty) list
	cout << "**********Test 1***********\n";
	cout << "Before adding nodes...\n";
	cout << "Testing get_length()\n";
	cout << "Expected: 0\n";
	cout << "Actual  : " << l.get_length() << "\n";
	if (l.get_length() == 0)
		cout << "Test 1 PASSED\n\n";
	else
		cout << "Test 1 FAILED\n\n";
	pause();

	// test push_front
	cout << "**********Test 2***********\n";
	cout << "Adding nodes...\n";
	cout << "Test 2.1: Testing push_front()\n";
	l.push_front(5);
	l.push_front(100);
	l.push_front(0);
	l.push_front(-8);
	l.push_front(16);
	cout << "Expected: 16 -8 0 100 5\n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nExpected length: 5\n";
	cout << "Actual length  : " << l.get_length() << "\n";
	cout << "Test 2.1 completed.\n";
	pause();

	// test pop_front
	cout << "Removing nodes...\n";
	cout << "Test 2.2: Testing pop_front()\n";
	l.pop_front();
	l.pop_front();
	l.pop_front();
	cout << "Print list...\n";
	cout << "Expected: 100 5\n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nExpected length: 2\n";
	cout << "Actual length  : " << l.get_length() << "\n";
	pause();

	// continue testing pop_front
	cout << "Continue removing...\n";
	l.pop_front();
	l.pop_front();
	l.pop_front(); //no more nodes, shouldn't remove anything 
	cout << "Print list...\n";
	cout << "Expected: \n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nExpected length: 0\n";
	cout << "Actual length  : " << l.get_length() << "\n";
	cout << "Test 2.2 completed.\n";
	pause();

	// test push_back
	cout << "Adding nodes...\n";
	cout << "Test 2.3: Testing push_back()\n";
	l.push_back(5);
	l.push_back(1);
	l.push_back(2);
	l.push_back(7);
	l.push_back(7919);
	cout << "Expected: 5 1 2 7 7919\n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nExpected length: 5\n";
	cout << "Actual length  : " << l.get_length() << "\n";
	cout << "Test 2.3 completed.\n";
	pause();

	// test pop_back
	cout << "Removing nodes...\n";
	cout << "Test 2.4: Testing pop_back()\n";
	l.pop_back();
	l.pop_back();
	cout << "Print list...\n";
	cout << "Expected: 5 1 2\n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nExpected length: 3\n";
	cout << "Actual length  : " << l.get_length() << "\n";
	pause();

	// continue testing pop_back
	cout << "Continue removing...\n";
	l.pop_back();
	l.pop_back();
	l.pop_back();
	l.pop_back(); //no more nodes, shouldn't remove anything 
	cout << "Print list...\n";
	cout << "Expected: \n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nExpected length: 0\n";
	cout << "Actual length  : " << l.get_length() << "\n";
	cout << "Test 2.4 completed.\n";
	pause();

	// insert nodes with push_front and push_back
	cout << "Adding nodes...\n";
	l.push_front(5);
	l.push_front(100);
	l.push_front(0);
	l.push_front(-8);
	l.push_front(16);
	l.push_back(5);
	l.push_back(1);
	l.push_back(2);
	l.push_back(7);
	l.push_back(7919);

	// test insert
	cout << "Test 2.5: Testing insert()\n";
	l.insert(11, 0);   // insert 11 at the front of the list
	l.insert(20, 100); // 100 is not a valid index, therefore 20 is not inserted
	l.insert(50, l.get_length()); // insert 50 at the end of the list
	l.insert(9, 5); // insert 9 at index 5 
	cout << "Expected: 11 16 -8 0 100 9 5 5 1 2 7 7919 50\n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nExpected length: 13\n";
	cout << "Actual length  : " << l.get_length() << "\n";
	cout << "Test 2.5 completed.\n";
	pause();

	// test remove
	cout << "Removing nodes...\n";
	cout << "Test 2.6: Testing remove()\n";
	l.remove(9);   // remove the node with index 9 (value 2) of the list
	l.remove(100); // 100 is not a valid index, therefore no node is removed
	l.remove(l.get_length() - 1); // remove the last node (value 50) in the list
	l.remove(0); // remove the first node (11) in the list 
	cout << "Expected: 16 -8 0 100 9 5 5 1 7 7919\n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nExpected length: 10\n";
	cout << "Actual length  : " << l.get_length() << "\n";
	cout << "Test 2.6 completed.\n";
	pause();

	// test sort_ascending
	cout << "**********Test 3***********\n";
	cout << "Sorting...\n";
	cout << "Test 3.1: Testing sort_ascending()\n";
	l.sort_ascending();
	cout << "Expected: -8 0 1 5 5 7 9 16 100 7919\n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nTest 3.1 completed.\n";
	pause();

	// test sort_descending
	cout << "Test 3.2: Testing sort_descending()\n";
	l.sort_descending();
	cout << "Expected: 7919 100 16 9 7 5 5 1 0 -8\n";
	cout << "Actual  :"; 
	l.print();
	cout << "\nTest 3.2 completed.\n";
	pause();

	// test clear
	cout << "**********Test 4***********\n";
	cout << "Tesing clear()\n";
	l.clear();
	cout << "Expected length: 0\n";
	cout << "Actual length  : " << l.get_length() << "\n";
	if (l.get_length() == 0)
		cout << "\nTest 4 PASSED\n";
	else
		cout << "\nTest 4 FAILED\n";

	// Run copy constructor
	linked_list l2 = l;

	// Run AOO
	l2 = l;

	// Run AOO on self
	l2 = l2;

	cout << "Run valgrind to check memory leaks/errors\n";

	return 0;
}
