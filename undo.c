#include "undo.h"

void initMoveHistory(MoveHistory* history) 
{
    history->count = 0;
}

void saveMove(MoveHistory* history, int row, int col, int player)
{
    if(history->count < 10000)
    {
        history->moves[history->count].row = row;
        history->moves[history->count].col = col;
        history->moves[history->count].player = player;
        history->count++;
    }
}

int undoMove(MoveHistory* history, Move* undoneMove)
{
    if(history->count > 0)
    {
        history->count--;  //让记录指向上一步落子
        if(undoneMove != 0)
        {
            undoneMove->row = history->moves[history->count].row;
            undoneMove->col = history->moves[history->count].col;
            undoneMove->player = history->moves[history->count].player;
        }
        return 1;
    }
    return 0;
}

int getMoveCount(MoveHistory* history)
{
    return history->count;
}
