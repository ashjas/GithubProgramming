#include<stdio.h>
#include<stdlib.h>
int N=0;
int *U = NULL;
int Max(int a, int b)
{
    return a>b?a:b;
}
int Best(int * U)
{
    int i,j,max=-1,divisor=-1;
    int * LDS = malloc(sizeof(int) * N);
    for(i=0;i<N;i++)
        LDS[i] = 0;
    LDS[0]=1;
    for(i=0;i<N;i++)
    {
        max = 1;
        divisor = U[i];
        for(j=0;j<i ;j++)
        {
                if(U[i] % U[j] == 0)
                {
                    max = Max(max,LDS[j]+1);
                }
        }
        LDS[i]= max;
    }
    max =-1;
    for(i=0;i<N;i++)
        if(LDS[i]> max)
            max= LDS[i];
    return max;

}
int main()
{
    int i;
    scanf("%d",&N);
    U = malloc(sizeof(int) * N);
    for(i=0;i<N;i++)
        scanf("%d",&U[i]);
    printf("\n%d",Best(U));

}
