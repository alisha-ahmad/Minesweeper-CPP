#include "cell.h"
#include "board.h"
#include <ctime>
#include <cstdlib>

//constructors
Board::Board(): rows(0), cols(0), mines(0), grid(nullptr) {}
Board::Board(int r, int c, int m): rows(r), cols(c), mines(m) {
    grid = new Cell*[rows];
    for (int i=0; i<rows; i++){
        grid[i] = new Cell[cols];
    }
    
}
Board::Board(const Board& other): rows(other.rows), cols(other.cols), mines(other.mines) {
    grid = new Cell*[rows];
    for (int i=0; i<rows; i++){
        grid[i] = new Cell[cols];
    }
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++) grid[i][j] = other.grid[i][j];
    }
}

//assignment operator
Board& Board::operator=(const Board& other){
    if (this != &other){
        Cell** temp = new Cell*[other.rows];
        for (int i=0; i<other.rows; i++){
            temp[i] = new Cell[other.cols];
        }
        for (int i=0; i<other.rows; i++){
            for (int j=0; j<other.cols; j++) temp[i][j] = other.grid[i][j];
        }
        for (int i=0; i<rows; i++){
            delete[] grid[i];
        }
        delete[] grid;
        rows = other.rows;
        cols = other.cols;
        mines = other.mines;
        grid = temp;
    }
    return *this;
}

//getters
int Board::get_cols() const{ return cols; }
int Board::get_rows() const{ return rows; }
int Board::get_mines() const{ return mines; }
Cell** Board::get_grid() const{ return grid; }

//grid initialization (public members)
void Board::init_mines(int ir, int ic){
        int pos, mr, mc;
        int count=0;
        while(count<mines){
            pos = rand()%(rows*cols);
            mr = pos/cols;
            mc = pos%cols;
            if (!(mr==ir && mc==ic) && !grid[mr][mc].is_mine()){
                grid[mr][mc].set_mine();
                count++;
            }
        }
}

void Board::fill_values(){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            if (!grid[i][j].is_mine()){
                int count = 0;
                if (i>0){
                    if (grid[i-1][j].is_mine()) count++;
                    if (j>0 && grid[i-1][j-1].is_mine()) count++; 
                    if (j<cols-1 && grid[i-1][j+1].is_mine()) count++; 
                }
                if (i<rows-1){
                    if (grid[i+1][j].is_mine()) count++;
                    if (j>0 && grid[i+1][j-1].is_mine()) count++; 
                    if (j<cols-1 && grid[i+1][j+1].is_mine()) count++;
                }
                if (j>0 && grid[i][j-1].is_mine()) count++;
                if (j<cols-1 && grid[i][j+1].is_mine()) count++; 
                grid[i][j].set_val(count);
            }
        }
    }
}

Board::~Board(){
    for (int i=0; i<rows; i++){
        delete[] grid[i];
    }
    delete[] grid; 
    grid = nullptr;
}