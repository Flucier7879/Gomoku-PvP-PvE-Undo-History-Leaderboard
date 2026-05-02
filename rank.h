#ifndef RANK_H
#define RANK_H

// 更新排行榜：resultFlag代表对局结束情况 1 玩家1胜, 2 玩家2胜, 3 平局
void updateRankList(const char* player1Name, const char* player2Name, int resultFlag);

// 打印排行榜到标准输出
void printRankList(void);

#endif

