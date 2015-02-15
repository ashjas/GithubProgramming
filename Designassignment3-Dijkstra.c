#include<stdio.h>
#include<stdlib.h>
int Nnodes,Nedges,src,dst,*visitedW,*Distance,DSize;
int maxWeight,maxNode = 0;
typedef struct Wnode
{
    int child;
    int weight;
    struct Wnode * next;
}Wnode;
Wnode** WAdjLst;
typedef struct heap
{
    int dist;
    struct heap * left;
    struct heap * right;
}heap;
heap * Heap = NULL;
void Swap(int *a, int *b)
{
    printf("\norig:%d,%d:",*a,*b);
    int temp = *a;
    *a = *b;
    *b = temp;
    printf("\nswaped:%d,%d:",*a,*b);
}
int Max(int a, int b)
{
    return a < b ? b : a;
}
int Min(int a, int b)
{
    return a > b ? b : a;
}
void heapifyDown(int s,int* Distance)
{
    int l = s*2 +1;
    int r = s*2 +2;
    if(l >= 12 || r >= 12)
        return;
    int min = Min(Distance[l],Distance[r]);
    if(Distance[s] < min)
        return;
    if(Distance[r] < Distance[l])
    {
        Swap(&Distance[s],&Distance[r]);
        heapifyDown(r,Distance);
    }
    else
    {
        Swap(&Distance[s],&Distance[l]);
        heapifyDown(l,Distance);
    }
}
void heapifyUp(int s)
{
    int p = (s - 1) / 2;
    if(Distance[s] > Distance[p])
        return;
    Swap(&Distance[s],&Distance[p]);
    heapifyUp(p);
}
int deleteMin(int *Distance)
{
    int min = Distance[0];
    Distance[0] = Distance[DSize--];
    heapifyDown(0,Distance);
}
void updateDistance(int s, int D, int* Distance)
{
    int l = s*2 +1;
    int r = s*2 +2;
    int min = Min(Distance[l],Distance[r]);
    Distance[s]=D;
    if(Distance[s] < min)
        heapifyUp(s);
    else
        heapifyDown(s,Distance);
}
int* makeHeap(int size, int* arr)
{
    int i;
    int * heap = malloc(sizeof(int) * size);
    for( i=0;i<size;i++)
        heap[i]=-1;
    
}
void dijkstraPath(int start)
{
    int i,j;
    Distance[start] = 0;
    for(i = 0; i<maxNode; i++)
    {
        int u;
        int minDis=maxWeight;
        for (j=0;j<maxNode;j++)
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
    if(Distance[dst] == maxWeight)
        printf("%s\n","NO");
    else
        printf("%s\n%d\n","YES",Distance[dst]);


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
int main()
{
    int i;
    maxWeight = 0;
    Nnodes = 2000;
    scanf("%d%d%d",&Nedges,&src,&dst);
    WAdjLst = (Wnode**) malloc(Nnodes * sizeof(Wnode*));
    for(i = 0; i< Nnodes;i++)
    {
        WAdjLst[i]= NULL;
    }
    for(i = 0;i< Nedges;i++)
    {
        int p,q,r;
        scanf("%d%d%d",&p,&r,&q);
        addChildW(p-1,q-1,r);
        addChildW(q-1,p-1,r);
        maxWeight += r;
        if(p > maxNode || q > maxNode)
            maxNode = p > q ? p : q;
    }
    maxWeight++;
    DSize = maxNode;
    Distance = (int*)malloc(maxNode * sizeof(int));
    visitedW = (int*)malloc(maxNode * sizeof(int));
    for (i = 0; i < maxNode; i++)
    {
        Distance[i] = maxWeight;
        visitedW[i] = -1;
    }
    src--;dst--;
    dijkstraPath(src);
    //int dist[12]={45,23,78,22,1,3,12,19,17,4,5,92};
    int dist[12]={45,45,45,45,45,45,45,45,45,45,5,45};
    printf("\norigarray:");
    for (i =0;i<12;i++)
        printf("%d ",dist[i]);
    //heapifyDown(0,dist);
    updateDistance(6,4,dist);
    printf("\nheapified array:");
    for (i =0;i<12;i++)
        printf("%d ",dist[i]);
    return 0;
}
