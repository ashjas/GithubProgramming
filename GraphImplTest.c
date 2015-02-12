#include<stdio.h>
#include<stdlib.h>
/*
 Can classify edges using pre and post numbers
 Tree/Forward edge (u,v) : Interval [pre(u),post(u)] contains [(pre(v),post(v)]
 Backward edge (u,v): Interval [pre(v),post(v)] contains [(pre(u),post(u)]
 Cross edge (u,v): Intervals [(pre(u),post(u)] and [(pre(v),post(v)] disjoint
 */
int * Level,*Parent,Nnodes,Nedges,src,dst,*visited,*component;
int * pre,*post,count = 0,comp = 1;
typedef struct node
{
    int child;
    struct node * next;
}node;
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
            if((itr->s == s && itr->t == t ) || (itr->s == t && itr->t == s))
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
void TopologicalOrder()
{
    int i,j,k;
    Queue * orderQ = NULL;
    Queue * finalQ = NULL;
    int * indegree = (int*)malloc(Nnodes * sizeof(int));
    for (i = 0; i< Nnodes; i++)
    {
        indegree[i] = 0;/*initialize all vertex indegrees to 0*/
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
            if(indegree[n->child] == 0)
                pushToQ(&orderQ , n->child);
            n = n->next;
        }
    }
}
int main()
{
    int i,j,k,directed = 0;
    scanf("%d",&directed);
    scanf("%d%d",&Nnodes,&Nedges);
    Level = (int*)malloc(Nnodes * sizeof(int));
    Parent = (int*)malloc(Nnodes * sizeof(int));
    pre = (int*)malloc(Nnodes * sizeof(int));
    post = (int*)malloc(Nnodes * sizeof(int));
    AdjLst = (node**) malloc(Nnodes * sizeof(node*));
    visited = malloc(Nnodes * sizeof(int));
    component = malloc(Nnodes * sizeof(int));
    for (i = 0; i < Nnodes; i++)
    {
        visited[i] = -1;
        post[i] = pre[i] = -1;
        component[i] = -1;
    }
    for(i = 0; i< Nnodes;i++)
    {
        AdjLst[i]= NULL;
    }
    for(i = 0;i< Nedges;i++)
    {
        int p,q;
        scanf("%d%d",&p,&q);
        addChild(p-1,q-1);
        if(!directed)
            addChild(q-1,p-1);
    }
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
    TopologicalOrder();
    return 0;
}
