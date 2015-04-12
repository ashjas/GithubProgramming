#include<iostream>
#include<vector>
using namespace std;
vector <int> vi;
#define Rep(i,n) for(int i(0),_n(n);i<_n;++i)
int main()
{
	int T, i, j, k ;
	char buf[1010];
	freopen("C:\\in.txt", "r", stdin);
	freopen("C:\\out.txt", "w", stdout);
	scanf("%d", &T);
	Rep(i, T)
	{
		int Smax,stood=0,tneed=0;
		scanf("%d ", &Smax);
		gets(buf);
		Rep(j, Smax+1)
		{
			int need;
			if (stood >= j)
			{
				char ch[2];
				ch[0]= buf[j];
				ch[1] = '\0';
				stood += atoi(ch);
			}
			else
			{
				char ch[2];
				ch[0] = buf[j];
				ch[1] = '\0';
				need = j - stood;
				stood += need + atoi(ch);
				tneed += need;
			}
		}
		printf("Case #%d: %d\n", i + 1, tneed);
	}
	return 0;
}
