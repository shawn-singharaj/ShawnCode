#include <iostream>

#include "player.hpp"

using std::cout;

player::player(int x, int y): location_x(x), location_y(y), num_arrows(0), check_win(0), check_loss(0), has_gold(0){

}

int player::get_location_x() const{
    return this->location_x;
}
int player::get_location_y() const{
    return this->location_y;
}
int player::get_num_arrows() const{
    return this->num_arrows;
}

bool player::get_check_win() const{
    return this->check_win;
}
bool player::get_check_loss() const{
    return this->check_loss;
}

bool player::get_has_gold() const{
    return this->has_gold;
}

bool player::get_is_confused () const{
    return this->is_confused;
}

void player::set_is_confused(bool is_confused){
    this->is_confused = is_confused;
}

void player::set_has_gold(bool has_gold){
    this->has_gold = has_gold;
}

void player::set_check_win(bool check_win){
    this->check_win = check_win;
}

void player::set_check_loss(bool check_loss){
    this->check_loss = check_loss;
}
    
void player::set_num_arrows(int num_arrows){
    this->num_arrows = num_arrows;
}

void player::move_right(){
    this->location_y++;
}
void player::move_left(){
    this->location_y--;
}
void player::move_up(){
    this->location_x--;
}
void player::move_down(){
    this->location_x++;
}

