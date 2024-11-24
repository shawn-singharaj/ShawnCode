#include <iostream>

#include "startup.hpp"
#include "pokemon.hpp"
#include "move.hpp"


using std::cout;
using std::cin;
using std::endl;
using std::string;

// prompt first trainer for pokemon choice and return as string
string prompt_first_pokemon() {
	int choice;
	do {
		cout << "Trainer 1: Which pokemon would you like?" <<
			endl;
		cout << "1. Charmander" << endl;
		cout << "2. Squirtle" << endl;
		cout << "3. Bulbasaur" << endl;
		cout << "4. Pidgey" << endl;
		cout << endl << "Your choice: ";
		cin >> choice;

		cout << endl;

		if (choice < 1 || choice > 4) {
			cout << "Invalid option!" <<
				endl << endl;
		}
	} while(choice < 1 || choice > 4);
	string poke_choice;
	switch(choice){
		case 1:
		poke_choice = "Charmander";
		break;
		case 2:
		poke_choice = "Squirtle";
		break;
		case 3:
		poke_choice = "Bulbasaur";
		break;
		default:
		poke_choice = "Pidgey";
	}

	return poke_choice;
}

// prompt second trainer for pokemon choice and return the choice as a string
string prompt_second_pokemon(string blacklisted_pokemon) {
	int choice;
	do {
		cout << "Trainer 2: Which pokemon would you like?" <<
			endl;

		if (blacklisted_pokemon == "Charmander") {
			cout << "1. Squirtle" << endl;
			cout << "2. Bulbasaur" << endl;
			cout << "3. Pidgey" << endl;
		} else if (blacklisted_pokemon == "Squirtle") {
			cout << "1. Charmander" << endl;
			cout << "2. Bulbasaur" << endl;
			cout << "3. Pidgey" << endl;
		} else if(blacklisted_pokemon == "Bulbasaur"){
			cout << "1. Charmander" << endl;
			cout << "2. Squirtle" << endl;
			cout << "3. Pidgey" << endl;
		}
		else{
			cout << "1. Charmander" << endl;
			cout << "2. Squirtle" << endl;
			cout << "3. Bulbasaur" << endl;
		}

		cout << endl << "Your choice: ";
		cin >> choice;

		cout << endl;

		if (choice < 1 || choice > 3) {
			cout << "Invalid option!" <<
				endl << endl;
		}
	} while(choice < 1 || choice > 3);
	string poke_choice;
	if(blacklisted_pokemon == "Charmander") {
		if(choice == 1){
			poke_choice = "Squirtle";
		}
		else if(choice == 2){
			poke_choice = "Bulbasaur";
		}
		else{
			poke_choice = "Pidgey";
		}
	} 
	else if(blacklisted_pokemon == "Squirtle"){
		if(choice == 1){
			poke_choice = "Charmander";
		}
		else if(choice == 2){
			poke_choice = "Bulbasaur";
		}
		else{
			poke_choice = "Pidgey";
		}
	}
	else if(blacklisted_pokemon == "Bulbasaur"){
		if(choice == 1){
			poke_choice = "Charmander";
		}
		else if(choice == 2){
			poke_choice = "Squirtle";
		}
		else{
			poke_choice = "Pidgey";
		}
	}
	else{
		if(choice == 1){
			poke_choice = "Charmander";
		}
		else if(choice == 2){
			poke_choice = "Squirtle";
		}
		else{
			poke_choice = "Bulbasaur";
		}
	}
	return poke_choice;
}

