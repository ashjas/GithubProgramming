#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int check(int **ar ,int i,int j,int N)
{
    int k,l,m,flag =1;
    for(k=0;k<N;k++)
        if(ar[k][j] == 1 )
        {
            flag = 0;
            break;
        }
    if(flag)
    {
        int r=i,c=j;
        while(r>=0 && c>=0)
        {
            if(ar[r][c] == 1)
            {
                flag =0;
                break;
            }
            r--;c--;
        }
    }
    if(flag)
    {
        int r=i,c=j;
        while(r<N && c<N)
        {
            if(ar[r][c] == 1)
            {
                flag =0;
                break;
            }
            r++;c++;
        }
    }
    if(flag)
    {
        int r=i,c=j;
        while(r<N && c>=0)
        {
            if(ar[r][c] == 1)
            {
                flag =0;
                break;
            }
            r++;c--;
        }
    }
    if(flag)
    {
        int r=i,c=j;
        while(r>=0 && c<N)
        {
            if(ar[r][c] == 1)
            {
                flag =0;
                break;
            }
            r--;c++;
        }
    }
    return flag;
}
long long count=0;
int nQueen(int ** ar,int i,int N)
{
    count++;
    int j;
    if(i == N)
        return 1;
    for(j=0;j<N;j++)
    {
        if(check(ar,i,j,N))
        {
            int flag =0;
            ar[i][j] = 1;
            flag = nQueen(ar,i+1,N);
            if(flag)
                return 1;
            ar[i][j]=0;
        }
    }
    return 0;
}
void print(int ** ar,int N)
{
    int i,j;
    printf("\n");
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            printf("%d ",ar[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int N,i,j,k,a;
    int ** ar =NULL;
    scanf("%d",&N);
    ar = (int **)malloc(sizeof(int*) * N);
    for(i=0;i<N;i++)
    {
        ar[i] = (int*)malloc(sizeof(int) * N);
    }
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            ar[i][j]=0;
    //print(ar,N);
    if(nQueen(ar,0,N) == 1)
    {
        print(ar,N);
        printf("\nRecursive calls :%lld\n",count);
    }
    else
        printf("\nNo possible solution.");
    return 0;
}
