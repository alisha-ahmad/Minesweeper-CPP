#include <cstdlib>
#include "display_func.h"
#include "game.h"
#include "board.h"
#include "cell.h"
#include <iostream>
#include <cctype>
#include <ctime>

using namespace std;

int main(){
    srand(static_cast<unsigned>(time(nullptr)));
    disp_instructions();
    int *level_info = select_level();
    
    Board mine_field(level_info[0], level_info[1], level_info[2]);
    Game session(mine_field);
    disp_move(session.get_board());
    int r_pos, c_pos;
    char move;

    //first move
    do {
        do {
            cout << "Enter cell coordinates [row] [col]: ";
            cin >> r_pos >> c_pos;
            if (cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Enter numbers only\n";
                continue;
            }
        } while (r_pos<0 || r_pos>=mine_field.get_rows() || c_pos<0 || c_pos>=mine_field.get_cols());
        do{
            cout << "Enter your move [F/C]: ";
            cin >> move;
        } while ((char)tolower(move)!='c' && (char)tolower(move)!='f');
        if ((char)tolower(move)=='f') session.toggleFlag(r_pos, c_pos);
        disp_move(session.get_board());
    } while ((char)tolower(move)!='c');

    mine_field.init_mines(r_pos, c_pos); 
    mine_field.fill_values();

    session.check_cell(r_pos, c_pos);
    system("cls");
    disp_move(session.get_board());

    while (!session.is_gameover() && !session.is_win())
    {
        do{
            cout << "Enter cell coordinates [row] [col]: ";
            cin >> r_pos >> c_pos;
            if (cin.fail()){
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Enter numbers only\n";
                continue;
            }
        } while (r_pos<0 || r_pos>=mine_field.get_rows() || c_pos<0 || c_pos>=mine_field.get_cols());
        do{
            cout << "Enter your move [F/C]: ";
            cin >> move;
        } while ((char)tolower(move)!='c' && (char)tolower(move)!='f');
        if ((char)tolower(move)=='f'){
            if (!session.is_visible(r_pos, c_pos)) session.toggleFlag(r_pos, c_pos);
        } else if ((char)tolower(move)=='c') session.check_cell(r_pos, c_pos);
        system("cls");
        if (session.is_gameover()){
            disp_mines(session.get_board());
            cout << "YOU LOST!!!\n";
            system("pause");
        } else {
            if (disp_move(session.get_board())){
                session.set_win();
                cout << "You won!\n";
            }
        }
    }
    delete[] level_info;
    level_info = nullptr;
    return 0;
}
