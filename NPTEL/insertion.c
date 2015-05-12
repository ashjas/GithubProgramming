#include<stdio.h>
#include<stdlib.h>
#define MAX 10
void swap(int arr[] ,int first,int second)
{
    int temp=arr[first];
    arr[first]=arr[second];
    arr[second]=temp;
}
void insertion_sort(int arr[])
{
    int i,j;
    for(i=1;i<MAX;i++)
    {
        int nextpos=i;
        while(nextpos > 0 && arr[nextpos] < arr[nextpos - 1])
        {
            swap(arr,nextpos,nextpos-1);
            nextpos--;
        }
    }
}
int main()
{
    int ar[MAX],i;
    printf("\nEnter 10 integers:\n");
    for (i=0;i<MAX;i++)
    {
        scanf("%d",&ar[i]);
    }
    printf("\n10 integers before sort:\n");
    for (i=0;i<MAX;i++)
    {
        printf("%d ",ar[i]);
    }
    insertion_sort(ar);
    printf("\n10 integers after sort:\n");
    for (i=0;i<MAX;i++)
    {
        printf("%d ",ar[i]);
    }
}
