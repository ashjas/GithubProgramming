//#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main()
{
    int Nnodes,Nedges,src,dst;
    int i,j,k;
    scanf("%d%d",&Nnodes,&Nedges);
    int **AdjMx=(int **)malloc(Nnodes * sizeof(int*));
    for(i = 0; i< Nnodes;i++)
    {
        AdjMx[i] = (int *)malloc(Nnodes * sizeof(int));
        for(j=0;j<Nnodes;j++)
            AdjMx[i][j]=0;
    }
    //for(i = 0; i< Nnodes;i++)
      //  for(j=0;j<Nnodes;j++)
        //    AdjMx[i][j]=0;


    for(i = 0;i< Nedges;i++)
    {
        int p,q;
        scanf("%d%d",&p,&q);
        AdjMx[q-1][p-1] = AdjMx[p-1][q-1] = 1;
    }
    scanf("%d%d",&src,&dst);
    /*printf("\nAdjecency Mtrix:\n");
    for(i=0;i<Nnodes;i++)
    {
        for(j=0;j<Nnodes;j++)
            printf("%d:",AdjMx[i][j]);
        printf("\n");
    }
    printf("\nsrc:%d,dst:%d",src,dst);*/

    return 0;

}
