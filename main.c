#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "undo.h"
#include "auto.h"
#include "rank.h"

void initboard(int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            board[i][j]=0;
        }
    }
}
            
void printboard(int n)
{
    int i,j;
    printf("  ");  //空出字符，保证列号对应
    for (j = 1; j <= n; j++) 
    {
        printf("%3d", j);
    }
    printf("\n");
    for(i=0;i<n;i++)
    {
        printf("%3d",i+1);
        for(j=0;j<n;j++)
        {
            if(board[i][j]==0)
            {
                printf(" · ");
            }
            else if(board[i][j]==1)
            {
                printf(" X ");
            }
            else if(board[i][j]==2)
            {
                 printf(" O ");
            }
        }
        printf("\n");
    }
}


int checkwin(int row, int col, int n, int player) 
{
    int directions[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}}; // 横向，纵向，主对角线，副对角线
    for(int d = 0;d<4;d++)
    {
        int count = 1;  //当前操作位置
        int dr = directions[d][0]; //row的改变量，沿着direction中第d个方向
        int dc = directions[d][1]; //col的改变量，沿着direction中第d个方向
        //正方向判断
        for(int i = 1;i<5;i++)
        {
            int r = row + i * dr;//新的row编号
            int c = col + i * dc;//新的col编号
            if(isValid(r,c,n) && board[r][c] == player)
                count++;
            else
                break;
        }
        //反方向判断
        for(int i = 1;i<5;i++)
        {
            int r = row - i * dr;//新的row编号
            int c = col - i * dc;//新的col编号
            if(isValid(r,c,n) && board[r][c] == player) //检查位置合法，且该位置为当前玩家的棋子
                count++;
            else
                break;
        }
        if(count >= 5)
            return player; // 返回获胜玩家编号
    }
    return 0; // 没有玩家赢
}

