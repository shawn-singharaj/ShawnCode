#ifndef CATALOG_H
#define CATALOG_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

// struct defs
struct Spell {
	string name;
	float success_rate;
	string effect;
};

struct Spellbook {
	string title;
	string author;
	int num_pages;
	int edition;
	int num_spells;
	float avg_success_rate;
	struct Spell *spells;
};

struct Wizard {
	string name;
	int id; // Used for logging in
	string password; // Used for logging in
	string position_title; // Used to restrict poison and death spells
	float beard_length;
};

// asks user for input file names
void prompt_for_file_name(string* wf, string* sf);

// allocate dynamic wizard array, assign values, and return it
Wizard* create_wizards(int size, ifstream& file);

// free wizard array
void delete_wizards(Wizard* wizlist);

// login function, returns the user's position
string login(Wizard* wizlist, int size);

/*
 * Function: create_spells
 * Description: Allocates a dynamic array of spells of the requested size and
 * 		returns a pointer that points to it
 * Parameters:
 * 		size (int): Size of dynamic array of spells to create
 * Returns: Pointer that points to dynamically allocated array of spells
 */
Spell* create_spells(int size);

/*
 * Function: read_spell_data
 * Description: Reads all of the information associated with a single spell
 * 		structure from the given spellbooks text file and returns a created
 * 		spell structure containing that information.
 * Parameters:
 * 		file (ifstream&): A reference to an std::ifstream that is open on
 * 		the input spellbooks text file and prepared to read information about
 * 		the next spell in a spellbook.
 * Returns: The created spell structure containing the information of the
 * 		next spell in the input file
 *
 * Hint: “ifstream& file” is a reference to a filestream object. You will
 * need to create one, open it up to read from the spellbooks text file, read
 * the information up to (but not including) the first spell, and then pass it
 * into this function to start reading spell data. Remember that information in
 * an input file must generally be read by your program in the order that it’s
 * presented in the file.
 */

Spell read_spell_data(ifstream& file);

/*
 * Function: create_spellbooks
 * Description: Allocates a dynamic array of spellbooks of the requested size
 * 		and returns a pointer that points to it.
 * Parameters:
 * 		size (int): Size of dynamic array of spellbooks to create
 * Returns: Pointer that points to dynamically allocated array of spellbooks
 */
Spellbook* create_spellbooks(int size);

/*
 * Function: read_spellbook_data
 * Description: Reads all of the information associated with a single spellbook
 * 		structure from the given spellbooks text file and returns a created
 * 		spellbook structure containing that information. Note that the
 * 		avg_success_rate member variable of the returned spellbook structure is
 * 		not contained in the text file, but rather will need to be computed as
 * 		the average (mean) success rate of all spells in the spellbook (i.e.,
 * 		add up the success rates of all spells in the spellbook, then divide by
 * 		the number of spells in the spellbook).
 * Parameters:
 * 		file (ifstream&): A reference to an std::ifstream that is open on
 * 		the input spellbooks text file and prepared to read information about
 * 		the next spellbook.
 * Returns: The created spellbook structure containing the information of the
 * 		next spellbook in the file
 *
 * Hint: This function will need to call the read_spell_data() function several
 * times in order to read all of the data associated with all of the spells in
 * the given spellbook.
 */
Spellbook read_spellbook_data(ifstream& file, string position);

// prints spells array to terminal
void print_spellbook(Spellbook& book, string position); 

// prints spells array to output file of user's choice
void outfile_spellbook(Spellbook& book, string position, string user_book);

// print spells to terminal without spellbook info
void print_spells(Spellbook& book, string position, string effect);

// print spells to output file of user's choice
void outfile_spells(Spellbook* book, string position, string effect, string user_book, int size);

/*
 * Function: delete_spells
 * Description: Deletes a given dynamic array of spells and updates its pointer
 * 		to be nullptr.
 * Parameters:
 * 		spells (Spell*&): A reference to the pointer that points to the dynamic
 * 			array of spells to be deleted.
 * Post-conditions: 1. Dynamic array of spells should be deleted. 2. spells
 * 		pointer parameter should be set to nullptr. Since this parameter is
 * 		passed by reference, the corresponding argument will be set to nullptr
 * 		as well.
 *
 * Hint: A dynamic array of spells is normally represented with a pointer of
 * type spell* pointing to the array’s base address, but here it’s spell*&.
 * That is, it’s a reference to a spell pointer. This is because the function
 * needs to be able to delete the array that the pointer points to AND modify
 * the pointer itself to be nullptr. In order to be able to modify the pointer
 * itself (which is an argument), the pointer needs to be passed by reference
 * (or passed by pointer---here we use a reference for simplicity).
 */
void delete_spells(Spell*& spells);

/*
 * Function: delete_spellbooks
 * Description: Deletes all of the dynamic memory associated with the given
 * 		array of spellbooks, including the arrays of spells inside each
 * 		spellbook. The size parameter indicates the size of the array of
 * 		spellbooks.
 * Parameters:
 * 		spellbooks (Spellbook*&): A reference to the pointer that points to the
 * 			dynamic array of spellbooks to be deleted
 * Post-conditions: 1. Dynamic arrays of spells within each spellbook should
 * 		be deleted (see hint). 2. Dynamic array of spellbooks should be deleted.
 * 		3. spellbooks pointer parameter should be set to nullptr. Since this
 * 		parameter is passed by reference, the corresponding argument will be set
 * 		to nullptr as well.
 *
 * Hint: This function should call the delete_spells() function several
 * times---once for each spellbook’s array of spells---and then proceed to
 * delete the array of spellbooks itself. spellbooks is passed by reference for
 * the same reason as in the delete_spells() function.
 */
void delete_spellbooks(Spellbook*& spellbooks, int size);


#endif
