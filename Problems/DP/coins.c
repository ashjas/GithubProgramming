#include<stdio.h>
#include<limits.h>
//int S[12];
unsigned int S[12];
int V[3]={2,3,7};
int main()
{
    int i,j,k;
    for(i=0;i<12;i++)
    {
        //S[i]=999;
        S[i]=INT_MAX;
    }
    S[0]=0;
    
    for(i=0;i<3;i++)
    {
        for(j=0;j<12;j++)
        {
            if( S[j] + 1 < S[ j + V[i] ] )/*Earlier i was using assigning to S[j] sum of S[j + V[i]] which is wrong, as S[j] should always have count of coins, and not value of coin.*/
                S[ j + V[i] ] = S[j] +1;
        }
    }
    for(i=0;i<12;i++)
    {
        printf("%d:%d\n",i,S[i]);
    }
}
