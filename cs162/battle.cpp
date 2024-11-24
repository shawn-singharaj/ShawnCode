#include "battle.hpp"
#include "pokemon.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;


battle::battle():pokemon1_1(), pokemon2_1(), pokemon1_2(), pokemon2_2(), current_turn(1), is_dead(false){
}

battle::battle(pokemon& pokemon1_1, pokemon& pokemon2_1, pokemon& pokemon1_2, pokemon& pokemon2_2){
    this->pokemon1_1 = pokemon1_1;
    this->pokemon2_1 = pokemon2_1;
    this->pokemon1_2 = pokemon1_2;
    this->pokemon2_2 = pokemon2_2;
    this->current_turn = 1;
    this->is_dead = false;
}


// swaps pokemon in for the other pokemon and returns the pointer for it to be used in the main battle function
pokemon* battle::swap_pokemon(int current_turn, pokemon* current_poke, pokemon& pokemon1_1, pokemon& pokemon2_1, pokemon& pokemon1_2, pokemon& pokemon2_2){
    if(current_turn == 1){
        if(current_poke->get_name() == pokemon1_1.get_name())
        {
            current_poke = &pokemon1_2;
            cout << endl << current_poke->get_name() << " has come in for " << pokemon1_1.get_name() << "!" << endl;
        }
        else{
            current_poke = &pokemon1_1;
            cout << endl << current_poke->get_name() << " has come in for " << pokemon1_2.get_name() << "!" << endl;
        }
    }
    else{
        if(current_poke->get_name() == pokemon2_1.get_name())
        {
            current_poke = &pokemon2_2;
            cout << endl << current_poke->get_name() << " has come in for " << pokemon2_1.get_name() << "!" << endl;
        }
        else{
            current_poke = &pokemon2_1;
            cout << endl << current_poke->get_name() << " has come in for " << pokemon2_2.get_name() << "!" << endl;
        }
    }
    return current_poke;
}

// Battle loop
void battle::battle_loop(pokemon& pokemon1_1, pokemon& pokemon2_1, pokemon& pokemon1_2, pokemon& pokemon2_2){
    pokemon* pokemon1 = &pokemon1_1;  // Pointer to initialize starting pokemons
    pokemon* pokemon2 = &pokemon2_1;  

    int choice = 3, num_heals1 = 1, num_heals2 = 1;
     
        do{ // Loop until one of the pokemon run out of HP
            do{// Menu loop for each trainer asking if the trainer wants to use an attack or heal
            cout << "\nIt's trainer " <<  current_turn << "'s turn.\n" << pokemon1->get_name() << " has " << pokemon1->get_hp() << "/" << pokemon1->get_max_hp();
            cout << " hp remaining\n" << pokemon2->get_name() << " has " << pokemon2->get_hp() << "/" << pokemon2->get_max_hp() << " hp remaining\n" << endl;
            cout << "What would you like to do?\n1. Use a move\n2. Heal (One use)\n3. Swap Pokemon" << endl << "Your choice: ";
            cin >> choice;
            if(choice == 1){ // if user uses a move, call the pokemon's use_move function 
                if(current_turn == 1){
                    pokemon1->use_move(*pokemon2);
                }
                else{
                    pokemon2->use_move(*pokemon1);
                }
            }
            else if (choice == 2){ // if user heals, call the pokemon's heal function
                if(current_turn == 1){
                    if(num_heals1 < 1){
                        cout << "\nOut of uses." << endl; // if the one heal is used
                        break;
                    }
                    pokemon1->heal(pokemon1->get_hp());
                    num_heals1--;
                }
                else{
                    if(num_heals2 < 1){
                        cout << "Out of uses." << endl; // if the one heal is used
                        break;
                    }
                    pokemon2->heal(pokemon2->get_hp());
                    num_heals2--;
                }
            }
            else if(choice == 3){ // swap current pokemon for other pokemon
                if(current_turn == 1){
                    if(pokemon1->get_name() == pokemon1_1.get_name())
                    {
                        if(pokemon1_2.get_hp() == 0){ // if other pokemon is dead
                            cout << pokemon1_2.get_name() << " cannot be swapped in." << endl;
                            break;
                        }
                        else{ // if it isnt, then swap
                            pokemon1 = swap_pokemon(1, pokemon1, pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2);
                        }
                    }
                    else{
                        if(pokemon1_1.get_hp() == 0){ // if other pokemon is dead
                            cout << pokemon1_1.get_name() << " cannot be swapped in." << endl;
                            break;
                        }
                        else{ // if it isnt, then swap
                            pokemon1 = swap_pokemon(1, pokemon1, pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2);
                        }
                    }                   
                }
                else{
                     if(pokemon2->get_name() == pokemon2_1.get_name())
                    {
                        if(pokemon2_2.get_hp() == 0){ // if other pokemon is dead
                            cout << pokemon2_2.get_name() << " cannot be swapped in." << endl;
                            break;
                        }
                        else{ // if it isnt, then swap
                            pokemon2 = swap_pokemon(2, pokemon2, pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2);
                        }
                    }
                    else{
                        if(pokemon2_1.get_hp() == 0){ // if other pokemon is dead 
                            cout << pokemon2_1.get_name() << " cannot be swapped in." << endl;
                            break;
                        }
                        else{  // if it isnt, then swap
                            pokemon2 = swap_pokemon(2, pokemon2, pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2);
                        }
                    }
                }
            }
            else{ // if user doesn't input 1 or 2
                cout << "Invalid choice, try again." << endl;
            }
            if(this->current_turn == 1){ // switch trainer's turn after the trainer uses a move or heals
                this->current_turn = 2;
            }
            else{
                this->current_turn = 1;
            }
        }while((choice != 1 && choice != 2 && choice != 3));
        if((pokemon1_1.get_hp() == 0 && pokemon1_2.get_hp() == 0) || (pokemon2_1.get_hp() == 0 && pokemon2_2.get_hp() == 0)){
            this->is_dead = true;
        }
        else if (pokemon1->get_hp() == 0) { // if current pokemon faints, swap if possible
            if (pokemon1 == &pokemon1_1 && pokemon1_2.get_hp() > 0) {
                pokemon1 = swap_pokemon(1, pokemon1, pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2); // Swap to second pokemon
            } 
            else if (pokemon1 == &pokemon1_2 && pokemon1_1.get_hp() > 0) {
                pokemon1 = swap_pokemon(1, pokemon1,  pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2); // Swap to first pokemon
            }
        }
        else if (pokemon2->get_hp() == 0) { // if current pokemon faints, swap if possible
            if (pokemon2 == &pokemon2_1 && pokemon2_2.get_hp() > 0) {
                pokemon2 = swap_pokemon(2, pokemon2,  pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2); // Swap to second pokemon
            }
            else if (pokemon2 == &pokemon2_2 && pokemon2_1.get_hp() > 0) {
                pokemon2 = swap_pokemon(2, pokemon2,  pokemon1_1, pokemon2_1, pokemon1_2, pokemon2_2); // Swap to first pokemon
            }
        }
    }while((is_dead == false));
    if(this->current_turn == 1){ // switch trainer's turn for winner declaration
        this->current_turn = 2;
    }
    else{
        this->current_turn = 1;
    }
    cout << endl << "Trainer " << current_turn << " wins!" << endl; // winner declaration
}

