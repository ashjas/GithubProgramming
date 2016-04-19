#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<iostream>
using namespace std;
int Grid[4][4];
int Grid2[4][4];
int COUNT[4][4];
char input[5];
int N;
#define BLOCK 2
#define OCCUPY 1
#define WALL -1
#define EMPTY 0
void SetCount(int i, int j)
{
	int count = 0;
	if (Grid[i][j] != OCCUPY)
	{
		//Grid[i][j] = OCCUPY;
		// BLOCK all clumns
		for (int k = j + 1; k < N; k++)//block all columns in row forward
		{
			if (Grid[i][k] == EMPTY)
				count++;
			if (Grid[i][k] == WALL)
				break;
		}
		for (int k = j - 1; k >= 0; k--)//block all columns in row forward
		{
			if (Grid[i][k] == EMPTY)
				count++;
			if (Grid[i][k] == WALL)
				break;
		}
		//Block all rows
		for (int k = i + 1; k < N; k++)//block all columns in row forward
		{
			if (Grid[k][j] == EMPTY)
				count++;
			if (Grid[k][j] == WALL)
				break;
		}
		for (int k = i - 1; k >= 0; k--)//block all columns in row forward
		{
			if (Grid[k][j] == EMPTY)
				count++;
			if (Grid[k][j] == WALL)
				break;
		}
		COUNT[i][j] = count;
	}
}
void SetRook(int i,int j)
{
	Grid[i][j] = OCCUPY;
	// BLOCK all clumns
	for (int k = j + 1; k < N; k++)//block all columns in row forward
	{
		if (Grid[i][k] == EMPTY)
			Grid[i][k] = BLOCK;
		if (Grid[i][k] == WALL)
			break;
	}
	for (int k = j - 1; k >= 0; k--)//block all columns in row forward
	{
		if (Grid[i][k] == EMPTY)
			Grid[i][k] = BLOCK;
		if (Grid[i][k] == WALL)
			break;
	}
	//Block all rows
	for (int k = i + 1; k < N; k++)//block all columns in row forward
	{
		if (Grid[k][j] == EMPTY)
			Grid[k][j] = BLOCK;
		if (Grid[k][j] == WALL)
			break;
	}
	for (int k = i - 1; k >= 0; k--)//block all columns in row forward
	{
		if (Grid[k][j] == EMPTY)
			Grid[k][j] = BLOCK;
		if (Grid[k][j] == WALL)
			break;
	}
	
}
int MAX(int a,int b)
{
	if (a > b)
		return a;
	else return b;

}
void resetCOUNT()
{
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			COUNT[j][k] = 9999;
		}
	}
}
void resetGrid()
{
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			Grid2[j][k] = Grid[j][k] = -3;
		}
	}
}
int isleft()
{
	for (int j = 0; j < N; j++)
	{
		for (int k = 0; k < N; k++)
		{
			if (Grid[j][k] == EMPTY)
				return 1;
		}
	}
	return 0;
}
int main()
{
	int i, T;
	freopen("Text.txt", "r", stdin);
	cin >> T;
	for (i = 0; i < T; i++)
	{
		cin >> N;
		
		for (int j = 0; j < N; j++)
		{
			cin >> input;
			for (int k = 0; k < N; k++)
			{
				if (input[k] == '.')
					Grid2[j][k] = Grid[j][k] = EMPTY;
				if (input[k] == 'X')
					Grid2[j][k] = Grid[j][k] = WALL;
			}
		}
		
		while (isleft())
		{
			resetCOUNT();
			for (int j = 0; j < N; j++)
			{
				for (int k = 0; k < N; k++)
				{
					if (Grid[j][k] != WALL && Grid[j][k] != BLOCK)
					{
						SetCount(j, k);
					}
				}
			}
			int minCount = 99999; int minj, mink;
			for (int j = 0; j < N; j++)
			{
				for (int k = 0; k < N; k++)
				{
					if (COUNT[j][k] < minCount)
					{
						minCount = COUNT[j][k];
						minj = j; mink = k;
					}
				}
			}
			SetRook(minj, mink);
		}

		int ans1 = 0;
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				if (Grid[j][k] == OCCUPY)
					ans1++;
			}
		}
		

		
		printf("Case #%d\n%d\n",i+1,ans1);
	}
	return 0;
}
#if 0
5
4
.X..
....
XX..
....
2
XX
.X
3
.X.
X.X
.X.
3
...
.XX
.XX
4
....
....
....
....

Output:
Case #1
5
Case #2
1
Case #3
5
Case #4
2
Case #5
4
#endif
