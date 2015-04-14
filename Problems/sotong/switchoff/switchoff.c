#include<stdio.h>
#include<stdlib.h>

int main()
{
    int i,j,k,a,count=0,T;
    freopen("in", "r", stdin);
    scanf("%d",&T);
    for(k=0;k<T;k++)
    {
        int * ar = NULL;
        int S,N;
        int switchLeft,idxv=0,I=0,min=99999;
        int totalWatt=0,steps_moved=0,freqL=0,freqR=0;
        scanf("%d %d",&N,&S);
        ar = (int*)malloc(sizeof(int) * N);
        switchLeft=N;
        for(i=0;i<N;i++)
        {
            scanf("%d",&ar[i]);
        }
        for(i=0;i<N;i++)
        {
            idxv=0;I=0;min=99999;
            for(j=0;j<N;j++)
            {
                if(ar[j] != -1 && S != ar[j] && abs(S-ar[j]) < min)
                {
                    min = abs(S-ar[j]);
                    idxv=ar[j];
                    I=j;
                }
            }
            totalWatt+= switchLeft*min;
            switchLeft--;
            S = idxv;
            ar[I]=-1;
        }
        printf("%d\n",totalWatt);
    }


    return 0;
}
