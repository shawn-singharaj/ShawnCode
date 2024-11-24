#ifndef PLAYER_HPP
#define PLAYER_HPP

class player{
private:
    int location_x = 0; // tracks player location, number of arrows, if they win/lost, have gold, and confused
    int location_y = 0;
    int num_arrows = 0;
    bool check_win = 0;
    bool check_loss = 0;
    bool has_gold = 0;
    bool is_confused = 0;
public:
    player(int x, int y); // constructor

    int get_location_x() const; // getters
    int get_location_y() const;
    int get_num_arrows() const;
    bool get_check_win() const;
    bool get_check_loss() const;
    bool get_has_gold() const;
    bool get_is_confused () const;

    void set_is_confused(bool is_confused); // setters
    void set_has_gold(bool has_gold);
    void set_check_win(bool check_win);
    void set_check_loss(bool check_loss);
    void set_num_arrows(int num_arrows);
    
    void move_right(); // moves player's location
    void move_left();
    void move_up();
    void move_down();

};



#endif