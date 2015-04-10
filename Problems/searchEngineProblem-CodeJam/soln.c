#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<iostream>

typedef struct node
{
	char str[100];
}Node;
int main()
{
	int i,j,k,T,a;
	freopen("input.txt","r",stdin);
	scanf("%d",&T);
	char dump[5];
	for(i=0;i<T;i++)
	{
		int SE,SQ,leastFreq=9999,leastIndex=0;
		Node *arSE = NULL,*arSQ = NULL;
		int * arSEFreq = NULL;
				
		scanf("%d",&SE);
		arSE = (Node*)malloc(sizeof(Node) * SE);
		arSEFreq = (int *)malloc(sizeof(int) * SE);

		for(j=0;j<SE;j++)
		{
			arSEFreq[j] = 0;
			//arSE[j].str[0]='\0';
			//arSE[j] = (char *)malloc(sizeof(char) * 100);
			//scanf("%[\^n]",arSE[j]);
			//std::cin.getline(arSE[j].str,100);
			if(j == 0)
				gets(dump);
			gets(arSE[j].str);
			//printf("aa:%s\n",arSE[j].str);
			//fgets (arSE[j], 100, stdin);
		}
		
		scanf("%d",&SQ);
		if(SQ == 0)
		{
			printf("#%d %d\n",i+1,0);
			continue;
		}
		arSQ = (Node*)malloc(sizeof(Node) * SQ);
		for(j=0;j<SQ;j++)
		{
			//arSQ[j] = (char *)malloc(sizeof(char) * 100);
			//scanf("%[\^n]",arSQ[j]);
			if(j == 0)
				gets(dump);
			gets(arSQ[j].str);
			//printf("%s\n",arSQ[j].str);
			//fgets (arSQ[j], 100, stdin);
		}

		for(j=0;j<SE;j++)
		{
			for(k=0;k<SQ;k++)
			{
				//printf("%s \n %s ",ar);
				if(strcmp(arSE[j].str,arSQ[k].str) == 0)
					arSEFreq[j]++;
			}
		}
		for(j=0;j<SE;j++)
		{
			if(arSEFreq[j] <= leastFreq)
			{
				leastFreq = arSEFreq[j];
				leastIndex = j;
			}
		}
		printf("#%d %d\n",i+1,leastFreq);
		
	}
	//scanf("%d",&a);
	return 0;
}
