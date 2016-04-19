#include<stdio.h>
//#include"stdafx.h"
#include<stdlib.h>
#include<limits.h>

typedef struct _cell
{
    int x;
    int y;
    int p;
    int wt;
}cell;
typedef struct _Q
{
    cell vertex;
    struct _Q* next;
    struct _Q* tail;
}Queue;

Queue *Q = NULL;
cell Parent[1000][1000];
cell dummy;
int R, C, L, X, Y;
cell Arr[1000][1000];
cell Arr2[1000][1000];
int xx[6] = { -2, 2, -1, 1, -2, 2 };
int yy[6] = { -1, -1, -2, -2, -2, -2 };
typedef struct ans
{
    int x;
    int y;
    int minWt;
}Ans;
cell answer[1000];
int pathY = 0;
#define MAXWT 400000

void enQ(cell v)
{
    Queue * q = (Queue*)malloc(sizeof(Queue));
    q->vertex = v;
    q->next = NULL;
    q->tail = q;
    if (Q == NULL)
    {
        Q = q;
    }
    else
    {
        Q->tail->next = q;
        Q->tail = q;
    }
}
cell deQ()
{
    cell n;
    if (Q == NULL)
        return n;
    n = Q->vertex;
    Queue *q = Q;
    if (Q->next)
        Q->next->tail = Q->tail;// Q->next will be NULL for last item.
    Q = Q->next;
    if (q)
        free(q);
    return n;
}
int isQEmpty()
{
    if (Q == NULL)
        return 1;
    return 0;
}
int ends[6][2]= {
                -2 , -1,
                 2 , -1,
                 -1, -2,
                 1, -2,
                 -2,-2,
                 2,-2
                };
int moves[6][6] = {
                    -1, 0, -1 ,0 ,0 ,-1,
                     1, 0,  1, 0, 0, -1,
                     0, -1, 0, -1, -1, 0,
                     0, -1 ,0, -1, 1, 0,
                     1, 1, 1, 1, -3, -3,
                     -1, -1, -1, -1, -3,-3
                    };
void BFS(int x, int y)
{
    int i,j,p,q;
    cell tmp = dummy; int minWt=MAXWT;
    Parent[x][y] = tmp;
    //cell c ;c.x=x,c.y=y,c.wt=Arr[x][y].wt;
    enQ(Arr[x][y]);
    int power=-1;
    while (!isQEmpty())
    {
        cell v = deQ();
        if(power < 2;)
        power++;
        for(i=0;i<6;i++)
        {
            int X = v.x+ ends[i][0];
            int Y = v.y+ ends[i][1];
            if(X >= 0 && X < R && Y >= 0 && Y < C && Parent[X][Y].x == dummy.x)
            {
                /*for(j=0;j<3;j+=2)// for adding up weights, and setting parent for backtracking
                {
                    p = v.x+ moves[i][j];
                    q = v.y+ moves[i][j+1];
                    Parent[p][q] = Arr[v.x][v.y];
                }*/
                Arr[X][Y].wt += Arr[v.x][v.x].wt;
                Parent[X][Y] = Arr[v.x][v.y];
                //cell c; c.x=X;c.y=Y;c.wt=Arr[X][Y].wt;
                enQ(Arr[X][Y]);
                if(X == 0 && answer[x].wt > Arr[X][Y].wt)//reached the top row.
                {
                    answer[x] = Arr[X][Y];
                    //answer[x].x = X;
                    //answer[x].y = Y;
                    //answer[x].minWt = Arr[X][Y].wt;
                }
            }

        }


    }
}
void resetArr()
{
    int j,k;
        for (j = 0; j<R ; j++)
        {
            for(k=0;k<C;k++)
            {
                Arr[j][k] = Arr2[j][k];
            }
        }

}
void printPath(int x, int y)
{
    if(x == R - 1)
    {
        printf("%d %d ",x,y);
        return;
    }
    cell c = Parent[x][y];
    printPath(c.x,c.y);
    printf("%d %d ",x,y);
}
void printPath1(int x, int y)
{
    int i;
    for(i=0;i<R;i++)
    {
        printf("%d %d ",x,y);
        cell c = Parent[x][y];
        x = c.x;y = c.y;
    }
}
int main()
{
    int i, j, k;
    int T;
    dummy.x=dummy.y=dummy.wt=dummy.p = -  1;
    freopen("Text.txt", "r", stdin);
    setbuf(stdout, NULL);
    scanf("%d", &T);
    for (i = 0; i<T; i++)
    {
    int min=MAXWT,minJ;
        scanf("%d %d", &R, &C);

        int count = 0, src = -1;
        for (j = 0; j<R ; j++)
        {
            for(k=0;k<C;k++)
            {
                scanf("%d", &Arr[j][k].wt);
                Arr[j][k].x = j; Arr[j][k].y = k;
                //Arr[j][k].p = count;
                Arr2[j][k]=Arr[j][k];
                Parent[j][k] = dummy;
                //count++;
            }
        }

        for (j = 0; j < C; j++)// for home row.
        {
            answer[j].wt=MAXWT;
        }
        count = 0;
        for (j = 0; j < C; j++)// for home row.
        {
            BFS(j,R-1);
            resetArr();
        }
        for(j=0 ; j< C; j++)
        {
            if(answer[j].wt < min)
            {
                min = answer[j].wt;
                minJ = j;
            }
        }
        printf("Case #%d\n", i + 1);
        printf("%d\n", answer[minJ].wt);
//        printPath(answer[minJ].x,answer[minJ].y);
    }
    return 0;
}
#if 0
6  --> Number of test cases
3 3  -->  Test case#1: N= 3, M=3
1 2 3   -->  1st row:  Target row, cell cost values
4 8 -2  -->  2nd row: cost cell values
1 5 3   -->  3rd row: Home row, cost cell values
3 3  -->  Test case#2: N= 3, M=3
1 2 3  --> 1 st row: ... and so on ...
-7 8 -2  --> ... so on ...
1 5 3
7 8
1 1 9 9 9 9 9 9
9 9 -88 1 9 9 9 9
9 9 9 1 1 9 9 9
1 1 1 1 -99 9 9 9
-10 1 8 9 9 1 9 9
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
1 9 9 1 -10 9 9
1 9 9 1 1 9 9
9 -88 9 1 8 1 9
9 1 1 1 9 1 9
9 9 1 -99 9 1 9 
9 9 9 9 1 9 9
9 9 9 9 9 1 9
9 9 9 9 9 9 1
10 7
1 9 -9 -99 -10 9 9
1 9 9 1 10 9 9
1 9 9 1 -10 -69 9
1 9 9 1 1 9 9
9 -88 9 1 8 1 9
9 1 1 1 9 1 9
9 9 1 -99 9 1 9 
9 9 9 9 1 9 9
9 9 9 9 9 1 9
9 9 9 9 9 9 1
----------------------------------
Output:
Case #1
0
3
3 1 2 3 1 1
Case #2
-1
3
3 3 2 1 1 3
Case #3
-176
5
7 8 6 6 4 5 2 3 1 1
Case #4
12
4
7 6 5 5 3 4 1 5
Case #5
- 176
5
8 7 6 6 5 4 3 2 1 1
Case #6
- 344
7
10 7 8 6 7 4 5 2 4 4 3 6 1 4
#endif
