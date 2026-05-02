#ifndef UNDO_H
#define UNDO_H

typedef struct
{
    int row;
    int col;
    int player;
} Move;

typedef struct
{
    Move moves[10000];
    int count;
} MoveHistory;

void initMoveHistory(MoveHistory* history);

void saveMove(MoveHistory* history, int row, int col, int player);

int undoMove(MoveHistory* history, Move* undoneMove);

int getMoveCount(MoveHistory* history);

#endif
