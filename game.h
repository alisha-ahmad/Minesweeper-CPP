#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game{
private:
    Board *board;
    bool gameover, win;

    void rev_zero(int i, int j);
    bool chord(int ir, int ic);
    int count_flags(int i, int j);

public:
    Game();
    Game(Board &b);
    Game(const Game& other);
    Game& operator=(const Game& other);

    void reveal(int i, int j);
    void toggleFlag(int i, int j);
    void check_cell(int i, int j);


    Board* get_board();
    bool is_gameover();
    bool is_win();
    int get_val(int i, int j);
    bool is_visible(int i, int j);
    void set_win();
    void set_gameover();
};

#endif