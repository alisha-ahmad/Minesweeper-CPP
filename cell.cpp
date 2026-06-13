#include "cell.h"
// #include <stdio.h>
// #include <ctime>
// #include <cstdlib>

//constructors
Cell::Cell(): val(0), flagged(false), visible(false) {}
Cell::Cell(int i): val(i), flagged(false), visible(false) {}
Cell::Cell(const Cell &other): val(other.val), flagged(other.flagged), visible(other.visible) {}
//asignment operator
Cell& Cell::operator=(const Cell &other){
    if (this != &other){
        val = other.val;
        flagged = other.flagged;
        visible = other.visible;
    }
    return *this;
}

//getters
bool Cell::is_mine() const { return val == -1; }
bool Cell::is_flagged() const {return flagged; }
bool Cell::is_visible() const { return visible; }
int Cell::get_val() const { return val; }

//setters
void Cell::set_val(int i){ val = i; }
void Cell::set_mine(){ val = -1; }
void Cell::set_flag(){ flagged = true; }
void Cell::remove_flag(){ flagged = false; }
void Cell::make_visible(){ visible = true; }
 