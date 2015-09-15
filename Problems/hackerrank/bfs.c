#include<stdio.h>
#include<stdlib.h>

typedef struct _node
{
    int child;
    struct _node* next;
}Node;
typedef struct _Queue
{
    int vertex;
    struct _Queue * last;
    struct _Queue* next;
}Queue;

Queue * Q = NULL;
Node ** AdjList = NULL;
int *GLevel = NULL;
int Nnodes;
void add2Q(int v)
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->vertex = v;
    q->next = NULL;
    q->last = q;
    if (Q == NULL)
    {
        Q = q;
        return;
    }
    Q->last->next = q;
    Q->last = q;
}

int dequeue()
{
    if (Q == NULL)
        return -1;
    int v = Q->vertex;
    Queue * q = Q;
    Q = Q->next;
    if(Q)
        Q->last = q->last;
    free(q);
    return v;
}

int isQEmpty()
{
    if(Q == NULL)
        return 1;
    else 
        return 0;
}
void addEdge(int prn, int child)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->child = child;
    n->next = NULL;
    if(AdjList[prn] == NULL) 
    {
        AdjList[prn]= n;
    }
    else
    {
        Node *t = AdjList[prn];
        while(t->next)
        {
            // this condition checks if prn--child edge is already added, so does not add a redundant node!
            //this was causing test case #5 to timeout!
            if(t->next->child == child)
                return;
            t = t->next;
        }
        t->next = n;
    }
}
void printQ()
{
    Queue * q = Q;
    while(q)
    {
        printf("%d ",q->vertex);
        q=q->next;
    }
    printf("\n");
}
void BFS(int start)
{
    int i;
    GLevel[start] = 0;
    add2Q(start);
    while(!isQEmpty())
    {
        int v = dequeue();
        Node * n = AdjList[v];
        while(n)
        {
            if(GLevel[n->child] == -1)
            {
                GLevel[n->child] = (GLevel[v] + 1) ;
                add2Q(n->child);
            }   
            n = n->next;
        }
    }
    for(i=0;i<Nnodes;i++)
    {
        if(GLevel[i] > 0)
            printf("%d ",GLevel[i] * 6);
        else if(GLevel[i] != 0)
            printf("%d ",GLevel[i] );
    }
    printf("\n");
}
int main()
{
    int i,T,Edges;
    scanf("%d",&T);
    for(i=0;i<T;i++)
    {
        int j =0,prn,chd,source;
        //int  Level[1000];
        scanf("%d %d",&Nnodes,&Edges);
        int *Level = malloc(sizeof(int) * Nnodes);
        GLevel = Level;
        for(j=0;j<Nnodes;j++)
        {
            Level[j]= -1;
        }
        AdjList = (Node **) malloc(Nnodes * sizeof(Node *));
        for(j=0;j<Nnodes;j++)
        {
            AdjList[j] = NULL;
        }
        for(j=0;j<Edges;j++)
        {
            scanf("%d %d",&prn,&chd);
            addEdge(prn-1,chd-1);
            addEdge(chd-1,prn-1);
        }
        scanf("%d",&source);
        BFS(source-1);
    }

}
