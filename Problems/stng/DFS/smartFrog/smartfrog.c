#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define SZ 501
int Grid[SZ][SZ];
int Visited[SZ][SZ];
int m, n;

int dfs(int i, int j)
{
	int ret_r = 1, ret_d = 1; int ret = 0;
	if (Visited[i][j] > 0)
		return Visited[i][j] ;
	for (int r = i + 1; r < m; r++)
	{
		if (Grid[r][j] <= Grid[i][j])
		{	
			ret_d += dfs(r, j);
		}
	}
	for (int c = j + 1; c < n; c++)
	{
		if (Grid[i][c] >= Grid[i][j] && Visited[i][c] == 0)
		{
			ret_r += dfs(i, c);
			
		}
	}
	ret = ret_r > ret_d ? ret_r : ret_d;
	if (ret > Visited[i][j])
		Visited[i][j] = ret;
	return Visited[i][j];
}
void reset()
{
	for (int j = 0; j<m; j++)
	{
		for (int k = 0; k<n; k++)
		{
			Visited[j][k] = 0;
		}
	}
}
int main()
{

	freopen("Text.txt", "r", stdin);
	int T;
	cin >> T;
	for (int i = 0; i<T; i++)
	{
		cin >> m >> n;
		for (int j = 0; j<m; j++)
		{
			for (int k = 0; k<n; k++)
			{
				cin >> Grid[j][k];
			}
		}

		int max = 0;
		for (int j = 0; j<m; j++)
		{
			for (int k = 0; k<n; k++)
			{
				dfs(j, k);
			}
		}
		int mm = 0;
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (Visited[j][k] > mm)
					mm = Visited[j][k];
			}
		}
		cout << "Case #" << i + 1 << endl;
		cout << mm << endl;
		reset();
	}
	return 0;
}
