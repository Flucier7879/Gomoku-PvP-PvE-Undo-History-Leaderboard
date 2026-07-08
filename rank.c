#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rank.h"

#define MAX_RANK 200

typedef struct
{
    char name[100];
    int score;
} RankItem;

static int loadRankList(RankItem* list, int maxCount)
{
    FILE* fp = fopen("rankList.txt", "r");
    if (!fp)
    {
        return 0; // 文件不存在时视为空排行榜
    }
    int count = 0;
    char line[256];
    while (count < maxCount && fgets(line, sizeof(line), fp) != NULL)
    {
        // 跳过注释或空行
        if (line[0] == '#' || line[0] == '\n')
            continue;
        if (sscanf(line, "%99s %d", list[count].name, &list[count].score) == 2)
        {
            count++;
        }
    }
    fclose(fp);
    return count;
}

static void saveRankList(RankItem* list, int count)
{
    FILE* fp = fopen("rankList.txt", "w");
    if (!fp) return;

    // 可读排行榜
    fprintf(fp, "# 排行榜（按分数降序）\n");
    fprintf(fp, "# 名次. 玩家 分数\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "# %d. %s %d\n", i + 1, list[i].name, list[i].score);
    }
    fprintf(fp, "# ---------------------------------\n");

    // 供程序读取的原始数据（同样按排序写出）
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %d\n", list[i].name, list[i].score);
    }
    fclose(fp);
}

static void addScoreToRank(RankItem* list, int* count, const char* name, int delta)
{
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(list[i].name, name) == 0)
        {
            list[i].score += delta;
            return;
        }
    }
    if (*count < MAX_RANK)
    {
        strncpy(list[*count].name, name, sizeof(list[*count].name) - 1);
        list[*count].name[sizeof(list[*count].name) - 1] = '\0';
        list[*count].score = delta;
        (*count)++;
    }
}

static int compareRank(const void* a, const void* b)
{
    const RankItem* ra = (const RankItem*)a;
    const RankItem* rb = (const RankItem*)b;
    if (rb->score != ra->score)
        return rb->score - ra->score; // 分数高的在前
    return strcmp(ra->name, rb->name); // 分数相同按名字排序
}

void updateRankList(const char* player1Name, const char* player2Name, int resultFlag)
{
    RankItem list[MAX_RANK];
    int count = loadRankList(list, MAX_RANK);

    if (resultFlag == 1)
    {
        addScoreToRank(list, &count, player1Name, 2);
        addScoreToRank(list, &count, player2Name, 0);
    }
    else if (resultFlag == 2)
    {
        addScoreToRank(list, &count, player1Name, 0);
        addScoreToRank(list, &count, player2Name, 2);
    }
    else if (resultFlag == 3) // 平局
    {
        addScoreToRank(list, &count, player1Name, 1);
        addScoreToRank(list, &count, player2Name, 1);
    }

    qsort(list, count, sizeof(RankItem), compareRank);
    saveRankList(list, count);
}
void printRankList(void)
{
    RankItem list[MAX_RANK];
    int count = loadRankList(list, MAX_RANK);
    if (count == 0)
    {
        printf("\n排行榜为空。\n");
        return;
    }
    qsort(list, count, sizeof(RankItem), compareRank);
    printf("\n------ 排行榜 (name score) ------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s %d\n", i + 1, list[i].name, list[i].score);
    }
    printf("---------------------------------\n\n");
}

