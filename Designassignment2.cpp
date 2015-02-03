//#include<iostream>
#include<queue>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;
int * Level,*Parent,Nnodes,Nedges,src,dst;
struct node
{
    int child;
    node * next;
};
vector<node*> AdjLst;
//int ** AdjMx;
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
        //for(j = 0;j < Nnodes; j++)
        node * t = AdjLst[explore];
        while(t)
        {
            //if(AdjMx[explore][j] == 1)
            {
                if(Level[t->child] == -1)
                {
                    Level[t->child] = Level[explore] + 1;
                    Parent[t->child] = explore;  
                    Q.push(t->child);
                }
            }
        }
    }
    /*
    printf("\nParentArray:");
    for(i = 0;i<Nnodes; i++)
        if(Parent[i] != -1)
            printf("\nParent of %d:%d",i+1,Parent[i]+1);
    printf("\nLevelArray:");
    for(i = 0;i<Nnodes; i++)
        if(Level[i] != -1)
            printf("\nLevel of %d:%d",i+1,Level[i]);
    printf("\n");
    /**/
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
    //AdjMx=(int **)malloc(Nnodes * sizeof(int*));

    for(i = 0; i< Nnodes;i++)
    {
        //AdjMx[i] = (int *)malloc(Nnodes * sizeof(int));
    //    for(j=0;j<Nnodes;j++)
      //      AdjMx[i][j]=0;
        AdjLst.push_back(NULL);

    }
    for(i = 0;i< Nedges;i++)
    {
        int p,q;
        scanf("%d%d",&p,&q);
        //AdjMx[q-1][p-1] = AdjMx[p-1][q-1] = 1;
        addChild(p,q);
    }
    scanf("%d%d",&src,&dst);
    src--;dst--;
/*    printf("\nAdjecency Mtrix:\n");
    for(i=0;i<Nnodes;i++)
    {
        for(j=0;j<Nnodes;j++)
            printf("%d:",AdjMx[i][j]);
        printf("\n");
    }
    printf("\nsrc:%d,dst:%d",src,dst)/**/;
    BFS(src);
    return 0;

}
