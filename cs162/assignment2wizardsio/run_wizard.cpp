#include "catalog.hpp"
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

int main()
{
	string wizard_fname, spell_fname, spellbook_name, spell_effect, user_file; // declare strings
	prompt_for_file_name(&wizard_fname, &spell_fname); // calls function that prompts user for file names
	ifstream wiz_file; // open files
	ifstream spell_file;
	wiz_file.open(wizard_fname);
	spell_file.open(spell_fname);
	if (!wiz_file.is_open()) { // if the files weren't open, error and terminate
		cout << wizard_fname << " could not be opened.\n";
		return -1;
	}
	if (!spell_file.is_open()) {
		cout << spell_fname << " could not be opened.\n";
		return -1;
	}
	// declare ints
	int wiz_size, spell_size, user_choice;
	wiz_file >> wiz_size; // read in number of wizards
	spell_file >> spell_size; // read in number of spellbooks
	Wizard* wiz_list = create_wizards(wiz_size, wiz_file); // function call to allocate and fill wizards array

	string position = login(wiz_list, wiz_size); // function call to  log user in and return their position
	
	Spellbook* spell_array = create_spellbooks(spell_size); // function call to allocate struct array for spellbooks
	for(int i = 0; i < spell_size; i++) 
		spell_array[i] = read_spellbook_data(spell_file, position); // function call to fill array with all spellbook info
	
	//cout << spell_array[0].spells[0].effect;

	do{ // menu loop		
		cout << "Which option would you like to choose?\n1. Display all";
		cout << "\n2. Search spellbook by its name\n3. Search spells by their effect";
		cout << "\n4. Quit\nYour choice: ";
		cin >> user_choice;
		bool pass = false; 
		switch(user_choice){
			case 1:
				for(int i = 0; i < spell_size; i++)
					print_spellbook(spell_array[i], position); // function call to print whole spell array
				break;
			case 2:
				int book_num;
				do{
				cout << "\nEnter a spellbook name: ";
				cin >> spellbook_name;
				for(int i = 0; i < spell_size; i++){
					if(spellbook_name == spell_array[i].title){ // if user input == one of the spellbook titles
						book_num = i; // store that current index positon to be used later
						pass = true; // break out of do while loop
						break;
					}
				}
				if (!pass) { // if no valid spellbook was found
       				cout << "Invalid input, try again." << endl;
   				}
				}while(pass == false); // loop until valid spellbook name is inputted
				int print_choice;
				do{ // second menu
					cout << "\nHow would you like the information displayed?\n1. Print to screen";
					cout << "\n2. Print to file\n";
					cin >> print_choice;	
					switch(print_choice){
						case 1: 
							print_spellbook(spell_array[book_num], position);// function call to print to terminal
							break;
						case 2:
							cout << "Enter file name: ";
							cin >> user_file;
							outfile_spellbook(spell_array[book_num], position, user_file); // function call to print to output file
							break;
						default:
							cout << "Invalid input, try again." << endl;
							break;
					}	
				}while(print_choice != 1 && print_choice != 2); // loop until user inputs 1 or 2
				break;
			case 3:
				do{
					cout << "\nEnter spell effect: ";
					cin >> spell_effect;
					if(spell_effect != "fire" && spell_effect != "bubble" && spell_effect != "memory_loss" 
					&& spell_effect != "death" && spell_effect != "poison") // if user inputs invalid spell effect
						cout << "Invalid spell effect, try again." << endl;
					// if student inputs restricted effect
					else if (position == "Student" && (spell_effect == "death" || spell_effect == "poison")) 
						cout << "Invalid spell effect, try again." << endl;

					else{ // second menu
						do{
						cout << "\nHow would you like the information displayed?\n1. Print to screen";
						cout << "\n2. Print to file\n";
						cin >> print_choice;	
						switch(print_choice){
							case 1: 
								for(int i = 0; i < spell_size; i++)
								print_spells(spell_array[i], position, spell_effect);	// function call to print spells to terminal
								break;
							case 2:
								cout << "Enter file name: ";
								cin >> user_file; // function call to print spells to output file
								outfile_spells(spell_array, position, spell_effect, user_file, spell_size);
								break;
							default:
								cout << "Invalid input, try again." << endl;
								break;
						}	
					}while(print_choice != 1 && print_choice != 2); // loop if user inputs something other than 1 or 2
					pass = true;
					}
				}while(pass == false); // loop until user inputs valid effect
				break;
			case 4: // quit
				break;
			default: // if user doesn't input 1-4 
				cout << "Invalid input, try again." << endl;
				break;
		}
	}while(user_choice != 4); // loop until user quits
	for(int i = 0; i < spell_size; i++) 
		delete_spells(spell_array[i].spells);
	delete_spellbooks(spell_array, spell_size); // function call to free memory from spells array
	wiz_file.close(); // close files
	spell_file.close();
	delete_wizards(wiz_list); // function call to free memory from wizards array

	return 0;
}
