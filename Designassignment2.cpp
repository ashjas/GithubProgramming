//#include<iostream>
#include<queue>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int * Level,*Parent,Nnodes,Nedges,src,dst;
int ** AdjMx;
void BFS(int start)
{
    int i,j;
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
        for(j = 0;j < Nnodes; j++)
        {
            if(AdjMx[explore][j] == 1)
            {
                if(Level[j] == -1)
                {
                    Level[j] = Level[explore] + 1;
                    Parent[j] = explore;  
                    Q.push(j);
                }
            }
        }
    }
    printf("\nParentArray:");
    for(i = 0;i<Nnodes; i++)
        if(Parent[i] != -1)
            printf("\nParent of %d:%d",i+1,Parent[i]+1);
    printf("\nLevelArray:");
    for(i = 0;i<Nnodes; i++)
        if(Level[i] != -1)
            printf("\nLevel of %d:%d",i+1,Level[i]);
}
int main()
{
    int i,j,k;
    scanf("%d%d",&Nnodes,&Nedges);
    Level = (int*)malloc(Nnodes * sizeof(int));
    Parent = (int*)malloc(Nnodes * sizeof(int));
    AdjMx=(int **)malloc(Nnodes * sizeof(int*));
    for(i = 0; i< Nnodes;i++)
    {
        AdjMx[i] = (int *)malloc(Nnodes * sizeof(int));
        for(j=0;j<Nnodes;j++)
            AdjMx[i][j]=0;
    }
    for(i = 0;i< Nedges;i++)
    {
        int p,q;
        scanf("%d%d",&p,&q);
        AdjMx[q-1][p-1] = AdjMx[p-1][q-1] = 1;
    }
    scanf("%d%d",&src,&dst);
/*    printf("\nAdjecency Mtrix:\n");
    for(i=0;i<Nnodes;i++)
    {
        for(j=0;j<Nnodes;j++)
            printf("%d:",AdjMx[i][j]);
        printf("\n");
    }
    printf("\nsrc:%d,dst:%d",src,dst)/**/;
    BFS(0);
    return 0;

}
