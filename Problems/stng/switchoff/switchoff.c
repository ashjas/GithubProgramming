#include<stdio.h>
#include<stdlib.h>
int checkEqMinOptimumPath(int a, int b, int curS, int * ar, int N)
{
	int i, Min = 9999;
	for (i = 0; i<N; i++)
	{
		if (ar[i] != -1 && curS != ar[i] && a != ar[i] && b != ar[i] && abs(a - ar[i]) < Min)
		{
			Min = abs(a - ar[i]);
		}
	}
	for (i = 0; i<N; i++)
	{
		if (ar[i] != -1 && curS != ar[i] && a != ar[i] && b != ar[i] && abs(b - ar[i]) < Min)
		{
			return b;
		}
	}
	return a;
}
int main()
{
	int i, j, k, a, count = 0, T;
	freopen("in", "r", stdin);
	scanf("%d", &T);
	for (k = 0; k<T; k++)
	{
		int * ar = NULL;
		int S, N;
		int switchLeft, idxv = 0, I = 0, min = 99999;
		int totalWatt = 0, steps_moved = 0, freqL = 0, freqR = 0;
		scanf("%d %d", &N, &S);
		ar = (int*)malloc(sizeof(int) * N);
		switchLeft = N;
		for (i = 0; i<N; i++)
		{
			scanf("%d", &ar[i]);
		}
		for (i = 0; i<N; i++)
		{
			idxv = 0; I = 0; min = 99999;
			for (j = 0; j<N; j++)
			{
				if (ar[j] != -1 && S != ar[j] && abs(S - ar[j]) < min)
				{
					min = abs(S - ar[j]);
					idxv = ar[j];
					I = j;
				}
				else if (ar[j] != -1 && S != ar[j] && abs(S - ar[j]) == min)
				{
					int a = checkEqMinOptimumPath(ar[I], ar[j], S, ar, N);
					if (a == ar[j])
					{
						idxv = ar[j];
						I = j;
					}
				}
			}
			totalWatt += switchLeft*min;
			switchLeft--;
			S = idxv;
			ar[I] = -1;
		}
		printf("%d\n", totalWatt);
	}


	return 0;
}
