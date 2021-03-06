#include<stdio.h>
#include<stdlib.h>
/*
 Can classify edges using pre and post numbers
 Tree/Forward edge (u,v) : Interval [pre(u),post(u)] contains [(pre(v),post(v)]
 Backward edge (u,v): Interval [pre(v),post(v)] contains [(pre(u),post(u)]
 Cross edge (u,v): Intervals [(pre(u),post(u)] and [(pre(v),post(v)] disjoint
 */
int * Level,*Parent,Nnodes,Nedges,src,dst,*visited,*visitedW,*component,*Distance;
int * pre,*post,count = 0,comp = 1;
int maxWeight;
typedef struct node
{
    int child;
    struct node * next;
}node;
typedef struct Wnode
{
    int child;
    int weight;
    struct Wnode * next;
}Wnode;
typedef struct EDGES/* edges*/
{
    int s;
    int t;
    struct EDGES * next;
}EDGES;
struct EDGES * HEAD_TE = NULL;
struct EDGES * HEAD_SKIPPED = NULL;
struct EDGES * HEAD_NTE = NULL;
typedef struct Queue
{
    int vertex;
    struct Queue * tail;
    struct Queue * next;
}Queue;
int isQempty(Queue * Q)
{
    if(Q == NULL)
        return 1;
    else 
        return 0;
}
void pushToQ(Queue ** QQ, int vert)
{
    Queue *Q = *QQ;
    Queue *node = (Queue*) malloc(sizeof(Queue));
    node->vertex=vert;
    if(Q == NULL)
    {
        node->next = NULL;
        node->tail = node;
        Q = node;
    }
    else
    {
        node->next = NULL;
        Q->tail->next = node;
        Q->tail = node;
    }
    *QQ = Q;
}
int popQ(Queue ** QQ)
{
    if(*QQ == NULL)
        return -1;
    else
    {
        Queue *Q = *QQ;
        Queue * node = Q;
        int val = Q->vertex;
        Queue * tail = Q->tail;
        Q = Q->next;
        if(Q)
            Q->tail = tail;
        free(node);
        *QQ = Q;
        return val;
    }

}
node** AdjLst;
Wnode** WAdjLst;
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
    Queue *Q = NULL;
    for (i = 0; i < Nnodes; i++)
    {
        Parent[i] = Level[i] = -1;
    }
    Level[start] = Parent[start] = 0;
    pushToQ(&Q,start);
    while(!isQempty(Q))
    {
        int explore = popQ(&Q);
        if(explore == -1) break;
        node * t = AdjLst[explore];
        while(t)
        {
            if(Level[t->child] == -1)
            {
                Level[t->child] = Level[explore] + 1;
                Parent[t->child] = explore;  
                pushToQ(&Q,t->child);
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
void addEdge(EDGES ** EE ,int s,int t)
{
    EDGES * TreeEdges = *EE;

    EDGES * N = (EDGES*)malloc(sizeof(EDGES));
    N->s = s;
    N->t = t;
    N->next=NULL;
    if(TreeEdges == NULL)
        TreeEdges = N;
    else
    {
        EDGES * itr = TreeEdges;
        while(itr)
        {
            if(itr->next == NULL)
            {
                itr->next=N;
                break;
            }
            if((itr->s == s && itr->t == t ) || (itr->s == t && itr->t == s))/*This is to check if an edge is already added from both directions,so skip adding it second time.*/
            {
                free(N);
                break;
            }
            itr=itr->next;
        }
    }
    *EE = TreeEdges;
}
void DFS(int start)
{
    int i;
    visited[start] = 1;
    component[start] = comp;
    node *t = AdjLst[start];
    pre[start] = count;
    count++;
    while(t)
    {
        if(visited[t->child] != 1)
        {
            Parent[t->child] = start;
            addEdge(&HEAD_TE, start, t->child);
            DFS(t->child);
        }
        else
        {
            addEdge(&HEAD_SKIPPED, start, t->child);
        }
        t = t->next;
    }
    post[start] = count; 
    count++;
}
void dijkstraPath(int start)
{
    int i,j;
    for (i = 0; i < Nnodes; i++)
    {
       Distance[i] = maxWeight;
    }
    Distance[start] = 0;
    for(i = 0; i<Nnodes; i++)
    {
        int u;
        int minDis=maxWeight;
        for (j=0;j<Nnodes;j++)
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
    printf("\nDijkstra's Distance:\n");
    for(i = 0; i < Nnodes; i++)
        printf("%d ",Distance[i]);


}
int MIN(int a,int b)
{
    return a<b?a:b;
}
void bellmanFord(int s)
{
    int i,j,k;
    int * Distance = malloc(sizeof(int) * Nnodes);
    for(i=0;i<Nnodes;i++)
    {
        Distance[i] = maxWeight;
    }
    Distance[s] = 0;
    for(i=0;i<Nnodes;i++)
    {
        for(j=0;j<Nnodes;j++)
        {
            Wnode * n = WAdjLst[j];
            while(n)
            {
                //  if(Distance[n->child] > Distance[i] + n->weight)
                Distance[n->child]= MIN(Distance[n->child], Distance[j] + n->weight );
                n=n->next;
            }
        }
    }
    printf("\nbellmanFord paths:\n");
    for(j=0;j<Nnodes; j++)
    {
        printf("%d ",Distance[j]);
    }
}
void floyd_warshall_all_pairs_shortest_path()
{
    int i,j,k;
    
    int ***W = (int***)malloc(sizeof(int**) * Nnodes);
    for(i=0;i<Nnodes; i++)
        W[i] = (int**)malloc(sizeof(int *) * Nnodes);
    for(i=0;i<Nnodes; i++)
        for(j=0;j<Nnodes; j++)
            W[i][j] = (int*)malloc(sizeof(int ) * Nnodes);
    for(i=0;i<Nnodes; i++)
        for(j=0;j<Nnodes; j++)
            W[i][j][0] = maxWeight;
//    int W[8][8][8];
    for(i=0;i<Nnodes;i++)
        for(j=0;j<Nnodes;j++)
            for(k=0;k<Nnodes;k++)
                W[i][j][k] = maxWeight;
    /*
    for(i=0;i<Nnodes;i++)
        for(j=0;j<Nnodes;j++)
            W[i][j][0] = maxWeight;
*/
        printf("\n");
    for(i=0;i<Nnodes; i++)
    {
        Wnode * n = WAdjLst[i];
        while(n)
        {
            W[i][n->child][0] = n->weight;
            n= n->next;
        }
    }
    for(i=0;i<Nnodes; i++)
    {
        for(j=0;j<Nnodes; j++)
        {
            printf("%d ",W[i][j][0]);
        }
        printf("\n");
    }
    for(k=1;k<Nnodes;k++)
        for(i=0;i<Nnodes;i++)
            for(j=0;j<Nnodes;j++)
            {
                W[i][j][k]= MIN(W[i][j][k-1],W[i][k][k-1] + W[k][j][k-1]);
            }
    printf("\nall Ws\n");
    for(k=0;k<Nnodes; k++)
    {
        printf("\n--------%d:\n",k);
        printf("     %d %d %d %d %d %d %d %d\n",1,2,3,4,5,6,7,8);
        for(i=0;i<Nnodes; i++)
        {
            printf("r:%d: ",i+1);
            for(j=0;j<Nnodes; j++)
            {
                printf("%d ",W[i][j][k]);
            }
            printf("\n");
        }
    }
}
void printNTE(EDGES *TE, EDGES *Skipped)
{
    EDGES *te = TE;
    EDGES *sk = Skipped;
    int found = 0;
    while(sk)
    {
        te = TE;
        while(te)
        {
            if( (sk->s == te->s && sk->t == te->t) || (sk->s == te->t && sk->t ==te->s))
            {
                found = 1;
                break;
            }
            else
                found = 0;

            te = te->next;
        }
        if(!found)
        {
            addEdge(&HEAD_NTE,sk->s,sk->t);
        }
        sk = sk->next;
    }
    printf("\n");

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
void TopologicalOrder()
{
    int i,j,k;
    Queue * orderQ = NULL;
    Queue * finalQ = NULL;
    int * indegree = (int*)malloc(Nnodes * sizeof(int));
    int * LPT = (int*)malloc(Nnodes * sizeof(int));/*longest path array.*/
    for (i = 0; i< Nnodes; i++)
    {
        indegree[i] = 0;/*initialize all vertex indegrees to 0*/
        LPT[i] = 0;
    }
    for (i = 0; i< Nnodes; i++)/*find real indegrees*/
    {
        node * n = AdjLst[i];
        while(n)
        {
            indegree[n->child] += 1;
            n = n->next;
        }
    }
    for (i = 0; i< Nnodes; i++)
    {
        if(indegree[i] == 0)
            pushToQ(&orderQ , i);
    }
    printf("\nTopologically sorted order:\n");
    while(!isQempty(orderQ))
    {
        int enumerate = popQ(&orderQ);
        printf("%d ",enumerate+1);
        node * n = AdjLst[enumerate];
        while(n)/*now update indegrees of all neighbour vertices to vertex just enumerated with indegree 0*/
        {
            indegree[n->child] -= 1;
            LPT[n->child] = LPT[enumerate] + 1> LPT[n->child] ? LPT[enumerate] + 1 : LPT[n->child] ;/*Only update distance in LPT array if target node has distance < distance of enumerated node + 1*/
            if(indegree[n->child] == 0)
                pushToQ(&orderQ , n->child);
            n = n->next;
        }
    }
    printf("\nLPT array:\n");
    for (i = 0; i< Nnodes; i++)
        printf("%d ",LPT[i]);
}
int main()
{
    int i,j,k,type = 0/*0=undirected,1=directed,2=weighted undirected*/;
    maxWeight = 0;
    scanf("%d",&type);
    scanf("%d%d",&Nnodes,&Nedges);
    Level = (int*)malloc(Nnodes * sizeof(int));
    Parent = (int*)malloc(Nnodes * sizeof(int));
    Distance = (int*)malloc(Nnodes * sizeof(int));
    pre = (int*)malloc(Nnodes * sizeof(int));
    post = (int*)malloc(Nnodes * sizeof(int));
    AdjLst = (node**) malloc(Nnodes * sizeof(node*));
    if(type == 2)
    {
        WAdjLst = (Wnode**) malloc(Nnodes * sizeof(Wnode*));
        for(i = 0; i< Nnodes;i++)
        {
            WAdjLst[i]= NULL;
        }
    }
    visited = malloc(Nnodes * sizeof(int));
    visitedW = malloc(Nnodes * sizeof(int));
    component = malloc(Nnodes * sizeof(int));
    for (i = 0; i < Nnodes; i++)
    {
        visited[i] = -1;
        visitedW[i] = -1;
        post[i] = pre[i] = -1;
        component[i] = -1;
    }
    for(i = 0; i< Nnodes;i++)
    {
        AdjLst[i]= NULL;
    }
    for(i = 0;i< Nedges;i++)
    {
        int p,q,r;
        if(type == 0)
        {
            scanf("%d%d",&p,&q);
            addChild(p-1,q-1);
            addChild(q-1,p-1);
        }
        else if(type == 1)
        {
            scanf("%d%d",&p,&q);
            addChild(p-1,q-1);
        }
        else if(type == 2)
        {
            scanf("%d%d%d",&p,&q,&r);
            addChildW(p-1,q-1,r);
            //addChildW(q-1,p-1,r);
            maxWeight += r;
        }
    }
    maxWeight++;
    scanf("%d%d",&src,&dst);
    src--;dst--;
    //BFS(src);
    for(i = 0;i<Nnodes ; i++)
    {
        if(visited[i] == -1)
        {
            DFS(i);/*run DFS in a loop if any of the vertex remain unvisited, meaning there are more than one component*/
            printf("\nDFS:%d,comp:%d\n",i+1,comp);
            comp++;
        }
    }
    printf("Parent array:\n");
    for(i = 0; i< Nnodes;i++)
    {
        printf("%d ",Parent[i]);
    }
    printf("\nComponent array:\n");
    for(i = 0; i< Nnodes;i++)
    {
        printf("%d ",component[i]);
    }
    printf("\nPre,post array:\n");
    for(i = 0; i< Nnodes;i++)
    {
        printf("%d,%d ",pre[i],post[i]);
    }
    printf("\n");
    printf("\nTEs:\n");
    EDGES *n=HEAD_TE;
    while(n)
    {
        printf(" %d,%d |",n->s+1,n->t+1);
        n = n->next;
    }
    printf("\nSKIPPED Edges:\n");
    n=HEAD_SKIPPED;
    while(n)
    {
        printf(" %d,%d |",n->s+1,n->t+1);
        n = n->next;
    }
    printNTE(HEAD_TE, HEAD_SKIPPED);
    printf("\nNon Tree Edges:\n");
    n=HEAD_NTE;
    while(n)
    {
        if(pre[n->s] < pre[n->t] && post[n->s] > post[n->t])
        {
            printf(" FwdEdg %d,%d |\n",n->s+1,n->t+1);
        }
        if(pre[n->s] > pre[n->t] && post[n->s] < post[n->t])
        {
            printf(" BkwEdg %d,%d |\n",n->s+1,n->t+1);
        }
        if( (pre[n->s] < pre[n->t] && post[n->s] < post[n->t]) || ( pre[n->s] > pre[n->t] && post[n->s] > post[n->t]) )
        {
            printf(" CrsEdg %d,%d |\n",n->s+1,n->t+1);
        }
        n = n->next;
    }
    //TopologicalOrder();
    if(type == 2)
        dijkstraPath(src);
    if(type == 2)
       floyd_warshall_all_pairs_shortest_path(); 
    if(type == 2)
        for(i=0;i<Nnodes;i++)
        bellmanFord(i);
    return 0;
}
