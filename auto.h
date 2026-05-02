#ifndef AUTO_H
#define AUTO_H

extern int board[100][100];

int isValid(int row, int col, int n);

void autoMove(int n, int player, int* row, int* col);

#endif

