#include<stdio.h>
#include"stdafx.h"
#include<stdlib.h>
#include<limits.h>

typedef struct _Q
{
	int vertex;
	struct _Q* next;
	struct _Q* tail;
}Queue;
typedef struct _list
{
	int child;
	struct _list * next;
}List;
typedef struct _cell
{
	int n;
	int e;
	int w;
	int s;
}cell;
cell Cell[10000];
Queue *Q = NULL;
int Level[10000];
int R, C, L, X, Y;
int Arr[100][100];
int _4[4] = { 0 };//NEWS
void isSafe(int _p)
{
	int p;
	p = _p;
	_4[0] = _4[1] = _4[2] = _4[3] = 0;
	p = p - C;//N
	if (Cell[_p].n == 1 && p >= 0 && p < (R*C))
		if (Cell[p].s == 1)
			_4[0] = 1;

	p = _p;
	p = p + 1;//E
	if (Cell[_p].e == 1 && p >= 0 && p < (R*C))
		if (Cell[p].w == 1)
			_4[1] = 1;

	p = _p;
	p = p - 1;//W
	if (Cell[_p].w == 1 && p >= 0 && p < (R*C))
		if (Cell[p].e == 1)
			_4[2] = 1;

	p = _p;
	p = p + C;//S
	if (Cell[_p].s == 1 && p >= 0 && p < (R*C))
		if (Cell[p].n == 1)
			_4[3] = 1;
}
void updateCell(int p, int val)
{
	switch (val)
	{
	case 1:
		Cell[p].n = 1;
		break;
	case 2:
		Cell[p].e = 1;
		break;
	case 3:
		Cell[p].n = 1;
		Cell[p].e = 1;
		break;
	case 4:
		Cell[p].s = 1;
		break;
	case 5:
		Cell[p].s = 1;
		Cell[p].n = 1;
		break;
	case 6:
		Cell[p].e = 1;
		Cell[p].s = 1;
		break;
	case 7:
		Cell[p].n = 1;
		Cell[p].e = 1;
		Cell[p].s = 1;
		break;
	case 8:
		Cell[p].w = 1;
		break;
	case 9:
		Cell[p].n = 1;
		Cell[p].w = 1;
		break;
	case 10:
		Cell[p].e = 1;
		Cell[p].w = 1;
		break;
	case 11:
		Cell[p].n = 1;
		Cell[p].e = 1;
		Cell[p].w = 1;
		break;
	case 12:
		Cell[p].s = 1;
		Cell[p].w = 1;
		break;
	case 13:
		Cell[p].n = 1;
		Cell[p].s = 1;
		Cell[p].w = 1;
		break;
	case 14:
		Cell[p].e = 1;
		Cell[p].w = 1;
		Cell[p].s = 1;
		break;
	}
}
void enQ(int v)
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
int deQ()
{
	int n;
	if (Q == NULL)
		return -1;
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

void BFS(int s, int L)
{
	int i;
	Level[s] = 0;
	enQ(s);
	while (!isQEmpty())
	{
		int v = deQ();
		int val;
		isSafe(v);
		for (i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0://N
				val = v - C;
				if (Level[val]== -1 && _4[i] == 1)
				{
					Level[val] = Level[v] + 1;
					if (Level[val] < L)
						enQ(val);
				}
				break;
			case 1://E
				val = v + 1;
				if (Level[val] == -1 && _4[i] == 1)
				{
					Level[val] = Level[v] + 1;
					if (Level[val] < L)
						enQ(val);
				}
				break;
			case 2://W
				val = v - 1;
				if (Level[val] == -1 && _4[i] == 1)
				{
					Level[val] = Level[v] + 1;
					if (Level[val] < L)
						enQ(val);
				}
				break;
			case 3://S
				val = v + C;
				if (Level[val] == -1 && _4[i] == 1)
				{
					Level[val] = Level[v] + 1;
					if (Level[val] < L)
						enQ(val);
				}
				break;
			default:
				break;
			}
			
		}
	}
}

int main()
{

	int i, j, k;
	int T;
	freopen("Text.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (i = 0; i<T; i++)
	{
		scanf("%d %d %d %d %d", &R, &C, &L, &X, &Y);


		for (j = 0; j < 10000; j++)
			Level[j] = -1;

		X = X - 1; Y = Y - 1;
		int count = 0, src = -1;
		for (j = 0; j<R; j++)
		{
			for (k = 0; k < C; k++, count++)
			{
				scanf("%d", &Arr[j][k]);
				if (j == X && k == Y)
					src = count;
			}
		}
		count = 0;
		for (j = 0; j < R; j++)
		{
			for (k = 0; k < C; k++, count++)
			{
				updateCell(count, Arr[j][k]);
			}
		}
		BFS(src, L);
		int answer = 0;
		count = 0;
		for (j = 0; j < R; j++)
		{
			for (k = 0; k < C; k++, count++)
			{
				if (Level[count] > 0)
				{
					answer++;
				}
				printf(" %d ", Level[count]);
			}
			printf("\n");
		}
		printf("Case #%d\n", i + 1);
		printf("%d\n", answer + 1);
	}
	return 0;
}
#if 0
5
5 5 1 3 2
14 14 10 7 4
11 13 14 13 5
7 7 14 11 5
7 11 11 14 13
7 11 14 14 9
5 5 2 3 2
14 14 10 7 4
11 13 14 13 5
7 7 14 11 5
7 11 11 14 13
7 11 14 14 9
5 5 3 3 2
14 14 10 7 4
11 13 14 13 5
7 7 14 11 5
7 11 11 14 13
7 11 14 14 9
5 5 5 3 2
14 14 10 7 4
11 13 14 13 5
7 7 14 11 5
7 11 11 14 13
7 11 14 14 9
6 5 7 3 2
14 14 10 7 4
11 13 14 13 5
7 7 14 11 5
7 11 11 14 13
7 11 14 14 9
7 11 14 14 9

correct:
Case #1
4
Case #2
9
Case #3
15
Case #4
22
Case #5
29

case 1://N
case 2://E
case 3://NE
case 4://S
case 5://SN
case 6://ES
case 8://W
case 7://NES
case 9://NW
case 10://EW
case 11://NEW
case 12://SW
case 13://NSW
case 14://EWS

#endif
