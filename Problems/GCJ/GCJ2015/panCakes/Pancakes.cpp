#include<iostream>
#include<vector>
#include<stack>
using namespace std;
typedef vector <stack<int>> vsi;
#define Rep(i,n) for(int i(0),_n(n);i<_n;++i)
int maxSize(vsi ar)
{
	int max=0;
	Rep(i, ar.size())
	{
		if (ar[i].size() > max)
			max = ar[i].size();
	}
	return max;
}
int maxFreq(vsi &ar)
{
	int freq = 0;
	int max = maxSize(ar);
	Rep(i, ar.size())
	{
		if (ar[i].size() == max)
			freq++;
	}
	return freq;
}
void divide(vsi &ar,int max)
{
	Rep(i, ar.size())
	{
		if (ar[i].size() == max)
		{
			stack<int> s;
			Rep(j, (ar[i].size() / 2))
			{
				ar[i].pop();
				s.push(1);
			}
			ar.push_back(s);
			break;
		}
	}
}
int hasCakes(vsi &ar)
{
	for (int i = 0; i < ar.size(); i++)
	{
		if (!ar[i].empty())
			return 1;
	}
	return 0;
}
void eat(vsi &ar)
{
	//Rep(i, ar.size())
	vsi::iterator iter = ar.begin();
	for (; iter != ar.end();iter++)
	{
		if ((*iter).size() >= 1)
		{
			//ar.erase(iter);
			//iter = ar.begin();
			(*iter).pop();
		}
		else
		{
			//ar[i].pop();
			//(*iter).pop();
		}
	}
}
int main()
{
	int T, i, j, k ;
	char buf[1010];
	freopen("C:\\in.txt", "r", stdin);
	freopen("C:\\out.txt", "w", stdout);
	scanf("%d", &T);
	Rep(i, T)
	{
		int diners;
		scanf("%d", &diners);
		vsi ar(diners);
		Rep(j, diners)
		{
			int a;
			scanf("%d", &a);
			Rep(k, a)
			{
				ar[j].push(1);
			}
		}
		int max = maxSize(ar), fmax = maxFreq(ar);
		int minutes = 0;
		vsi::iterator iter = ar.begin();
		//Rep(j, ar.size())
		//for (int j = 0; j < ar.size();j++)
		//for (; iter != ar.end();iter++)
		while (hasCakes(ar))
		{
			if (max > 0)
			{
				minutes++;
				if (fmax == 1 && max>1)
				{
					divide(ar, max);
					max = maxSize(ar);
					fmax = maxFreq(ar);
				}
				else
				{
					eat(ar);
					max--;
				}
			}
		}
		printf("Case #%d: %d\n", i + 1, minutes);
	}
	return 0;
}
