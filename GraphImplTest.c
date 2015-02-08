#include<stdio.h>
#include<stdlib.h>
int * Level,*Parent,Nnodes,Nedges,src,dst,*visited;
int * pre,*post,count = 0;
typedef struct node
{
    int child;
    struct node * next;
}node;
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
        printf("\neeeeeeeee\n");
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
void DFS(int start)
{
    int i;
    visited[start] = 1;
    for (i = 0;i<Nnodes; i++)
        printf("%d ",visited[i]);
    printf("\n");
    node *t = AdjLst[start];
    pre[start] = count;
    count++;
    while(t)
    {
        if(visited[t->child] != 1)
        {
            Parent[t->child] = start;
            DFS(t->child);
        }
        t = t->next;
    }
    post[start] = count; 
    count++;
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
    pre = (int*)malloc(Nnodes * sizeof(int));
    post = (int*)malloc(Nnodes * sizeof(int));
    AdjLst = (node**) malloc(Nnodes * sizeof(node*));
    visited = malloc(Nnodes * sizeof(int));
    for (i = 0; i < Nnodes; i++)
    {
        visited[i] = -1;
        post[i] = pre[i] = -1;
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
        addChild(q-1,p-1);
    }
    scanf("%d%d",&src,&dst);
    src--;dst--;
    //BFS(src);
    DFS(src);
    printf("Parent array:\n");
    for(i = 0; i< Nnodes;i++)
    {
        printf("%d ",Parent[i]);
    }
    printf("\nPre,post array:\n");
    for(i = 0; i< Nnodes;i++)
    {
        printf("%d,%d ",pre[i],post[i]);
    }
    printf("\n");
    return 0;
}
