
#include<stdio.h>
#include<stdlib.h>

typedef struct _list
{
	int cur = 0;
	int data[1000];
}List;


typedef struct _Queue
{
	int vertex;
	int data[1000];
	int front = 0;
	int tail = 0;
}Queue;

Queue Q;
List L[1000];
int GLevel[1000];
int Nnodes;
void add2List(int u, int v)
{
	L[u].data[L[u].cur++] = v;
}
void add2Q(int v)
{
	Q.data[Q.tail++] = v;
}

int dequeue()
{
	int v = Q.data[Q.front++];
	return v;
}

int isQEmpty()
{
	if (Q.front == Q.tail)
		return 1;
	else
		return 0;
}
void addEdge(int prn, int child)
{
	int i = 0;
	for (i = 0; i < L[prn].cur; i++)
	{
		if (L[prn].data[i] == child)
			return;
	}
	L[prn].data[L[prn].cur++] = child;
}

void BFS(int start)
{
	int i;
	GLevel[start] = 0;
	add2Q(start);
	while (!isQEmpty())
	{
		int v = dequeue();
		for (i = 0; i < L[v].cur; i++)
		{
			if (GLevel[L[v].data[i]] == -1)
			{
				GLevel[L[v].data[i]] = GLevel[v] + 1;
				add2Q(L[v].data[i]);
			}
		}
	}
	for (i = 0; i<Nnodes; i++)
	{
		if (GLevel[i] > 0)
			printf("%d ", GLevel[i] * 6);
		else if (GLevel[i] != 0)
			printf("%d ", GLevel[i]);
	}
	printf("\n");
}
int main()
{
	int i, T, Edges;
	scanf("%d", &T);
	for (i = 0; i<T; i++)
	{
		int j = 0, prn, chd, source;
		//int  Level[1000];
		scanf("%d %d", &Nnodes, &Edges);
		for (j = 0; j<Nnodes; j++)
		{
			GLevel[j] = -1;
		}
		for (j = 0; j<Edges; j++)
		{
			scanf("%d %d", &prn, &chd);
			addEdge(prn - 1, chd - 1);
			addEdge(chd - 1, prn - 1);
		}
		scanf("%d", &source);
		BFS(source - 1);
	}
	scanf("%d", &i);
}
