#include<queue>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int * Level,*Parent,Nnodes,Nedges,src,dst;
struct node
{
    int child;
    node * next;
};
node** AdjLst;
int isPathToSource(int start)
{
    if(start == -1)
        return -1;
    else if(start == src )
        return 1;
    else
    {
        start = Parent[start];
        isPathToSource(start);
    }
}
void BFS(int start)
{
    int i,j,foundPath=-1;
    queue<int> Q;
    for (i = 0; i < Nnodes; i++)
    {
        Parent[i] = Level[i] = -1;
    }
    Level[start] = Parent[start] = 0;
    Q.push(start);
    while(!Q.empty())
    {
        int explore = Q.front();
        Q.pop();
        node * t = AdjLst[explore];
        while(t)
        {
            if(Level[t->child] == -1)
            {
                Level[t->child] = Level[explore] + 1;
                Parent[t->child] = explore;  
                Q.push(t->child);
            }
            t=t->next;
        }
    }
    if(Level[dst] != -1)
    {
        if(isPathToSource(src) == 1)
            printf("%d",Level[dst]);
    }
    else
        printf("%d",0);
}
void addChild(int prn,int child)
{
    node * N = (node*)malloc(sizeof(node));
    N->child = child;
    N->next=NULL;
    if(AdjLst[prn] == NULL)
        AdjLst[prn]=N;
    else
    {
        node * t = AdjLst[prn];
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
    int i,j,k;
    scanf("%d%d",&Nnodes,&Nedges);
    Level = (int*)malloc(Nnodes * sizeof(int));
    Parent = (int*)malloc(Nnodes * sizeof(int));
    AdjLst = (node**) malloc(Nnodes * sizeof(node*));
    for(i = 0; i< Nnodes;i++)
    {
        AdjLst[i]= NULL;
    }
    for(i = 0;i< Nedges;i++)
    {
        int p,q;
        scanf("%d%d",&p,&q);
        addChild(p-1,q-1);
        addChild(q-1,p-1);
    }
    scanf("%d%d",&src,&dst);
    src--;dst--;
    BFS(src);
    return 0;
}
