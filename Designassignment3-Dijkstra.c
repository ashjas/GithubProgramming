#include<stdio.h>
#include<stdlib.h>
int Nnodes,Nedges,src,dst,*visitedW,*Distance;
int maxWeight,maxNode = 0;
typedef struct Wnode
{
    int child;
    int weight;
    struct Wnode * next;
}Wnode;
Wnode** WAdjLst;
void dijkstraPath(int start)
{
    int i,j;
    for (i = 0; i < maxNode; i++)
    {
        Distance[i] = maxWeight;
    }
    Distance[start] = 0;
    for(i = 0; i<maxNode; i++)
    {
        int u;
        int minDis=maxWeight;
        for (j=0;j<maxNode;j++)
        {
            if(visitedW[j] == -1)
                if (Distance[j]<minDis)
                {
                    minDis = Distance[j];
                    u = j;
                }
        }
        visitedW[u] = 1;
        Wnode * n = WAdjLst[u];
        while(n)
        {
            if(visitedW[n->child] == -1 && Distance[n->child] > (Distance[u] + n->weight))
                Distance[n->child] =  Distance[u] + n->weight;
            n = n->next;
        }
    }
    if(Distance[dst] == maxWeight)
        printf("%s\n","NO");
    else
        printf("%s\n%d\n","YES",Distance[dst]);


}
void addChildW(int prn,int child, int weight)
{
    Wnode * N = (Wnode*)malloc(sizeof(Wnode));
    N->child = child;
    N->weight = weight;
    N->next=NULL;
    if(WAdjLst[prn] == NULL)
        WAdjLst[prn]=N;
    else
    {
        Wnode * t = WAdjLst[prn];
        while(t)
        {
            if(t->next == NULL)
            {
                t->next=N;
                break;
            }
            t=t->next;
        }
    }
}
int main()
{
    int i;
    maxWeight = 0;
    Nnodes = 2000;
    scanf("%d%d%d",&Nedges,&src,&dst);
    Distance = (int*)malloc(Nnodes * sizeof(int));
    WAdjLst = (Wnode**) malloc(Nnodes * sizeof(Wnode*));
    visitedW = malloc(Nnodes * sizeof(int));
    for(i = 0; i< Nnodes;i++)
    {
        WAdjLst[i]= NULL;
        visitedW[i] = -1;
    }
    for(i = 0;i< Nedges;i++)
    {
        int p,q,r;
        scanf("%d%d%d",&p,&r,&q);
        addChildW(p-1,q-1,r);
        addChildW(q-1,p-1,r);
        maxWeight += r;
        if(p > maxNode || q > maxNode)
            maxNode = p > q ? p : q;
    }
    maxWeight++;
    src--;dst--;
    dijkstraPath(src);
    return 0;
}
