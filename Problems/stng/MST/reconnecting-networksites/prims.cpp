#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int Nnodes, Nedges, src, dst, *visitedW, *Distance, *Nbr, DSize;
int maxWeight, maxNode = 0, size = 0;
typedef struct Wnode
{
	int child;
	int weight;
	struct Wnode * next;
}Wnode;
Wnode** WAdjLst;

void addChildW(int prn, int child, int weight)
{
	Wnode * N = (Wnode*)malloc(sizeof(Wnode));
	N->child = child;
	N->weight = weight;
	N->next = NULL;
	if (WAdjLst[prn] == NULL)
		WAdjLst[prn] = N;
	else
	{
		Wnode * t = WAdjLst[prn];
		while (t)
		{
			/*if (t->child == N->child)
			{
			if (t->weight > N->weight)
			t->weight = N->weight;
			break;
			}*/
			if (t->next == NULL)
			{
				t->next = N;
				break;
			}
			t = t->next;
		}
	}
}
int min(int & wtt)
{
	int wt = INT_MAX;
	int minChild = -1;
	for (int i = 0; i < Nnodes; i++)
	{
		//Wnode* tt = WAdjLst[i];
		//while (tt)
		{
			if (visitedW[i] == -1 && Distance[i] <= wt)
			{
				wt = Distance[i];
				minChild = i;
			}
			//tt = tt->next;
		}
	}
	wtt = wt;
	return minChild;
}
int Prims(int src)
{
	
	int WT = 0;
	Distance[src] = 0;

	for (int i = 0; i < Nnodes; i++)
	{
		int wt;
		int minChild = min(wt);

		if (minChild != -1)
		{
			visitedW[minChild] = 1;
			WT = WT + wt;// wt of MST


			Wnode* ttt = WAdjLst[minChild];
			while (ttt)
			{
				if (visitedW[ttt->child] == -1 && Distance[ttt->child] > ttt->weight)
				{
					Distance[ttt->child] = ttt->weight;
					Nbr[ttt->child] = minChild;
				}
				ttt = ttt->next;
			}

		}
	}
	return WT;
}
int main()
{
	int T;
	freopen("Text.txt","r",stdin);
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		/*input lines for first ans*/
		int a, b, ans1 = 0, ans2 = 0, maxInputWeight = 0;
		cin >> Nnodes;
		WAdjLst = (Wnode**)malloc(Nnodes * sizeof(Wnode*));
		visitedW = (int*)malloc(Nnodes * sizeof(int));
		Distance = (int*)malloc(Nnodes * sizeof(int));
		Nbr = (int*)malloc(Nnodes * sizeof(int));
		for (int i = 0; i < Nnodes; i++)
		{
			WAdjLst[i] = NULL;
			visitedW[i] = -1;
			Distance[i] = INT_MAX;
			Nbr[i] = -1;
		}
		for (int i = 0; i < Nnodes - 1; i++)
		{
			cin >> a >> a >> b;
			ans1 += b;
		}
		/*input lines for additional K lines*/
		int kLines, w;
		cin >> kLines;
		for (int i = 0; i < kLines; i++)
		{
			cin >> a >> b >> w;
			if (a != b)
			{
				addChildW(a - 1, b - 1, w);
				addChildW(b - 1, a - 1, w);
			}
			maxInputWeight += w;
		}
		/*input lines for Original M lines*/
		int MLines;
		cin >> kLines;
		for (int i = 0; i < kLines; i++)
		{
			cin >> a >> b >> w;
			if (a != b)
			{
				addChildW(a - 1, b - 1, w);
				addChildW(b - 1, a - 1, w);
			}
			maxInputWeight += w;
		}

		ans2 = Prims(0);
		printf("Case #%d\n%d %d\n", t + 1, ans1, ans2);
	}
	return 0;
}
