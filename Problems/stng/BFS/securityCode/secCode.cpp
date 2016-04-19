#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<iostream>
#include<string>
using namespace std;
#define R_MAX 9999
int allPrimes[R_MAX][1000];
int visited[R_MAX];
int level[R_MAX];
int parent[R_MAX];
bool isPrime[R_MAX];
int N1,N2;
int Q[R_MAX];
int front = 0;
int tail = 0;

void enQ(int n)
{
    if (tail < R_MAX)
        Q[tail++] = n;
}
int dQ()
{
    int n = -1;
    if (front < R_MAX)
        n = Q[front++];
    return n;
}
int isQempty()
{
    if (front == tail)
        return 1;
    return 0;
}
int countToSource()
{
    int n = N2; int count = 0;
    while (parent[n] != 0)
    {
        printf("parent[%d]=%d\n",n,parent[n]);
        n = parent[n];
        count++;
    }
    return count;
}
void printChilds(int prn)
{
    for (int i = 1000; i < R_MAX; i++)
    {
        if(parent[i] == prn)
        {
            printf("%d:%d,",i,level[i]);
        }
    }
}
int BFS(int start)
{
    enQ(start);
    level[start] = parent[start] = 0;
    for (int i = 0; i < R_MAX; i++)
    {
        level[i] = visited[i] = 0;
    }
    while (front < tail)
    {
        int v = dQ();
        if (v == -1)
            break;
        visited[v] = 1;
        for (int i = 0; i < 1000, allPrimes[v][i] != 0; i++)
        {
            if (visited[allPrimes[v][i]] == 0)
            //if (level[allPrimes[v][i]] == 0 && visited[allPrimes[v][i]] == 0)
            {
                enQ(allPrimes[v][i]);
                parent[allPrimes[v][i]] = v;
                level[allPrimes[v][i]] = level[v] + 1;
            }
        }
/*        printf("\nChilds:of    %d == ",v);
        printChilds(v);
        printf("\nAllPrimes:of %d == ",v);
        for (int i = 0; i < 1000, allPrimes[v][i] != 0; i++)
            printf("%d,",allPrimes[v][i]);
            /**/

    }

    for (int i = 1000; i < R_MAX; i++)
    {
        //printf("\nChilds:of    %d == ",i);
        //printChilds(i);
/*       printf("\nAllPrimes:of %d == ",i);
        for (int j = 0; j < 1000, allPrimes[i][j] != 0; j++)
            printf("%d,",allPrimes[i][j]);
            /**/
    }
    printf("\n Level[N2]:%d",level[N2]);
    if (parent[N2] == 0)
    {
        return 0;
    }
    else
    {
        return countToSource();
    }
}
int checkPrime(int num)
{
    for (int i = 2; i <= num / 2; i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}
void setPrimes()
{
    for(int i = 1000; i<R_MAX; i++)
        {
            if(checkPrime(i) == 1)
            {
                isPrime[i]= true;
            //printf("%d ",i);
            }
        }
}

int createNum(int a,int b,int c,int d)
{
    return (a * 1000 + b * 100 + c * 10 + d);
}


void makeGraph(int n)
{
    int digit[4]; int j = 0;
    int q = 10; int nn = n;

    for (int i = 0; i < 4; i++)
    {
        digit[i] = nn % q;
        nn = nn / q;
    }
    int minus = ((digit[3] - 1) * 1000);
    if (minus < 0)
        minus = 0;
    for (int i = n - minus; i <= (n - minus + (8 * 1000)); i +=1000 )
    {
        if (i == n)
            continue;
        if (isPrime[i] == true)
        {
            allPrimes[n][j++] = i;
        }
    }
    minus = ((digit[2] - 1) * 100);
    if (minus < 0)
        minus = 0;
    for (int i = n - minus; i <= (n - minus + (8 * 100)); i += 100)
    {
        if (i == n)
            continue;
        if (isPrime[i] == true)
        {
            allPrimes[n][j++] = i;
        }
    }
    minus = ((digit[1] - 1) * 10);
    if (minus < 0)
        minus = 0;
    for (int i = n - minus; i <= (n - minus + (8 * 10)); i += 10)
    {
        if (i == n)
            continue;
        if (isPrime[i] == true)
        {
            allPrimes[n][j++] = i;
        }
    }
    minus = (digit[0] - 1);
    if (minus < 0)
        minus = 0;
    for (int i = n - minus; i <= (n - minus + 8 ); i += 1)
    {
        if (i == n)
            continue;
        if (isPrime[i] == true)
        {
            allPrimes[n][j++] = i;
        }
    }

}
void reset()
{
    for (int i = 1000; i < R_MAX; i++)
    {
        for (int j = 0; j < 1000; j++)
            allPrimes[i][j]=0;
    }
    for (int j = 0; j < R_MAX; j++)
        Q[j] = 0;
    front = tail = 0;
}
int main()
{
    int i, T;
    freopen("Text.txt", "r", stdin);
    cin >> T;
    setPrimes();
    for (i = 0; i < T; i++)
    {
        cin >> N1 >> N2;
        for (int j = 1000; j <= R_MAX;j++)
            if(isPrime[j])
                makeGraph(j);

                makeGraph(8017);
    //    if(i == 1)
        printf("Case #%d\n%d\n", i + 1, BFS(N1));
        reset();
    }
    return 0;
}
#if 0
3
1033 8179
1373 8017
1033 1033
-------------------
Case #1
6
Case #2
7
Case #3
0
#endif

