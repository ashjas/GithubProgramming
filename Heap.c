#include<stdio.h>
#include<stdlib.h>
int size;
int * NodeToHeap,*HeapToNode;
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
        fixHeapDown(heap, minchildIdx);
    }
}
int * makeMinArrayHeap(int size, int* arr)
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
    int ret = heap[0];
    heap[0]=heap[size - 1];
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

int main()
{
    int i,*arr,*heap,size1,ii,val;
    scanf("%d",&size);
    arr = malloc(sizeof(int) * size);
    NodeToHeap= malloc(sizeof(int) * size);
    HeapToNode= malloc(sizeof(int) * size);
    for(i=0;i<size;i++)
    {
        scanf("%d",&arr[i]);
    }

    heap=makeMinArrayHeap(size, arr);
    printf("\norig array:\n");
    for(i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
    }
        print(heap);
         size1= size;
    printf("\nenter i to update and its val:");
    scanf("%d%d",&ii,&val);
    //for(i=0;i<size1;i++)
    {
        //printf("\nDeleted:%d",deleteMin(heap));
        updateHeapNode(ii,heap,val);
       // updateHeapNode(7,heap,3489);
        print(heap);
    }

}
