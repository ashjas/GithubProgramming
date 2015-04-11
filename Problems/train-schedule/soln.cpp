#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
#include<vector>
#include<set>

int nA, nB, *A=NULL, *B=NULL, N, Acnt = 0, Bcnt = 0;
vector <pair<int, int> > * vAG;
vector <pair<int, int> > * vBG;
void sort(int * ar, int size)
{
	int i, j;
	for (i = 0; i < size; i+=2)
	{
		for (j = i + 2; j < size; j += 2)
		{
			if (ar[j] < ar[i])
			{
				int temp = ar[i];
				ar[i] = ar[j];
				ar[j] = temp;
				temp = ar[i + 1];
				ar[i + 1] = ar[j + 1];
				ar[j + 1] = temp;
			}
		}
	}
}
int checkLessB(int);
int checkLessA(int i)
{
	
	int j = 0;
	//while ((*vAG).begin() + j != (*vBG).end())
	while (j < (*vAG).size() && (*vAG).size() > 0 && i < (*vBG).size() && (*vBG).size() > 0)
	{
	
		if ((*vBG)[i].second <= (*vAG)[j].first)
		{
			checkLessB(j);
			(*vAG).erase((*vAG).begin() + j);
			
			return 1;
		}
		j++;
	}
	return 0;
}
int checkLessB(int i)
{
	
	int j = 0;
	//while ((*vBG).begin() + j != (*vBG).end())
	while (j < (*vBG).size() && (*vBG).size() > 0 && i < (*vAG).size() && (*vAG).size() > 0)
	{
		if ((*vAG)[i].second <= (*vBG)[j].first)
		{
			checkLessA(j);
			(*vBG).erase((*vBG).begin() + j);
			
			return 1;
		}
		j++;
	}
	return 0;
}

int max(int a, int b)
{
	return a>b ? a : b;
}
int main()
{
	int i, j, k, T, a,p;
	FILE * f;
	f= freopen("B-large-practice.in","r",stdin);
//	f = freopen("C:\\out","w",stdout);
	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		Acnt = Bcnt = 0;
		scanf("%d %d %d", &T,&nA,&nB);
		if (nA >0)
		A = (int*) malloc(sizeof(int) * nA * 2);
		if (nB>0)
		B = (int*) malloc(sizeof(int) * nB * 2);
		char buf[50];
		char one[5];
		char two[5];
		for (j = 0; j < nA*2; j++)
		{
			if (j==0)
				gets(buf);
			gets(buf);
			int l=0;
			for (k = 0; k < strlen(buf); k++)
			{
				if (k<5)
				{ 
					if (buf[k] != ':')
						one[l++] = buf[k];
					else
						continue;
				}
				if (k == 5)
				{
					one[l] = '\0';
					l = 0;
				}
				else if (k > 5)
				{
					if (buf[k] != ':')
						two[l++] = buf[k];
					else
						continue;
				}
				if (k == 10)
					two[l] = '\0';
			}
			A[j++] = atoi(one);
			A[j] = atoi(two);
			A[j] += T;
		}
		for (j = 0; j < nB*2; j++)
		{
			gets(buf);
			int l = 0;
			for (k = 0; k < strlen(buf); k++)
			{
				if (k<5)
				{
					if (buf[k] != ':')
						one[l++] = buf[k];
					else
						continue;
				}
				if (k == 5)
				{
					one[l] = '\0';
					l = 0;
				}
				else if (k > 5)
				{
					if (buf[k] != ':')
						two[l++] = buf[k];
					else
						continue;
				}
				if (k == 10)
					two[l] = '\0';
			}
			B[j++] = atoi(one);
			B[j] = atoi(two);
			B[j] += T;
		}
		sort(A, nA*2);
		sort(B, nB*2);
		vector <pair<int, int> > vA(nA);
		vector <pair<int, int> > vB(nB);
		vAG = &vA;
		vBG = &vB;
		for (j = 0,k=0; j < nA * 2; j+=2,k++)
		{
			vA[k].first = A[j];
			vA[k].second = A[j + 1];
		}
		for (j = 0,k=0; j < nB * 2; j += 2,k++)
		{
			vB[k].first = B[j];
			vB[k].second = B[j + 1];
		}
		/*printf("\n%d----------\n", i + 1);
		for (j = 0,k=0; j < max(nA,nB); j++,k++)
		{
			if (j < nA)
			{
				printf("%4d,", vA[j].first);
				printf("%4d,", vA[j].second);
			}
			if (k < nB)
			{
				printf("    %4d,", vB[k].first);
				printf("%4d,", vB[k].second);
			}
			printf("\n");
		}
		printf("\n");*/
		/*for (j = 0; j < nB; j++)
		{
			printf("%d,", vB[j].first);
			printf("%d,", vB[j].second);
			printf("\n");
		}*/
		/*Inputs done .now find the answer.*/
		
			 p = 0; k = 0; j = 0;
		 while (vA.size() > 0 || vB.size() > 0)
		 {
			 p++;
			 if (vA.size() > 0 && vB.size() > 0 && vA[0].first <= vB[0].first)
			 {
				 Acnt++;
				 checkLessB(0);
				 vA.erase(vA.begin());
			 }
			 else if (vA.size() >0 && vB.size() > 0 && vA[0].first >= vB[0].first)
			 {
				 Bcnt++;
				 checkLessA(0);
				 vB.erase(vB.begin());
			 }
			 else if (vA.size() > 0 && vB.size() == 0)
			 {
				 Acnt++;
				 vA.erase(vA.begin());
			 }
			 else if (vB.size() > 0 && vA.size() == 0)
			 {
				 Bcnt++;
				 vB.erase(vB.begin());
			 }
		 }
		printf("Case #%d: %d %d\n", i+1, Acnt, Bcnt);
	}
	
	
	scanf("%d",&a);
	return 0;
}
