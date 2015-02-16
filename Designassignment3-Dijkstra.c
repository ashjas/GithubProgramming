#include<stdio.h>
#include<stdlib.h>
int Nnodes,Nedges,src,dst,*visitedW,*Distance,DSize;
int maxWeight,maxNode = 0,size = 0;
int * NodeToHeap,*HeapToNode;
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
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Max(int a, int b)
{
    return a < b ? b : a;
}

int Min(int a, int b)
{
    return a > b ? b : a;
}

void fixHeapUp(int* heap, int i)
{
    int p = (i - 1) / 2;
    if(i == 0)/*reached the top*/
        return;
    if(heap[p] > heap[i])
    {
        Swap(&heap[p], &heap[i]);
        Swap(&HeapToNode[p], &HeapToNode[i] );
        Swap(&NodeToHeap[p], &NodeToHeap[i] );
        fixHeapUp(heap, p);
    }
}

void fixHeapDown(int* heap, int i)
{
    int l = i*2 + 1;
    int r = i*2 + 2;
    int minchild = Min(heap[l],heap[r]);
    int minchildIdx = heap[l] < heap[r] ? l : r;
    if(r >= size)/*reached the top*/
        return;
    if(heap[i] > minchild)
    {
        Swap(&heap[i], &heap[minchildIdx]);
        Swap(&HeapToNode[i], &HeapToNode[minchildIdx] );
        Swap(&NodeToHeap[i], &NodeToHeap[minchildIdx] );
        fixHeapDown(heap, minchildIdx);
    }
}
int * makeMinArrayHeap(int size, int* arr)/*Need not use this here as we have the Distance heap already created, all being a const Maxweight value.*/
{
    int* heap,i;
    heap = malloc(sizeof(int) * size);
    heap[0] = arr[0];/*just start with first array as is*/
    for(i=1 ;i < size;i++)
    {
        heap[i] = arr[i];
        fixHeapUp(heap,i);
    }
    return heap;
}

int deleteMin(int * heap)
{
    int ret = HeapToNode[0];
    heap[0]=heap[size - 1];
    HeapToNode[0] = HeapToNode[size -1];
    NodeToHeap[0] = NodeToHeap[size -1];
    size--;
    fixHeapDown(heap, 0);
    return ret;
}
void print(int *heap)
{
    int i;
    printf("\nheapified array:\n");
    for(i=0;i<size;i++)
    {
        printf("%d ",heap[i]);
    }
}
void updateHeapNode(int i, int* heap, int val)
{
    int p = (i -1) /2;
    heap[i] = val;
    if(heap[i] < heap[p] )
        fixHeapUp(heap,i);
    else
        fixHeapDown(heap,i);
}
void dijkstraPath(int start)
{
    int i,j;
    //Distance[start] = 0;
    updateHeapNode(start, Distance,0);
    for(i = 0; i<maxNode; i++)
    {
        int u;
        /*int minDis=maxWeight;
        for (j=0;j<maxNode;j++)
        {
            if(visitedW[j] == -1)
                if (Distance[j]<minDis)
                {
                    minDis = Distance[j];
                    u = j;
                }
        }*/
        u = deleteMin(Distance);/*will give heap to node*/
        visitedW[u] = 1;
        Wnode * n = WAdjLst[u];
        while(n)
        {
            int nodechild,nodemin;
            nodechild = NodeToHeap[n->child]; nodemin = NodeToHeap[u];
            if(visitedW[n->child] == -1 && Distance[nodechild] > (Distance[nodemin] + n->weight))
                //Distance[nodechild] =  Distance[nodemin] + n->weight;
                updateHeapNode(nodechild,Distance,(Distance[nodemin] + n->weight));
            n = n->next;
        }
    }
    dst = NodeToHeap[dst];
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
    NodeToHeap = (int*)malloc(maxNode * sizeof(int));
    HeapToNode = (int*)malloc(maxNode * sizeof(int));
    for (i = 0; i < maxNode; i++)
    {
        Distance[i] = maxWeight;
        visitedW[i] = -1;
        NodeToHeap[i] = i;
        HeapToNode[i] = i;
    }
    src--;dst--;
    dijkstraPath(src);
    //int dist[12]={45,23,78,22,1,3,12,19,17,4,5,92};
    //int dist[12]={45,45,45,45,45,45,45,45,45,45,5,45};
    //printf("\norigarray:");
    //for (i =0;i<12;i++)
    //    printf("%d ",dist[i]);
    //heapifyDown(0,dist);
    //updateDistance(6,4,dist);
    //printf("\nheapified array:");
    //for (i =0;i<12;i++)
    //    printf("%d ",dist[i]);
    return 0;
}
