#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<iostream>
#include<string>
#define ROWMAX 40000
#define RC 401
#define RR 201
#define EMPTY -1
#define ERZA -2
#define JELAAL -3
#define BLOCK -4
using namespace std;
int Grid[RC][RR];
int Level[RC][RR];


int C;
int dsti, dstj,srci,srcj;
struct _Q
{
    int i;
    int j;
};
int _move_i[6] = { -1, -1, 1, 1 , 0 ,0};
int _move_j[6] = { -1, 1, -1, 1 ,-2 ,2};
_Q Q[ROWMAX];
int front = 0;
int tail = 0;

void enQ(int i,int j)
{
    if (tail < ROWMAX)
    {
        Q[tail].i = i;
        Q[tail].j = j;
        tail++;
    }
}
_Q dQ()
{
    _Q q; q.i = q.j = -1;
    if (front < ROWMAX)
        q = Q[front++];
    return q;
}
int isQempty()
{
    if (front == tail)
        return 1;
    return 0;
}
void reset()
{
    front = tail = 0;
    for (int k = 0; k < RR; k++)
    {
        for (int l = 0; l < RC; l++)
        {
            Level[k][l] = -1;
        }
    }
}
void BFS(int i,int j)
{
    int range = Grid[i][j];
    int caught = 0;
    //reset();

    Level[i][j] = 0;
    Grid[i][j] = BLOCK;
    enQ(i, j);
    while (front < tail )
    {
        _Q v = dQ();
        if (v.i == -1)
            break;

        for (int i = 0; i < 6;i++)
        {
            int l, m;
            l = v.i + _move_i[i];
            m = v.j + _move_j[i];
            if (l >= 0 && l < RR && m >= 0 && m < RC)
            {
                if (Level[l][m] == -1 && Level[v.i][v.j] < range && Grid[l][m] == EMPTY)
                {
                    Level[l][m] = Level[v.i][v.j] + 1;
                    Grid[l][m] = BLOCK;
                    enQ(l, m);
                }
            }
        }
    }
}
int BFSPath(int i, int j)
{
    int caught = 0;
    reset();

    Level[i][j] = 0;
    enQ(i, j);
    while (front < tail)
    {
        _Q v = dQ();
        if (v.i == -1)
            break;

        for (int i = 0; i < 6; i++)
        {
            int l, m;
            //up left
            l = v.i + _move_i[i];
            m = v.j + _move_j[i];
            if (l >= 0 && l < RR && m >= 0 && m < RC)
            {
                if (Level[l][m] == -1 && Grid[l][m] != BLOCK)
                {
                    Level[l][m] = Level[v.i][v.j] + 1;
                    enQ(l, m);
                }
            }
        }
    }
    if (Level[dsti][dstj] == -1)
        return 0;
    else
        return 1;

}
void initializeGrid()
{
    for (int i = 0; i < RR; i++)
    {
        for (int j = 0; j < RC; j++)
        {
            Grid[i][j] = 0;
        }
    }
}
int main()
{
    int i, T;
    freopen("Text.txt", "r", stdin);
    cin >> T;
    for (i = 0; i < T; i++)
    {
        int ans = 0;
        char str[201];
        cin >> C ;
        int blank = C ;
        C = (2 * C)-1;

        for (int j = 0; j < C; j++)
        {
            if (j <= C/2 )
                blank--;
            else
                blank++;
            cin >> str;
            for (int k = 0,r = blank; str[k] != '\0'; k++,r += 2)
            {
                if (str[k] == '.')
                    Grid[j][r] = EMPTY;
                if (str[k] == 'R')
                {
                    Grid[j][r] = JELAAL;
                    srci = j; srcj = r;
                }
                if (str[k] == 'C')
                {
                    Grid[j][r] = ERZA;
                    dsti = j; dstj = r;
                }
                if (str[k] >= '1' && str[k] <= '9')
                {
                    char c = str[k];
                    int a = c - '0';
                    Grid[j][r] = a;
                }
            }
        }
        for (int j = 0; j < RR; j++)
        {
            for (int k = 0; k < RC; k++)
            {
                if (Grid[j][k] >= 1 && Grid[j][k] <= 9)
                    BFS(j, k);
            }
        }
        ans = BFSPath(srci,srcj);


        if (ans == 1)
            printf("Case #%d\n%s\n", i + 1, "YES");
        else
            printf("Case #%d\n%s\n", i + 1, "NO");


    }
    return 0;
}
