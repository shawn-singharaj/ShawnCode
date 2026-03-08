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

// Function definitions 
void prompt_for_file_name(string* wf, string* sf){
    cout << "Enter name of file for wizard information: ";
    cin >> *wf;
    cout << "Enter name of file for spellbook information: ";
    cin >> *sf;
}

Wizard* create_wizards(int size, ifstream& file){
    Wizard* wizlist = new Wizard[size]; // allocate memory

    for(int i = 0; i < size; i++){  // assign values to wizard struct array
        file >> wizlist[i].name;
        file >> wizlist[i].id; 
	    file >> wizlist[i].password; 
        file >> wizlist[i].position_title; 
        file >> wizlist[i].beard_length;
    }
    return wizlist;
}

void delete_wizards(Wizard* wizlist){
    delete [] wizlist; // free memory
}

string login(Wizard* wizlist, int size){
    int user_id;
    int attempts = 0;
    string user_pass;

    while(attempts < 3){ // loop 3 times
        cout << "\nPlease enter your ID: ";
        cin >> user_id;
        cout << "Please enter your password: ";
        cin >> user_pass;
        for(int i = 0; i < size; i++){
            if(user_id == wizlist[i].id && user_pass == wizlist[i].password){ // if successful login, output wizard info
                cout << "\nWelcome, " << wizlist[i].name << endl;
                cout << "ID: " << wizlist[i].id << endl;
                cout << "Status: " << wizlist[i].position_title << endl;
                cout << "Beard Length: " << wizlist[i].beard_length << endl << endl;
                return wizlist[i].position_title;
            }
        }
        cout << "Incorrect ID or Password. You are at " << attempts + 1 << "/3 attempts."<< endl; // if incorrect login info
        attempts++;
    }
    cout << "Too many failed attempts." << endl; 
    exit(1); // terminate program if loop breaks
}

Spell* create_spells(int size){
    return new Spell[size]; // allocate memory for spell array
}

Spell read_spell_data(ifstream& file){
    Spell spell_data; // spell struct info assigned
    file >> spell_data.name;
	file >> spell_data.success_rate;
	file >> spell_data.effect;

    return spell_data;
}

Spellbook* create_spellbooks(int size){
    return new Spellbook[size]; // allocate memory for spell array
}

Spellbook read_spellbook_data(ifstream& file, string position){
    Spellbook spellbook_data;
    float avg = 0.0;
	file >> spellbook_data.title; // assign values for the spellbook struct array
    file >> spellbook_data.author;
	file >> spellbook_data.num_pages;
	file >> spellbook_data.edition;
	file >> spellbook_data.num_spells;

    spellbook_data.spells = new Spell[spellbook_data.num_spells]; // allocate memory for individual spells
    
    for(int i = 0; i < spellbook_data.num_spells; i++){ // assign values for spell struct array
        file >> spellbook_data.spells[i].name;
        file >> spellbook_data.spells[i].success_rate;
        file >> spellbook_data.spells[i].effect;
        avg += spellbook_data.spells[i].success_rate;
    } 
    spellbook_data.avg_success_rate = avg / spellbook_data.num_spells;

    return spellbook_data;
}

void print_spellbook(Spellbook& book, string position){
    int redacted_spells = 0;
    float success_rate = 0.0;
    for(int i = 0; i < book.num_spells; i++) // count restricted spells and add their success rates for new avg
        if(position == "Student" && (book.spells[i].effect == "death" || book.spells[i].effect == "poison")){
            redacted_spells++;
            success_rate += book.spells[i].success_rate;
        }
            
    cout << "\n\nTitle: " << book.title;
    cout << "\nAuthor: " << book.author;
	cout << "\nEdition: " << book.edition;
    cout << "\nNumber of pages: " << book.num_pages;
	cout << "\nNumber of spells: " << (book.num_spells - redacted_spells); // new total of spells
	cout << "\nAverage success rate of spells: " << (((book.avg_success_rate * book.num_spells) - success_rate)); // new avg

    for(int i = 0; i < book.num_spells-1; i++){ // sort spells in descending order of success rate
         for(int j = 0; j < book.num_spells-i-1; j++){
            if(book.spells[j].success_rate < book.spells[j+1].success_rate){
                    Spell temp = book.spells[j];
                    book.spells[j] = book.spells[j+1];
                    book.spells[j+1] = temp;
            }
        }   
    }       

    for(int i = 0; i < book.num_spells; i++){ // output spells
        if(position == "Student" && (book.spells[i].effect == "death" || book.spells[i].effect == "poison"))
            continue; // skip restricted spells for students
        else{
            cout << "\n\tSpell name: " << book.spells[i].name; 
            cout << "\n\tSuccess Rate: " << book.spells[i].success_rate;
            cout << "\n\tEffect: " << book.spells[i].effect;
        }        
    }
    cout << endl;
}

void print_spells(Spellbook& book, string position, string effect){
     for(int i = 0; i < book.num_spells; i++){
        if(position == "Student" && (book.spells[i].effect == "death" || book.spells[i].effect == "poison"))
            continue; // skip restricted spells for students
        else if (book.spells[i].effect == effect){ // output spells of the user's input
            cout << "\n\tSpell name: " << book.spells[i].name; 
            cout << "\n\tSuccess Rate: " << book.spells[i].success_rate;
            cout << "\n\tEffect: " << book.spells[i].effect;
        }        
    }
}

void outfile_spells(Spellbook* book, string position, string effect, string user_book, int size){
    ofstream file; // open output file
    file.open(user_book);
    for(int i = 0; i < size; i++){ // print the spells
        for(int j = 0; j < book[i].num_spells; j++){
            if(position == "Student" && (book[i].spells[j].effect == "death" || book[i].spells[j].effect == "poison"))
                continue; 
            else if (book[i].spells[j].effect == effect){
                file << "\n\tSpell name: " << book[i].spells[j].name; 
                file << "\n\tSuccess Rate: " << book[i].spells[j].success_rate;
                file << "\n\tEffect: " << book[i].spells[j].effect;
            }        
        }
    }
    file.close();    
}

void outfile_spellbook(Spellbook& book, string position, string user_book){
    ofstream file; // open output file
    file.open(user_book);
    int redacted_spells = 0;
    float success_rate = 0.0;
    for(int i = 0; i < book.num_spells; i++) // count restricted spells
        if(position == "Student" && (book.spells[i].effect == "death" || book.spells[i].effect == "poison")){
            redacted_spells++;
            success_rate += book.spells[i].success_rate;
        }
            
    // print spellbook info
    file << "\n\nTitle: " << book.title; 
    file << "\nAuthor: " << book.author;
	file << "\nEdition: " << book.edition;
    file << "\nNumber of pages: " << book.num_pages;
	file << "\nNumber of spells: " << (book.num_spells - redacted_spells); // new spell total
	file << "\nAverage success rate of spells: " << (((book.avg_success_rate * book.num_spells) - success_rate)); // new avf

    for(int i = 0; i < book.num_spells; i++){
        if(position == "Student" && (book.spells[i].effect == "death" || book.spells[i].effect == "poison"))
            continue; // skip restricted spells for students
        else{// print spell info
            file << "\n\tSpell name: " << book.spells[i].name; 
            file << "\n\tSuccess Rate: " << book.spells[i].success_rate;
            file<< "\n\tEffect: " << book.spells[i].effect;
        }        
    }
    file.close();
}

void delete_spells(Spell*& spells){
    delete [] spells; // free spell struct array
}

void delete_spellbooks(Spellbook*& spellbooks, int size){      
    delete [] spellbooks;
    spellbooks = nullptr;
}