void clearbuffer(void) 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    system("chcp 65001 > nul");  // 设置控制台编码为 UTF-8，避免中文乱码
    while (1) // 支持多局循环
    {
        int n;
        int row,col;
        int inputCol,inputRow;
        int totalMoves = 0;
        int player = 1;
        int mode;
        int humanPlayer = 1;
        int gameResult = 0; // 1:玩家1赢 2:玩家2赢 3:平局
        char player1Name[100] = "";
        char player2Name[100] = "";
        
        printf("五子棋游戏开始\n");
        printf("玩家1将会使用X，玩家2将会使用O\n");
        while(1)
        {
            printf("请选择游戏模式：\n");
            printf("1. 双人对战\n");
            printf("2. 人机对战\n");
            printf("请输入选项（1或2）：");
            if (scanf("%d", &mode) != 1) 
            {
                printf("输入无效，请输入1或2。\n");
                clearbuffer();
                continue;
            }
            if (mode == 1 || mode == 2) 
                break;
        }


        if (mode == 2) 
        {
            while (1) 
            {
                printf("请选择您要扮演的玩家：\n");
                printf("1. 玩家1（X，先手）\n");
                printf("2. 玩家2（O，后手）\n");
                printf("请输入选项（1或2）：");
                if (scanf("%d", &humanPlayer) != 1) 
                {
                    printf("输入无效，请输入1或2。\n");
                    clearbuffer();
                }
                if (humanPlayer == 1 || humanPlayer == 2) 
                    break;
            }
        }
        
        // 输入玩家用户名（根据人机选择决定谁是电脑）
        clearbuffer();  // 清理前面 scanf 残留的换行
        if (mode == 1) 
        {
            printf("\n请输入玩家1的用户名：");
            if (fgets(player1Name, sizeof(player1Name), stdin) != NULL) 
            { 
                size_t len = strlen(player1Name);
                if (len > 0 && player1Name[len - 1] == '\n') {
                    player1Name[len - 1] = '\0';
                }
            }
            if (strlen(player1Name) == 0) 
            {
                strcpy(player1Name, "玩家1");
            }

            printf("请输入玩家2的用户名：");
            if (fgets(player2Name, sizeof(player2Name), stdin) != NULL) 
            {
                size_t len = strlen(player2Name);
                if (len > 0 && player2Name[len - 1] == '\n') {
                    player2Name[len - 1] = '\0';
                }
            }
            if (strlen(player2Name) == 0) 
            {
                strcpy(player2Name, "玩家2");
            }
        } 
        else 
        {
            if (humanPlayer == 1) 
            {
                printf("\n请输入玩家1的用户名：");
                if (fgets(player1Name, sizeof(player1Name), stdin) != NULL) 
                { 
                    size_t len = strlen(player1Name);
                    if (len > 0 && player1Name[len - 1] == '\n') {
                        player1Name[len - 1] = '\0';
                    }
                }
                if (strlen(player1Name) == 0) 
                {
                    strcpy(player1Name, "玩家1");
                }
                strcpy(player2Name, "电脑");
            }
            else  // humanPlayer == 2
            {
                strcpy(player1Name, "电脑");
                printf("\n请输入玩家2的用户名：");
                if (fgets(player2Name, sizeof(player2Name), stdin) != NULL) 
                { 
                    size_t len = strlen(player2Name);
                    if (len > 0 && player2Name[len - 1] == '\n') {
                        player2Name[len - 1] = '\0';
                    }
                }
                if (strlen(player2Name) == 0) 
                {
                    strcpy(player2Name, "玩家2");
                }
            }
        }
        
        printf("\n游戏开始！%s (X) vs %s (O)\n\n", player1Name, player2Name);

        while (1) 
        {
            printf("请输入棋盘大小（5~100）：");
            if (scanf("%d", &n) != 1) 
            {
                printf("输入无效，请输入整数。\n");
                clearbuffer();
                continue;
            }
            if (n >= 5 && n <= 100) break;
            printf("棋盘大小必须在 5 到 100 之间！\n");
        }
        initboard(n);
        MoveHistory history;
        initMoveHistory(&history);
        while(1)
        {
            printboard(n);  //更新棋盘
            if(mode == 2 && player != humanPlayer)
            {
                printf("\n电脑正在思考...\n");
                autoMove(n, player, &row, &col);
                printf("电脑选择了位置：%d %d\n", row + 1, col + 1);

            }
            else
            {
                while(1)
                {
                    printf("\n（悔棋请输入 0 0，退出请输入 -1 -1）\n");
                    if (player == 1) {
                        printf("\n%s，请输入落子位置（行 列）", player1Name);
                    } else {
                        printf("\n%s，请输入落子位置（行 列）", player2Name);
                    }
                    if (scanf("%d %d", &inputRow, &inputCol) != 2)
                    {
                        printf("输入无效，请输入两个整数。\n");
                        clearbuffer();
                        continue;
                    }
                    clearbuffer();
                    // 悔棋和退出是人类玩家专用，需要和机器分开处理
                    if (inputRow == -1 && inputCol == -1)
                    {
                        printf("游戏已退出！感谢游玩\n");
                        return 0;
                    }

                    if (inputRow == 0 && inputCol == 0)
                    {
                        if(totalMoves == 0)
                        {
                            printf("无法悔棋!当前没有可撤销的步数\n");
                            continue;
                        }
                        else
                        {
                            Move undoneMove;
                            if(undoMove(&history, &undoneMove))
                            {
                                board[undoneMove.row][undoneMove.col] = 0;  //恢复棋盘
                                totalMoves--;
                                printf("已悔棋\n");
                                player = undoneMove.player;
                                // 悔棋后直接重新开始循环，重新打印棋盘并让当前玩家重新落子
                                continue;
                            }
                        }
                    }

                    // 普通落子：把人类输入的 1~n 转换成内部使用的 0~n-1
                    if (inputRow < 1 || inputRow > n || inputCol < 1 || inputCol > n)
                    {
                        printf("无效位置，请输入 1~%d 之间的行列号。\n", n);
                        continue;
                    }

                    row = inputRow - 1;
                    col = inputCol - 1;
                    break;
                }
            }
            if(!isValid(row, col, n) || board[row][col] != 0)  //判断是否合法
            {
                printf("无效位置，请重新输入。\n");
                continue;
            }
            totalMoves++;
            saveMove(&history, row, col, player);
            if(player == 1)
            {
                board[row][col] = 1;
            }
            else
            {
                board[row][col] = 2;
            }

            if(checkwin(row, col, n, player))
            {
                printboard(n);
                if (player == 1) 
                {
                    printf("\n%s获胜！恭喜！\n", player1Name);
                } 
                else 
                {
                    printf("\n%s获胜！恭喜！\n", player2Name);
                }
                printf("游戏结束！感谢游玩\n");
                FILE *fp = fopen("result.txt", "a");
                if (fp != NULL) 
                {
                    time_t now = time(NULL);
                    struct tm *timeinfo = localtime(&now);
                    char winnerName[100];
                    if (player == 1) 
                    {
                        strcpy(winnerName, player1Name);
                    } 
                    else 
                    {
                        strcpy(winnerName, player2Name);
                    }
                    fprintf(fp, "游戏结果：%s获胜\n", winnerName);
                    fprintf(fp, "游戏完成时间：%d年%d月%d日%d时%d分%d秒\n", 
                            timeinfo->tm_year + 1900, 
                            timeinfo->tm_mon + 1, 
                            timeinfo->tm_mday,
                            timeinfo->tm_hour, 
                            timeinfo->tm_min, 
                            timeinfo->tm_sec);
                    fprintf(fp, "\n");
                    fclose(fp);
                    printf("游戏结果已保存到result.txt\n");
                }
                gameResult = player; // 1或2
                break;
            }
            if(totalMoves == n * n)
            {
                printboard(n);
                printf("\n平局！棋盘已满。感谢游玩\n");
                FILE *fp = fopen("result.txt", "a");
                if (fp != NULL) 
                {
                    time_t now = time(NULL);
                    struct tm *timeinfo = localtime(&now);
                    fprintf(fp, "游戏结果：平局\n");
                    fprintf(fp, "游戏完成时间：%d年%d月%d日%d时%d分%d秒\n", 
                            timeinfo->tm_year + 1900, 
                            timeinfo->tm_mon + 1, 
                            timeinfo->tm_mday,
                            timeinfo->tm_hour, 
                            timeinfo->tm_min, 
                            timeinfo->tm_sec);
                    fprintf(fp, "\n");
                    fclose(fp);
                    printf("游戏结果已保存到result.txt\n");
                }
                gameResult = 3; // 平局
                break;
            }
            if(player == 1)
            player = 2;
            else
            player = 1;  //切换玩家
        }

        // 更新排行榜
        updateRankList(player1Name, player2Name, gameResult);

        // 赛后选项：a退出, b再来一局, c查看排行榜
        while (1)
        {
            char choice;
            printf("\n请输入选项：a 退出 / b 再来一局 / c 查看排行榜：");
            if (scanf(" %c", &choice) != 1)
            {
                printf("输入无效，请重新输入。\n");
                clearbuffer();
                continue;
            }
            clearbuffer();
            if (choice == 'a' || choice == 'A')
            {
                printf("感谢游玩，再见！\n");
                return 0;
            }
            else if (choice == 'b' || choice == 'B')
            {
                printf("\n即将开始新的一局...\n\n");
                break; // 跳出赛后选项循环，回到最外层开始新局
            }
            else if (choice == 'c' || choice == 'C')
            {
                printRankList();
            }
            else
            {
                printf("无效选项，请输入 a / b / c。\n");
            }
        }
    }
    return 0;
}

