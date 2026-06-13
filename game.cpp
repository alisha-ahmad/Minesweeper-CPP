#include "game.h"

// private members:
// Board board;
// bool gameover, win;

//constructors
Game::Game(): board(nullptr), gameover(false), win(false) {}
Game::Game(Board &b): board(&b), gameover(false), win(false) {}
Game::Game(const Game& other): board(other.board), gameover(other.gameover), win(other.win) {}

//assignment operator
Game& Game::operator=(const Game& other){
    if (this != &other){
        gameover=other.gameover;
        win = other.win;
        board = other.board;
    }
    return *this;
}

//private member functions
void Game::rev_zero(int i, int j){
    Cell **grid = board->get_grid();
    int cols=board->get_cols(), rows=board->get_rows();

    if (grid[i][j].is_visible() || grid[i][j].is_flagged()) return;
        grid[i][j].make_visible();
        if (i > 0){
            if (grid[i-1][j].get_val()==0 && !grid[i-1][j].is_visible()) rev_zero(i-1, j);
            else grid[i-1][j].make_visible();
            if (j > 0){
                if (grid[i-1][j-1].get_val()==0 && !grid[i-1][j-1].is_visible()) rev_zero(i-1, j-1);
                else grid[i-1][j-1].make_visible();
            }
            if (j < cols-1){
                if (grid[i-1][j+1].get_val()==0 && !grid[i-1][j+1].is_visible()) rev_zero(i-1, j+1);
                else grid[i-1][j+1].make_visible();
            }
        }
        if (i < rows-1){
            if (grid[i+1][j].get_val()==0 && !grid[i+1][j].is_visible()) rev_zero(i+1, j);
            else grid[i+1][j].make_visible();
            if (j > 0){
                if (grid[i+1][j-1].get_val()==0 && !grid[i+1][j-1].is_visible()) rev_zero(i+1, j-1);
                else grid[i+1][j-1].make_visible();
            }
            if (j < cols-1){
                if (grid[i+1][j+1].get_val()==0 && !grid[i+1][j+1].is_visible()) rev_zero(i+1, j+1);
                else grid[i+1][j+1].make_visible();
            }
        }
        if (j > 0){
            if (grid[i][j-1].get_val()==0 && !grid[i][j-1].is_visible()) rev_zero(i, j-1);
            else grid[i][j-1].make_visible();
        }
        if (j < cols-1){
            if (grid[i][j+1].get_val()==0 && !grid[i][j+1].is_visible()) rev_zero(i, j+1);
            else grid[i][j+1].make_visible();
        }
}

bool Game::chord(int ir, int ic) {
    int count = count_flags(ir, ic);
    Cell **arr = board->get_grid();
    if (count != arr[ir][ic].get_val()) return false;
    bool hit = false;
    int r=board->get_rows(), c=board->get_cols();
    for (int di=-1; di<=1; di++){
        for (int dj=-1; dj<=1; dj++){
            if (!(di==0 && dj==0)){
                int ni=ir+di;
                int nj=ic+dj;
                if (ni>=0 && ni<r && nj>=0 && nj<c){
                    if (arr[ni][nj].is_flagged()) continue;
                    if (arr[ni][nj].is_mine()) hit=true;
                    else if (arr[ni][nj].get_val()==0) rev_zero(ni, nj);
                    else if (!arr[ni][nj].is_visible()) reveal(ni, nj);
                }
            }
        }
    }
    return hit;
}
//in main: gameover = chord();

int Game::count_flags(int i, int j) {
    int count=0;
    Cell **arr = board->get_grid();
    int r=board->get_rows(), c=board->get_cols();
    if (i>0){
        if (arr[i-1][j].is_flagged()) count++;
        if (j>0 && arr[i-1][j-1].is_flagged()) count++;
        if (j<c-1 && arr[i-1][j+1].is_flagged()) count++;
    }
    if (i<r-1){
        if (arr[i+1][j].is_flagged()) count++;
        if (j>0 && arr[i+1][j-1].is_flagged()) count++;
        if (j<c-1 && arr[i+1][j+1].is_flagged()) count++;
    }
    if (j>0 && arr[i][j-1].is_flagged()) count++;
    if (j<c-1 && arr[i][j+1].is_flagged()) count++;
    return count;
}

//public functions:
void Game::reveal(int i, int j) {
   board->get_grid()[i][j].make_visible();
}
void Game::toggleFlag(int i, int j) {
    Cell **arr = board->get_grid();
     if (arr[i][j].is_visible()) return;
    if (arr[i][j].is_flagged()) {
        arr[i][j].remove_flag();
    } else {
        arr[i][j].set_flag();
    }
}

void Game::check_cell(int i, int j) {
    if (board->get_grid()[i][j].is_flagged()) return;
    if (board->get_grid()[i][j].is_mine()){
        gameover = true;
        return;
    }
    if (get_val(i,j)==0) rev_zero(i,j);
    else {
        if (is_visible(i,j) && get_val(i,j)!=0) gameover = chord(i,j);
        else reveal(i,j);
    }
}

Board* Game::get_board(){ return board; }
int Game::get_val(int i, int j){
    return board->get_grid()[i][j].get_val();
}
bool Game::is_gameover(){ return gameover; }
bool Game::is_win(){ return win; }
bool Game::is_visible(int i, int j){ return board->get_grid()[i][j].is_visible();}

void Game::set_win(){ win = true; }
void Game::set_gameover(){ gameover = true; }