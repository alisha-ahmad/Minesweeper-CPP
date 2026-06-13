#ifndef BOARD_H
#define BOARD_H

#include "cell.h"

class Board{
private:
    Cell** grid;
    int rows, cols, mines;
public:
    Board();
    Board(int r, int c, int m);
    Board(const Board& other);
    Board& operator=(const Board& other);

    int get_rows() const;
    int get_cols() const;
    int get_mines() const;
    Cell** get_grid() const;

    void init_mines(int ir, int ic);    //first click(ir,ic) safe 
    void fill_values();

    ~Board();


};


#endif

// init_mines()
// fill_values()
// get_cell()
// get_rows()
// get_cols()