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
    int weight;
    struct _list * next;
}List;
Queue *Q = NULL;
List **AdjList = NULL;
int *Visited = NULL;
int *Dist = NULL;
int *Parent = NULL;
int Nnodes,Edges;
int MAX_DIST = INT_MAX;
void enQ(int v)
{
    Queue * q = malloc(sizeof(Q));
    q->vertex = v;
        q->next = NULL;
        q->tail = q;
    if(Q == NULL)
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
    if(Q == NULL)
        return -1;
    n = Q->vertex;
    Queue *q = Q;
    if(Q->next)
        Q->next->tail = Q->tail;// Q->next will be NULL for last item.
    Q = Q->next;
    free(q);
    return n;
}
int isQEmpty()
{
    if(Q == NULL)
        return 1;
    return 0;
}
void addEdge(int p, int c, int w)
{
    List * l = malloc(sizeof(List));
    l->child = c;
    l->weight = w;
    l->next = NULL;
    if(AdjList[p] == NULL)   
    {
        AdjList[p] = l;
    }
    else
    {
        List * tmp = AdjList[p];
        while(tmp)
        {
            if(tmp->child == c)
            {
                if(tmp->weight > w)
                    tmp->weight = w;
                return;
            }
            if(!tmp->next)
                break;
            tmp = tmp->next;
        }
        /*
        while(tmp->next)
        {
            if(tmp->next->child == c)// this check is important, as it updates an edge b/w prn->child if a newer edge has lesser weight.
            {
                if(tmp->next->weight > w)
                    tmp->next->weight = w;
                return;
            }
            tmp = tmp->next;
        }*/
        tmp->next = l;
    }
}
int distToSource(int d)
{
    int dist=0;
    while(Parent[d]!=-1)
    {
        dist+=Dist[d];
        d = Parent[d];
    }
    return dist;

}
void dijkstraPath(int start)
{
    int i,j;
    for (i = 0; i < Nnodes; i++)
    {
       Dist[i] = MAX_DIST;
    }
    Dist[start] = 0;
    for(i = 0; i<Nnodes; i++)
    {
        int u;
        int minDis=MAX_DIST;
        for (j=0;j<Nnodes;j++)
        {
            if(Visited[j] == 0)
                if (Dist[j]<minDis)
                {
                    minDis = Dist[j];
                    u = j;
                }
        }
        Visited[u] = 1;
        List * n = AdjList[u];
        while(n)
        {
            if(Visited[n->child] == 0 && Dist[n->child] > (Dist[u] + n->weight))
                Dist[n->child] =  Dist[u] + n->weight;
            n = n->next;
        }
    }
    /*printf("\nDijkstra's Distance:\n");
    for(i = 0; i < Nnodes; i++)
        printf("%d ",Dist[i]);
*/

}
void Dijkstra(int s)
{
    Dist[s] = 0;
    enQ(s);
    while(!isQEmpty())
    {
        int v = deQ();
        List *l = AdjList[v];
        Visited[v] = 1;
        while(l)
        {
            if(Visited[l->child] == 0 && l->weight + Dist[v] < Dist[l->child])
            {
                Dist[l->child] = l->weight + Dist[v];
                if(Parent[l->child] == -1)
                    Parent[l->child] = v;
                else
                {
                    int newDist = distToSource(l->child);
                    //printf("here\n");
                    if(Dist[l->child] > newDist)
                    {
                        Dist[l->child] = newDist;
                    }
                    else
                    {
                        Parent[l->child] = v;
                    }
                }
                enQ(l->child);
            }
            l = l->next;
        }
    }
}
void cleanUpAdjList()
{
    int i;
    for(i=0;i<Nnodes;i++)
    {
        if(AdjList[i] != NULL)
        {
            List * l = AdjList[i];
            while(l)
            {
                List * t = l;
                l = l->next;
                free(t);
            }
        }
    }
    free(AdjList);
}
int main()
{

    int i,j,k;
    int T,N,E,S,p,c,w;
    scanf("%d",&T);
    for(i=0;i<T;i++)
    {
        scanf("%d %d",&N,&E);
        Nnodes = N;
        Edges = E;
        AdjList = (List**)malloc(N * sizeof(List*));
        Visited = (int*)malloc(N * sizeof(int));
        Dist= (int*)malloc(N * sizeof(int));
        Parent= (int*)malloc(N * sizeof(int));
        for(j=0;j<N;j++)
        {
            AdjList[j] = NULL;
            Visited[j] = 0;
            Dist[j] = MAX_DIST ;
            Parent[j] = -1 ;
        }
        for(j=0;j<E;j++)
        {
            scanf("%d %d %d", &p , &c , &w);           
            addEdge(p-1,c-1,w);
            addEdge(c-1,p-1,w);
        }
        scanf("%d", &S);
        dijkstraPath(S-1);
        for(j=0;j<N;j++)
        {
            if(Dist[j] == 0)
                continue;
            if(Dist[j] == MAX_DIST)
                printf("-1 ");
            else
                printf("%d ",Dist[j]);
        }
        printf("\n");
        free(Visited);
        free(Dist);
        free(Parent);
        cleanUpAdjList();
    }

}
