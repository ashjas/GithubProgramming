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
int main()
{
    int i,T,Nnodes,Edges;
    scanf("%d",&T);
    for(i=0;i<T;i++)
    {
        int j =0,prn,chd;
        scanf("%d %d",&Nnodes,&Edges);
        AdjList = (Node **) malloc(Nnodes * sizeof(Node *));
        for(j=0;j<Nnodes;j++)
        {
            AdjList[j] = NULL;
        }
        for(j=0;j<Edges;j++)
        {
            scanf("%d %d",&prn,&chd);
            addEdge(prn-1,chd-1);
            addEdge(chd);
        }
    }

    for(i =0;i<20;i++)
    {
        add2Q(i);
    }
    printQ();
    printf("dequeing\n");
    for( i =0;i<20;i++)
    {
        printf("%d ",dequeue());
    }
}
