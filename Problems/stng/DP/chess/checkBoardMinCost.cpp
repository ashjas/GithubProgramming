#include<stdio.h>
//#include"stdafx.h"
#include<stdlib.h>
#include<limits.h>
#include<iostream>
using namespace std;
int Grid[1001][1001];
int D[1001][1001];
int w[1001][1001];
int R, C;
#define INF 999999;
void printpath(int i, int j)
{
    if (i == R)
        return;
    printpath(i + 1, w[i][j]);
    printf("%d ", j+1);
}
int main()
{
    int i, T;
    freopen("checkBoardMinCost.txt", "r", stdin);
    cin >> T;
    for (i = 0; i < T; i++)
    {
        cin >> R >> C;
        for (int j = 0; j < R; j++)
        {
            for (int k = 0; k < C; k++)
            {
                cin >> Grid[j][k];
                D[j][k] = INF;
//                w[j][k] = 0;
            }
        }

        for (int j = R - 2; j >= 0; j--)
        {
            for (int k = 0; k < C; k++)
            {
                int max = INF;
                max = Grid[j][k] + Grid[j + 1][k];
                w[j][k] = k;

                if (k > 0 && max > (Grid[j][k] + Grid[j + 1][k-1]) )
                {
                    max = Grid[j][k] + Grid[j + 1][k-1];
                    w[j][k] = k-1;
                }
                if (k < (C - 1) && max > (Grid[j][k] + Grid[j + 1][k + 1]))
                {
                    max = Grid[j][k] + Grid[j + 1][k + 1];
                    w[j][k] = k + 1;
                }
                Grid[j][k] = max;
            }
        }
        int jmin = INF;int  max = INF;
        for (int j = 0; j < C; j++)
        {

            if (Grid[0][j] < max)
            {
                jmin = j;
                max = Grid[0][j];
            }
        }
        printf("Case #%d\n",i+1);
        printf("%d\n", Grid[0][jmin]);
        printpath(0,jmin);
        printf("\n");
    }
    return 0;
}
#if 0
6
3 3
1 2 3
4 8 - 2
1 5 3
3 3
1 2 3
- 7 8 - 2
1 5 3
7 8
1 1 9 9 9 9 9 9
9 9 - 88 1 9 9 9 9
9 9 9 1 1 9 9 9
1 1 1 1 - 99 9 9 9
- 10 1 8 9 9 1 9 9
9 9 1 1 1 9 1 9
9 9 9 9 9 9 9 1
7 7
1 9 9 1 1 9 9
9 1 9 1 8 1 9
9 1 9 1 9 1 9
9 9 1 1 9 1 9
9 9 9 9 1 9 9
9 9 9 9 9 1 9
9 9 9 9 9 9 1
8 7
1 9 9 1 - 10 9 9
1 9 9 1 1 9 9
9 - 88 9 1 8 1 9
9 1 1 1 9 1 9
9 9 1 - 99 9 1 9
9 9 9 9 1 9 9
9 9 9 9 9 1 9
9 9 9 9 9 9 1
10 7
1 9 - 9 - 99 - 10 9 9
1 9 9 1 10 9 9
1 9 9 1 - 10 - 69 9
1 9 9 1 1 9 9
9 - 88 9 1 8 1 9
9 1 1 1 9 1 9
9 9 1 - 99 9 1 9
9 9 9 9 1 9 9
9 9 9 9 9 1 9
9 9 9 9 9 9 1
-------------------
Output:
Case #1
3
3 3 2
Case #2
-5
1 1 1
Case #3
-182
8 7 6 5 4 3 2
Case #4
7
7 6 5 4 4 4 4
Case #5
-181
7 6 5 4 3 2 1 1
Case #6
-271
7 6 5 4 3 2 3 4 4 4
#endif
