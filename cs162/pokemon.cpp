#include "pokemon.hpp"
#include "move.hpp"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ceil;

// default constructor
pokemon::pokemon():name(""), type(""), hp(0), max_hp(0), attack(0), defense(0), num_moves(0), Moves(nullptr){
}

// non-default constructor
pokemon::pokemon(string n, string t, int h, int a, int d, int nm){
this->name = n;
this->type = t;
this->hp = h;
this->max_hp = this->hp;
this->attack = a;
this->defense = d;
this->num_moves = nm;
}

// Allocates memory and assigns value to Moves array, returns the pointer
move* pokemon::set_Move(int nm, move move1, move move2){
    this->Moves = new move [nm];
    
    Moves[0] = move1;
    Moves[1] = move2;
    return Moves;
}

// free the Moves array from memory
pokemon::~pokemon(){
    if(this->Moves != nullptr){
        delete [] this->Moves;
        this->Moves = nullptr;
    }
}

// copy constructor
pokemon::pokemon(const pokemon& p){
this->name = p.name;
this->type = p.type;
this->hp = p.hp;
this->max_hp = p.hp;
this->attack = p.attack;
this->defense = p.defense;
this->num_moves = p.num_moves;

// deep copy for Moves array
if(p.Moves != nullptr){
    this->Moves = new move[this->num_moves];
    for(int i = 0; i < this->num_moves; i++){
        this->Moves[i] = p.Moves[i];
    }
}
else{
    this->Moves = nullptr;
}
}

// Assignment operator overload
pokemon& pokemon::operator=(const pokemon& p){
    if(this == &p){
        return *this;
    }

    if(this->Moves != nullptr){
        delete [] this->Moves;
    }
      
    this->name = p.name;
    this->type = p.type;
    this->hp = p.hp;
    this->max_hp = p.max_hp;
    this->attack = p.attack;
    this->defense = p.defense;
    this->num_moves = p.num_moves;

    // deep copy
     if(p.Moves != nullptr){
        this->Moves = new move[this->num_moves];
        for(int i = 0; i < this->num_moves; ++i) {
            this->Moves[i] = p.Moves[i]; 
        }
    } 
    else{
        this->Moves = nullptr;
    }

    return *this;   
}

// getters
string pokemon::get_name() const{
    return this->name;
}
string pokemon::get_type() const{
    return this->type;
}
int pokemon::get_hp() const{
    return this->hp;
}
int pokemon::get_max_hp() const{
    return this->max_hp;
}
int pokemon::get_defense() const{
    return this->defense;
}

move* pokemon::get_Moves(int idx) const{
    if(idx < this->num_moves){
          return &this->Moves[idx];
     }
     return nullptr;
 }

// setter
void pokemon::set_hp(int hp){
    this->hp = hp;
}

// Takes parameters for the opposing pokemon to get it's type and the user's move choice
// and takes the move's type and returns a double that is the damage multiplier based off type interaction
double pokemon::type_interact(pokemon opp_poke, int choice){
    if((Moves[choice - 1].get_type() == "Water" && opp_poke.get_type() == "Fire") ||
      (Moves[choice - 1].get_type() == "Fire" && opp_poke.get_type() == "Grass") ||
      (Moves[choice - 1].get_type() == "Grass" && opp_poke.get_type() == "Water") ||
      (Moves[choice - 1].get_type() == "Flying" && opp_poke.get_type() == "Grass")){
        return 2.0; // return 2 if the selected move is strong against the other pokemon
    }    
    else if((Moves[choice - 1].get_type() == "Water" && opp_poke.get_type() == "Grass") || 
      (Moves[choice - 1].get_type() == "Fire" && opp_poke.get_type() == "Water") ||
      (Moves[choice - 1].get_type() == "Grass" && opp_poke.get_type() == "Fire") ||
      (Moves[choice - 1].get_type() == "Grass" && opp_poke.get_type() == "Flying")){
        return 0.5; // return 1/2 if the selected move is weak against the other pokemon
      }
    return 1.0;    // if there is no type interaction, return 1
}

// Takes the type interaction above, the random multiplier generated, the random critical hit chance generated, the
// user's move choice and the opposing pokemon and returns the calculated damage from the document
int pokemon::damage_calc(double ti, double rm, int rc, int choice, pokemon opp_poke){
    int damage = ceil((static_cast<double>(attack) / opp_poke.get_defense()) * ti * Moves[choice - 1].get_damage() * rm * rc); // damage calculation
    Moves[choice - 1].set_num_uses(Moves[choice - 1].get_num_uses() - 1); // subtract number of uses by 1
    return damage; // return the calculated damage
}

// Prompts the user to use one of the moves and calls damage_calc then calls the poke_attack to get the new HP value of the
// opposing pokemon
void pokemon::use_move(pokemon &opp_poke){
    int choice = 3, rand_crit = 0;
    double rand_mult = 0.0;
    do{ // loop while the user inputs an invalid number or selects a move that is out of uses
        rand_crit = rand() % 100; // generates a number 0-99
        if(rand_crit < 10){ // 10% chance there is a critical hit
            rand_crit = 3;
        }
        else{ // 90% chance there is not a critical hit
            rand_crit = 1;
        }
        double rand_mult = 0.8 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) / (1.2 - 0.8)); // generates a number 0.8-1.2
        do{// menu loop
            cout << "\nWhich move would you like to use?\n1. Scratch (" << Moves[0].get_num_uses() << " uses remaining)\n";
            cout << "2. " << Moves[1].get_name() << " (" << Moves[1].get_num_uses() << " uses remaining)" << endl << "Your choice: ";
            cin >> choice;
            if(choice == 1 || choice == 2){
                if(Moves[choice - 1].get_num_uses() == 0){
                    cout << Moves[choice - 1].get_name() << " has no uses remaining!" << endl; // if selected move is out of uses, loop again
                    continue; 
                }
                else{ 
                    double type_interaction = type_interact(opp_poke, choice); // call the type interaction multiplier
                    // output damage calculations
                    cout << "Performing damage calculation:\nValue of type_interaction: " << type_interaction;
                    cout << "\nValue of random_multiplier: " << rand_mult; 
                    cout << "\nValue of random_critical: " << rand_crit;
                    int damage = damage_calc(type_interaction, rand_mult, rand_crit, choice, opp_poke); // call damage calculation
                    cout << "\nValue of damage: " << damage << endl;
                    poke_attack(opp_poke, damage); // subtract opposing pokemon's HP
                    break;
                }
            }
            else{
            cout << "Invalid input, try again." << endl; // if user doesn't input 1 or 2
            }
        }while(true);
    }while(choice != 1 && choice != 2);
}

// Adds 10 to the pokemon's HP
void pokemon::heal(int hp){
    this->hp += 10;
    if(this->hp > this->max_hp){ // if HP goes above the maximum HP, set it to full health
        this->hp = this->max_hp;
    }
    cout << name << " used a potion! HP is now at " << this->hp << "/" << this->max_hp << endl; 
}

// Takes the damage number and subtracts it to the opposing pokemon's HP
void pokemon::poke_attack(pokemon &opp_poke, int damage){
    int new_hp = opp_poke.get_hp() - damage; // subtract current HP by damage calc
    if(new_hp < 0){
        new_hp = 0; // HP can't go below 0
        cout << endl << opp_poke.get_name() << " has fainted!" << endl; // the other pokemon has fainted
    }
    opp_poke.set_hp(new_hp); // sets HP to 0
}