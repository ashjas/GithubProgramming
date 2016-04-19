#include<stdio.h>
#include<stdlib.h>

typedef struct data
{
    int mat[64][64];
    int dat[64];
}Data;
int Pow(int p)
{
    int i=0,val=0;
    for(;i<p;i++)
        val*=2;
}
int binary(Data d,int indx, int column)
{
    int i,val=0,p=0;
    int * cand = d.mat[indx];
    for(i=column;i>=0;i--,p++)
    {
        val = val + cand[i] * Pow(p);
    }
    return val;
}
int Freq(Data d, int candidates)
{
    int i,j,freq=0;
    for(i=0;i<candidates;i++)
    {
        int c=1;
        if(d.dat[i] == -1)
            continue;
        for(j= i+1; j< candidates;j++)
        {
            if(d.dat[i] == d.dat[j])
            {
                c++;
                d.dat[j] = -1;
            }
        }
        if(c > freq)
            freq = c;
    }
    return freq;
}
int main()
{
    int T,rows,columns,k,i,j,l;
    scanf("%d",&T);
    for(i=0;i<T;i++)
    {
        Data data;
        int candidates=0;
        scanf("%d %d %d",&rows,&columns,&k);
        for(j=0;j<rows;j++)
        {
            for(l=0;l<columns;l++)
            {
                scanf("%d",&data.mat[j][l]);
            }
        }
        for(j=0;j<rows;j++)
        {
            int i = 0;
            int zeros=0;
            for(l=0;l<columns;l++)
            {
                if(data.mat[j][l] == 0)
                    zeros++;
            }
            if((k - zeros) > 0 && (k - zeros) % 2 == 0)
            {
                data.dat[i++] = j;
                candidates ++;
            }
        }
        printf("candidates :%d\n data:\n",candidates);

        for(j=0;j<candidates;j++)
        {
            data.dat[j]= binary(data,j,columns);
            printf("%d ",data.dat[j]);
        }
        printf("\nans:%d\n",Freq(data,candidates)) ;
    }
}
