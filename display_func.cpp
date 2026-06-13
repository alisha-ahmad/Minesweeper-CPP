#include <iostream>
#include "board.h"
#include "display_func.h"
#include "game.h"
using namespace std;

void disp_instructions(){
    cout << "**** MINESWEEPER ****\n";
    cout << "1. Enter row and column number to select a cell e.g. '2 3'\n";
    cout << "2. In order to flag a mine, enter F.\n";
    cout << "3. To check a cell, enter C.\n";
    cout << "4. For chording a revealed cell, enter C after row and column number.\n";
    cout << "If a flag is placed on a wrong neighbour cell and a mine is revealed during chording, you will lose.\n ";
}

int* select_level(){
    cout << "Select difficulty level: \n";
    cout << "\t1. Beginner (8x8, 10 mines)\n\t2. Intermediate (16x16, 40 mines)\n\t3. Expert (30x16, 99 mines)\n\t4. Custom\n";
    cout << "Level: ";
    int level;
    while (!(cin >> level)){
        cin.clear();
        cin.ignore(10000, '\n');
    }
    while (level<1 || level>4){
        cout << "Invalid difficulty level. Enter level: ";
        while (!(cin >> level)){
            cin.clear();
            cin.ignore(10000, '\n');
        }     
    }
    int r,c,m;
    if (level==1) r=8, c=8, m=10; 
    else if (level==2) r=16, c=16, m=40;
    else if (level==3) r=16, c=30, m=99;
    else{
        do{
            cout << "Enter number of rows (>3): ";
            while (!(cin >> r)){
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "Enter number of columns(>3): ";
            while (!(cin >> c)){
                cin.clear();
                cin.ignore(10000, '\n');
            }
        } while(r<=3 || c<=3);
        int max = (r-1)*(c-1);
        do {
            cout << "Enter number of mines(<" << max+1 << "): ";
            while (!(cin >> m)){
                cin.clear();
                cin.ignore(10000, '\n');
            }
        } while (m>max);
    }
    int *arr = new int[3];
    arr[0]=r, arr[1]=c, arr[2]=m;
    return arr;
}


bool disp_move(Board* field){
    int count=0;
    int c=field->get_cols();
    int r=field->get_rows();
    Cell** grid = field->get_grid();
    cout << "   ";
    for (int i=0; i<c; i++){
        if (i<10) cout << "   " << i << "  ";
        else cout << "  " << i << "  ";
    }
    cout << endl;
    for (int i=0; i<r; i++){
        if (i==0){
            cout << "   ";
            for (int j=0; j<c; j++){cout << " _____";}
            cout << endl;
        }
        for (int k=0; k<3; k++){
            if (k==1){
                if (i<10) cout << ' ' << i << " |";
                else cout << i << " |";
            }
            else cout << "   |";
            for (int j=0; j<c; j++){
                if (k==2){ cout << "_____|"; }
                else if (k==1){
                    if (grid[i][j].is_flagged()){ cout << "  F  |"; }
                    else if (grid[i][j].is_visible()){
                        cout << "  ";
                        if (grid[i][j].get_val()==1) cout << "\033[1;34m";
                        else if (grid[i][j].get_val()==2) cout << "\033[1;32m";
                        else if (grid[i][j].get_val()==3) cout << "\033[1;31m";
                        else if (grid[i][j].get_val()==4) cout << "\033[1;94m";

                        if (grid[i][j].is_mine()) cout << "*";
                        else cout << grid[i][j].get_val();
                        cout << "  \033[0m|";
                        count++;
                    }
                    else cout << "     |";
                }
                else cout << "     |";
            }
            cout << endl;
        }
    }
    return count == (r*c) - field->get_mines();
}

void disp_mines(Board* field){
    int c=field->get_cols();
    int r=field->get_rows();
    Cell** arr = field->get_grid();
            
    // int mineCount = 0;
    // for (int i = 0; i < r; i++) {
    //     for (int j = 0; j < c; j++) {
    //         if (arr[i][j].is_mine()) mineCount++;
    //     }
    // }
    // cout << "Mines found = " << mineCount << endl;

    cout << "   ";
    for (int i=0; i<c; i++){
        if (i<10) cout << "   " << i << "  ";
        else cout << "  " << i << "  ";
    }
    cout << endl;
    for (int i=0; i<r; i++){
        if (i==0){
            cout << "   ";
            for (int j=0; j<c; j++){cout << " _____";}
            cout << endl;
        }
        for (int k=0; k<3; k++){

            if (k==1 && i<10) cout << ' ' << i << " |";
            else if (k==1 && i>=10) cout << i << " |";
            else cout << "   |";

            for (int j=0; j<c; j++){
                if (k==2) cout << "_____|";
                else if (k==1){
                    cout << "  ";
                    if (arr[i][j].is_mine()){cout << "*  |";}
                    else if (arr[i][j].is_flagged() && !arr[i][j].is_mine()) cout << "\033[1;31m" << 'X' <<  "  \033[0m|";
                    else {
                        if (arr[i][j].is_visible()){
                            if (arr[i][j].get_val()==1) cout << "\033[1;34m";
                            else if (arr[i][j].get_val()==2) cout << "\033[1;32m";
                            else if (arr[i][j].get_val()==3) cout << "\033[1;31m";
                            else if (arr[i][j].get_val()==4) cout << "\033[1;94m";
                            cout << arr[i][j].get_val() << "  \033[0m|";
                        }
                        else cout << "   |";
                    }
                }
                else cout << "     |";
            }
            cout << endl;
        } 
    }
}