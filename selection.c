#include<stdio.h>
#include<stdlib.h>
#define MAX 10
void swap(int arr[] ,int first,int second)
{
    int temp=arr[first];
    arr[first]=arr[second];
    arr[second]=temp;
}
void selection_sort(int arr[])
{
    int i,j;
    for(i=0;i<MAX;i++)
    {
        int min=arr[i];
        int minIdx=-1;
        for(j=i+1;j<MAX;j++)
        {
            if(arr[j] < min)
            {
                minIdx=j;
                min = arr[j];
            }
        }
        if(minIdx > 0)
            swap(arr,i,minIdx);
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
    selection_sort(ar);
    printf("\n10 integers after sort:\n");
    for (i=0;i<MAX;i++)
    {
        printf("%d ",ar[i]);
    }
}
