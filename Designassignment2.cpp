//#include<iostream>
#include<queue>
#include<map>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int /** Level,*Parent,*/Nnodes,Nedges,src,dst;
struct adjList
{
    vector<int> vertices;
};
map< int,adjList > AdjMx;
vector<int> Level,Parent;
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
        Parent.push_back(-1);
        Level.push_back(-1);
        //Parent[i] = Level[i] = -1;
    }
    Level[start] = Parent[start] = 0;
    Q.push(start);
    while(!Q.empty())
    {
        int explore = Q.front();
        Q.pop();
        for(j = 0;j < AdjMx[explore].vertices.size(); j++)
        {
            //if(AdjMx[explore].vertices[j] == 1)
            {
                //if(Level[j] == -1)
                if(Level[AdjMx[explore].vertices[j]] == -1)
                {
                    Level[AdjMx[explore].vertices[j]] = Level[explore] + 1;
                    Parent[AdjMx[explore].vertices[j]] = explore;  
                    Q.push(AdjMx[explore].vertices[j]);
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
int main()
{
    int i,j,k;
    scanf("%d%d",&Nnodes,&Nedges);
    //Level = (int*)malloc(Nnodes * sizeof(int));
    //Parent = (int*)malloc(Nnodes * sizeof(int));
    //AdjMx=(int **)malloc(Nnodes * sizeof(int*));
    //for(i = 0; i< Nnodes;i++)
    {
      //  AdjMx[i] = (int *)malloc(Nnodes * sizeof(int));
    //    for(j=0;j<Nnodes;j++)
      //      AdjMx[i][j]=0;
    }
    for(i = 0;i< Nedges;i++)
    {
        int p,q;
        scanf("%d%d",&p,&q);
        //AdjMx[q-1][p-1] = AdjMx[p-1][q-1] = 1;
        adjList a;a.vertices.push_back(q);
        AdjMx[p]=a;
        //AdjMx.push_back(a);
        //AdjMx[p].vertices[q] = 1;
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
