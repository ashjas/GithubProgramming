#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<iostream>

typedef struct node
{
    char str[100];
}Node;
int updateArray(Node * arSE,int SE,Node * arSQ,int SQ,int * arFreq,int start)
{
    int i,j,k=-1;
    for(i=0;i<SE;i++)
        arFreq[i] = -1;
    for(i=0;i<SE;i++)
    {
        for(j=start;j<SQ;j++)
        {
            if(strcmp(arSE[i].str,arSQ[j].str) == 0)
            {
                arFreq[i] = j;
                break;
            }
        }
    }
    for (i=0;i<SE;i++)
    {
        if(arFreq[i] == -1)
            return -1;
        if(arFreq[i] > k)
            k = arFreq[i];
    }
    return k;
}
int main()
{
    int i,j,k,T,a;
    freopen("A-small-practice.in","r",stdin);
    scanf("%d",&T);
    char dump[5];
    for(i=0;i<T;i++)
    {
        int SE,SQ,leastFreq=9999,leastIndex=0;
        int max = 0,count=0,once =0,flag = 0;
        char maxStr[100];
        Node *arSE = NULL,*arSQ = NULL;
        int * arSEFreq = NULL;

        scanf("%d",&SE);
        arSE = (Node*)malloc(sizeof(Node) * SE);
        arSEFreq = (int *)malloc(sizeof(int) * SE);

        for(j=0;j<SE;j++)
        {
            arSEFreq[j] = -1;

            if(j == 0)
                gets(dump);
            gets(arSE[j].str);

        }

        scanf("%d",&SQ);
        //if(SQ == 0)
        //{
          //  printf("#%d %d\n",i+1,0);
            //continue;
        //}
        arSQ = (Node*)malloc(sizeof(Node) * SQ);
        for(j=0;j<SQ;j++)
        {

            if(j == 0)
                gets(dump);
            gets(arSQ[j].str);

        }
        max = updateArray(arSE,SE,arSQ,SQ,arSEFreq,0);

        if(max >=0)
        {
            strcpy(maxStr,arSQ[max].str);
            for(j=0;j<SQ;j++)
            {
                if(strcmp(maxStr,arSQ[j].str) != 0)
                {
                //     once =1;
                    continue;
                }
                //else if(once == 1)
                else
                {
                    max = updateArray(arSE,SE,arSQ,SQ,arSEFreq,j);
                    count++;
                    if(max == -1)
                        break;

                    strcpy(maxStr,arSQ[max].str);
                }
            }
        }
        printf("Case #%d %d\n",i+1,count);
    }
    return 0;
}
