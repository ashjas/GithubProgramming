#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main()
{
    int Nnodes,Nedges,src,dst;
    int i,j,k;
    scanf("%d%d",&Nnodes,&Nedges);
    int **AdjMx=(int **)malloc(Nnodes * sizeof(int));
    for(i = 0; i< Nnodes;i++)
    {
        AdjMx[i] = (int *)malloc(Nnodes * sizeof(int));
        //for(j=0;j<Nnodes;j++)
          //  AdjMx[i][j]=0;
    }
    //for(i = 0; i< Nnodes;i++)
      //  for(j=0;j<Nnodes;j++)
        //    AdjMx[i][j]=0;


    for(i = 0;i< Nedges;i++)
    {
        int i,j;
        scanf("%d%d",&i,&j);
        AdjMx[i][j] = 1;
    }
    scanf("%d%d",&src,&dst);
    printf("\nAdjecency Mtrix:\n");
    for(i=0;i<Nnodes;i++)
    {
        for(j=0;j<Nnodes;j++)
            //printf("j:%d val:%d :",j,AdjMx[i][j]);
            printf("%d:",AdjMx[i][j]);
    printf("\n");
    }
    printf("\nsrc:%d,dst:%d",src,dst);
    return 0;

}