// prompt first trainer for third pokemon, fourth pokemon assigned to second trainer
void prompt_third_pokemon(string bp1, string bp2, string* p1_2, string* p2_2){
	int choice;
	do {
		cout << "Trainer 1: Which pokemon would you like?" << endl;

		if((bp1 == "Charmander" && bp2 == "Squirtle")||(bp1 == "Charmander" && bp2 == "Squirtle")) {
			cout << "1. Bulbasaur" << endl;
			cout << "2. Pidgey" << endl;
		}
		else if((bp1 == "Squirtle" && bp2 == "Bulbasaur")||(bp1 == "Bulbasaur" && bp2 == "Squirtle")){
			cout << "1. Charmander" << endl;
			cout << "2. Pidgey" << endl;
		}
		else if((bp1 == "Charmander" && bp2 == "Bulbasaur")||(bp1 == "Bulbasaur" && bp2 == "Charmander")){
			cout << "1. Squirtle" << endl;
			cout << "2. Pidgey" << endl;
		}
		else if((bp1 == "Charmander" && bp2 == "Pidgey")||(bp1 == "Pidgey" && bp2 == "Charmander")){
			cout << "1. Squirtle" << endl;
			cout << "2. Bulbasaur" << endl;
		}
		else if((bp1 == "Squirtle" && bp2 == "Pidgey")||(bp1 == "Pidgey" && bp2 == "Squirtle")){
			cout << "1. Charmander" << endl;
			cout << "2. Bulbasaur" << endl;
		}
		else if((bp1 == "Bulbasaur" && bp2 == "Pidgey")||(bp1 == "Pidgey" && bp2 == "Bulbasaur")){
			cout << "1. Charmander" << endl;
			cout << "2. Squirtle" << endl;
		}
		
		cout << endl << "Your choice: ";
		cin >> choice;

		cout << endl;

		if (choice < 1 || choice > 2) {
			cout << "Invalid option!" <<
				endl << endl;
		}
	} while(choice < 1 || choice > 2);
	if((bp1 == "Charmander" && bp2 == "Squirtle")||(bp1 == "Charmander" && bp2 == "Squirtle")) {
			if(choice == 1){
				*p1_2 = "Bulbasaur";
				*p2_2 = "Pidgey";
			}
			else{
				*p1_2 = "Pidgey";
				*p2_2 = "Bulbasaur";
			}
		}
		else if((bp1 == "Squirtle" && bp2 == "Bulbasaur")||(bp1 == "Bulbasaur" && bp2 == "Squirtle")){
			if(choice == 1){
				*p1_2 = "Charmander";
				*p2_2 = "Pidgey";
			}
			else{
				*p1_2 = "Pidgey";
				*p2_2 = "Charmander";
			}
		}
		else if((bp1 == "Charmander" && bp2 == "Bulbasaur")||(bp1 == "Bulbasaur" && bp2 == "Charmander")){
			if(choice == 1){
				*p1_2 = "Squirtle";
				*p2_2 = "Pidgey";
			}
			else{
				*p1_2 = "Pidgey";
				*p2_2 = "Squirtle";
			}
		}
		else if((bp1 == "Charmander" && bp2 == "Pidgey")||(bp1 == "Pidgey" && bp2 == "Charmander")){
			if(choice == 1){
				*p1_2 = "Squirtle";
				*p2_2 = "Bulbasaur";
			}
			else{
				*p1_2 = "Bulbasaur";
				*p2_2 = "Squirtle";
			}
		}
		else if((bp1 == "Squirtle" && bp2 == "Pidgey")||(bp1 == "Pidgey" && bp2 == "Squirtle")){
			if(choice == 1){
				*p1_2 = "Charmander";
				*p2_2 = "Bulbasaur";
			}
			else{
				*p1_2 = "Bulbasaur";
				*p2_2 = "Charmander";
			}
		}
		else if((bp1 == "Bulbasaur" && bp2 == "Pidgey")||(bp1 == "Pidgey" && bp2 == "Bulbasaur")){
			if(choice == 1){
				*p1_2 = "Charmander";
				*p2_2 = "Squirtle";
			}
			else{
				*p1_2 = "Squirtle";
				*p2_2 = "Charmander";
			}
		}
	}


// takes the string from above functions and initializes objects 
pokemon assign_pokemon(string poke_choice){
	move scratch("Scratch", "Normal", 3, 10000);
		if(poke_choice == "Charmander"){
			move ember("Ember", "Fire", 5, 3);
			pokemon charmander("Charmander", "Fire", 18, 6, 4, 2);
			move* char_moves = charmander.get_Moves(2);
			charmander.set_Move(2, scratch, ember);
			return charmander;
		}
		else if(poke_choice == "Squirtle"){
			move water_gun("Water Gun", "Water", 5, 3);
			pokemon squirtle("Squirtle", "Water", 22, 4, 6, 2);
			move* squirt_moves = squirtle.get_Moves(2);
			squirtle.set_Move(2, scratch, water_gun);
			return squirtle;
		}
		else if(poke_choice == "Bulbasaur"){
			move vine_whip("Vine Whip", "Grass", 5, 3);
			pokemon bulbasaur("Bulbasaur", "Grass", 20, 5, 5, 2);
			move* bulb_moves = bulbasaur.get_Moves(2);
			bulbasaur.set_Move(2, scratch, vine_whip);
			return bulbasaur;
		}
		else{
			move wing_attack("Wing Attack", "Flying", 5, 3);
			pokemon pidgey("Pidgey", "Flying", 18, 4, 4, 2);
			move* pidgey_moves = pidgey.get_Moves(2);
			pidgey.set_Move(2, scratch, wing_attack);
			return pidgey;
		}
}
