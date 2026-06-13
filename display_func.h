#ifndef DISPLAY_FUNC_H
#define DISPLAY_FUNC_H

#include "board.h"

void disp_instructions();
int* select_level();
bool disp_move(Board* field);
void disp_mines(Board* field);

#endif