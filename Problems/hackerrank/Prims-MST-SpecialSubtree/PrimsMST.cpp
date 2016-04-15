//#include"stdafx.h"
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
    //visitedW[src] = 1;
    int WT = 0;
    Distance[src] = 0;
    //Wnode* t = WAdjLst[src];
    /*while (t)
      {
      Nbr[t->child] = 0;
      if (Distance[t->child] > t->weight)
      Distance[t->child] = t->weight;
      t = t->next;
      }*/
    for (int i = 0; i < Nnodes; i++)
    {
        int wt;
        /*Wnode* tt = WAdjLst[i];          // mistake was to only choose min edge among childs of current node, instead of searching all edges.(which min() does correctly)
        while (tt)
        {
            if (visitedW[tt->child] == -1 && Distance[tt->child] < wt)
            {
                wt = Distance[tt->child];
                minChild = tt->child;
            }
            tt = tt->next;
        }*/
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
    //freopen("Text.txt","r",stdin);
    //for (int t = 0; t < T; t++)
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
        int src;
        cin >> src;

        ans2 = Prims(src-1);
        printf("%d\n", ans2);
    }
    return 0;
}

