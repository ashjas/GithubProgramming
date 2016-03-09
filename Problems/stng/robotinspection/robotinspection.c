#include<stdio.h>
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
Queue *Q = NULL;
List **AdjList = NULL;
int *Visited = NULL;
//int *Level = NULL;
int Level[10000];
int *Parent = NULL;
int R, C, L, X, Y;
int MAX_DIST = INT_MAX;
int Arr[100][100];
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
void addEdge(int p, int val)
{
	List *l, *l2, *l3;
	l = l2 = l3 = NULL;
	int a;
	switch (val)
	{
	case 1://N

		a = p - C;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		break;
	case 2://E

		a = p + 1;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		break;
	case 4://W

		a = p - 1;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		break;
	case 8://S

		a = p + C;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		break;
	case 7://NEW

		a = p - C;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		a = p + 1;
		if (a >= 0 && a < R*C)
		{
			l2 = (List*)malloc(sizeof(List));
			l2->child = a;
			l2->next = l;
		}
		a = p - 1;
		if (a >= 0 && a < R*C)
		{
			l3 = (List*)malloc(sizeof(List));
			l3->child = a;
			l3->next = l2;
		}
		break;
	case 9://NS
		a = p - C;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		a = p + C;
		if (a >= 0 && a < R*C)
		{
			l2 = (List*)malloc(sizeof(List));
			l2->child = a;
			l2->next = l;
		}
		break;
	case 10://ES
		a = p + 1;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		a = p + C;
		if (a >= 0 && a < R*C)
		{
			l2 = (List*)malloc(sizeof(List));
			l2->child = a;
			l2->next = l;
		}
		break;
	case 11://NES
		a = p - C;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		a = p + 1;
		if (a >= 0 && a < R*C)
		{
			l2 = (List*)malloc(sizeof(List));
			l2->child = a;
			l2->next = l;
		}
		a = p + C;
		if (a >= 0 && a < R*C)
		{
			l3 = (List*)malloc(sizeof(List));
			l3->child = a;
			l3->next = l2;
		}
		break;
	case 12://SW ------
		a = p + C;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		a = p - 1;
		if (a >= 0 && a < R*C)
		{
			l2 = (List*)malloc(sizeof(List));
			l2->child = a;
			l2->next = l;
		}
		break;
	case 13://NSW
		a = p - C;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		a = p - 1;
		if (a >= 0 && a < R*C)
		{
			l2 = (List*)malloc(sizeof(List));
			l2->child = a;
			l2->next = l;
		}
		a = p + C;
		if (a >= 0 && a < R*C)
		{
			l3 = (List*)malloc(sizeof(List));
			l3->child = a;
			l3->next = l2;
		}
		break;
	case 14://EWS
		a = p + 1;
		if (a >= 0 && a < R*C)
		{
			l = (List*)malloc(sizeof(List));
			l->child = a;
			l->next = NULL;
		}
		a = p - 1;
		if (a >= 0 && a < R*C)
		{
			l2 = (List*)malloc(sizeof(List));
			l2->child = a;
			l2->next = l;
		}
		a = p + C;
		if (a >= 0 && a < R*C)
		{
			l3 = (List*)malloc(sizeof(List));
			l3->child = a;
			l3->next = l2;
		}
		break;
	}

	if (AdjList[p] == NULL)
	{
		if (l3 != NULL)
			AdjList[p] = l3;
		else if (l2 != NULL)
			AdjList[p] = l2;
		else
			AdjList[p] = l;
	}

}
void BFS(int s, int L)
{
	Level[s] = 0;
	enQ(s);
	while (!isQEmpty())
	{
		int v = deQ();
		Visited[v] = 1;
		List * l = AdjList[v];
		while (l)
		{
			if (Level[l->child] == -1)
			{
				Level[l->child] = Level[v] + 1;
				if (Level[l->child] < L)
					enQ(l->child);
			}
			l = l->next;
		}
	}
}
/*void cleanUpAdjList()
{
int i;
for (i = 0; i<Nnodes; i++)
{
if (AdjList[i] != NULL)
{
List * l = AdjList[i];
while (l)
{
List * t = l;
l = l->next;
free(t);
}
}
}
free(AdjList);
}*/
int main()
{

	int i, j, k;
	int T, N, E, S, p, c, w;
	freopen("Text.txt", "r", stdin);
	setbuf(stdout, NULL);
	scanf("%d", &T);
	for (i = 0; i<T; i++)
	{
		scanf("%d %d %d %d %d", &R, &C, &L, &X, &Y);

		AdjList = (List**)malloc(R * C * sizeof(List*));
		Visited = (int*)malloc(R * C * sizeof(int));
		//Level = (int*)malloc(R * C * sizeof(int));
		Parent = (int*)malloc(R * C * sizeof(int));
		for (j = 0; j<(R*C); j++)
		{
			AdjList[j] = NULL;
			Visited[j] = 0;
			Level[j] = -1;
			Parent[j] = -1;
		}
		for (j = 0; j < 10000;j++)
			Level[j] = -1;
		
		X = X - 1; Y = Y - 1;
		int count = 0, src = -1;
		for (j = 0; j<R; j++)
		{
			for (k = 0; k < C; k++, count++)
			{
				scanf("%d", &Arr[j][k]);
				addEdge(count, Arr[j][k]);
				if (j == X && k == Y)
					src = count;
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
                                        //printf(" %d",count);
                                }
                                printf(" %d ",Level[count]);
			}
                        printf("\n");
		}

		printf("Case #%d\n",i+1);
		printf("%d\n", answer+1);
		//free(Visited);
		//free(Dist);
		//free(Parent);
		//cleanUpAdjList();
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

#endif
