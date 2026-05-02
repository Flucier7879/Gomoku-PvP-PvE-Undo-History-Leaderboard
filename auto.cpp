#include <stdio.h>
#include <stdlib.h>
#include "auto.h"

int board[100][100];

int isValid(int row, int col, int n) 
{
    return row >= 0 && row < n && col >= 0 && col < n;
}

int evaluatePosition(int row, int col, int n, int player, int dr, int dc)
{
    int count = 1;
    int block = 0;
    int forwardCount = 0;
    int backwardCount = 0;
    for (int i = 1; i < 5; i++)
    {
        int r = row + i * dr;
        int c = col + i * dc;
        if (isValid(r, c, n))
        {
            if (board[r][c] == player)
            {
                forwardCount++;
            }
            else if (board[r][c] != 0)
            {
                block++;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            block++;
            break;
        }
    }
    for (int i = 1; i < 5; i++)
    {
        int r = row - i * dr;
        int c = col - i * dc;
        if (isValid(r, c, n))
        {
            if (board[r][c] == player)
            {
                backwardCount++;
            }
            else if (board[r][c] != 0)
            {
                block++;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            block++;
            break;
        }
    }
    count = forwardCount + backwardCount + 1;
    int judgeScore = 0;
    if (count >= 5) 
    {
        judgeScore = 100000; // 五连，必胜
    }
     else if (count == 4 && block== 0) 
    {
        judgeScore = 10000; // 四连且两端没有被堵住，必胜
    }
     else if (count == 4 && block == 1) 
    {
        judgeScore = 1000; // 四连且一端被堵住
    }
     else if (count == 3 && block == 0) 
    {
        judgeScore = 100; // 三连且两端没有被堵住
    }
     else if (count == 3 && block == 1) 
    {
        judgeScore = 10; // 三连且一端被堵住
    }
     else if (count == 2 && block == 0) 
    {
        judgeScore = 1; // 二连且两端没有被堵住
    }
    return judgeScore;
}

int calculateScore(int row, int col, int n, int player) 
{
    int totalScore = 0;
    if(!isValid(row, col, n) || (board[row][col]) != 0 )
    {
        return -1;
    }
    int directions[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}}; 
    for (int d = 0; d < 4; d++) 
    {
        int score = evaluatePosition(row, col, n, player, directions[d][0], directions[d][1]);
        totalScore = score + totalScore;
    }  //这是机器的进攻得分
    int opponent = 3 - player;
    for (int d = 0; d < 4; d++) 
    {
        int score = evaluatePosition(row, col, n, opponent, directions[d][0], directions[d][1]);
        totalScore += score * 0.8; 
        // 查阅资料后，机器的防御权重应当降低，否则机器会变成胆小鬼，经验给出的最佳系数是得分乘以0.7~0.9之间
        //于是这里取0.8
    }
    return totalScore;
}

void autoMove(int n, int player, int* row, int* col)
{
    int bestRow = -1, bestCol = -1;
    int bestScore = -1;  //初始设为-1，确保任何合法位置的评分都高于它
    int centerRow = n / 2;
    int centerCol = n / 2;
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int score = calculateScore(i, j, n, player);
            if(score > bestScore)
            {
                bestScore = score;
                bestRow = i;
                bestCol = j;
            }
        }
    }
    
    // 如果所有位置得分都是0（空棋盘），直接选择中心
    if (bestScore == 0) 
    {
        bestRow = centerRow;
        bestCol = centerCol;
    }
    
    if (bestRow == -1 || bestCol == -1) 
    {
        bestRow = centerRow;
        bestCol = centerCol;
    }
    *row = bestRow;
    *col = bestCol;  //利用指针可以实现同一个函数返回2个或更多值
}