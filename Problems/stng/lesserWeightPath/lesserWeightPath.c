#include<stdio.h>
#define QSIZE 999
int W[999*999];
int Adj[999][3];
int N,M;

typedef struct _Q
{
    int data[QSIZE];
    int front;
    int tail;
}Q;
Q qq;

void resetQ()
{
    int i;
    qq.front = qq.tail = -1;
    for(i=0;i<QSIZE;i++)
        qq.data[i] = -1;
}
int isQFull()
{
    if(qq.tail >= QSIZE)
        return 1;
    return 0;
}
int isQEmpty()
{
    if(qq.front >= qq.tail)
        return 1;
    return 0;
}
void addToQ(int n)
{

    if(qq.front == -1 && qq.tail == -1)
    {
        qq.front = qq.tail = 0;
        qq.data[qq.tail++] = n;
    }
    else
    {
        if(!isQFull())
        {
            qq.data[qq.tail++] = n;
        }
    }
}
int deQ()
{
    if(!isQEmpty())
    {
        int n = qq.data[qq.front];
        qq.data[qq.front++] = -1;
        return n;
    }
    else
    {
        resetQ();
        return -1;
    }

}
int main()
{
    int T,i,j,k;
#if 0
    scanf("%d",&T);
    for(i=0;i<T;i++)
    {
        scanf("%d %d",&N,&M);
        for(j=0;j < (N * M) ; j++)
        {
            scanf("%d",&W[j]);
            Adj[j][0] = j+1;
            Adj[j][1] = j+M;
            Adj[j][2] = j+M+1;
        }
    }
#endif
}
// testQ output.
#if 0
void testQ()
{
    int i,j=0;
    resetQ();
    for(i=0;i<20;i++)
    {
        addToQ(i);
        printf("eQ:%d ",i);
    }
    printf("\n");
    for(i=0;i<20;i++)
    {
        printf("dQ:%d ",deQ());
    }
    printf("\nfront:%d tail:%d",qq.front,qq.tail);
    printf("\ntesting Q after dqueing equally");
    for(i=0;i<21;i++)
    {
        printf("%d: ",qq.data[i]);
    }
    deQ();
    printf("\nfront:%d tail:%d",qq.front,qq.tail);
    printf("\ntesting Q after dqueing extra");
    for(i=0;i<21;i++)
    {
        printf("%d: ",qq.data[i]);
    }

    // add and dQ alternatively...
    printf("\n");
    resetQ();
    
    printf("\n add 20\n");
    for(i=0;i<20;i++)
    {
        addToQ(j);
        printf("eQ:%d ",j++);
    }
    printf("\n remove 10\n");
    for(i=0;i<10;i++)
    {
        printf("dQ:%d ",deQ());
    }
    printf("\n add 20\n");
    for(i=0;i<20;i++)
    {
        addToQ(j);
        printf("eQ:%d ",j++);
    }
    printf("\nfront:%d tail:%d",qq.front,qq.tail);
    printf("\n printing all data\n");
    for(i=0;i<QSIZE;i++)
    {
        if(qq.data[i] != -1)
            printf("%d: ",qq.data[i]);
    }
    printf("\n one more dQue");
    deQ();
    printf("\nfront:%d tail:%d",qq.front,qq.tail);
    printf("\n printing all data\n");
    for(i=0;i<QSIZE;i++)
    {
        if(qq.data[i] != -1)
            printf("%d: ",qq.data[i]);
    }
    printf("\n ele[front -1]:%d ele[front]:%d ele[tail]:%d\n",qq.data[qq.front -1],qq.data[qq.front],qq.data[qq.tail]);

}
... output
eQ:0 eQ:1 eQ:2 eQ:3 eQ:4 eQ:5 eQ:6 eQ:7 eQ:8 eQ:9 eQ:10 eQ:11 eQ:12 eQ:13 eQ:14 eQ:15 eQ:16 eQ:17 eQ:18 eQ:19 
dQ:0 dQ:1 dQ:2 dQ:3 dQ:4 dQ:5 dQ:6 dQ:7 dQ:8 dQ:9 dQ:10 dQ:11 dQ:12 dQ:13 dQ:14 dQ:15 dQ:16 dQ:17 dQ:18 dQ:19 
front:20 tail:20
testing Q after dqueing equally-1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: 
front:-1 tail:-1
testing Q after dqueing extra-1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: -1: 

add 20
eQ:0 eQ:1 eQ:2 eQ:3 eQ:4 eQ:5 eQ:6 eQ:7 eQ:8 eQ:9 eQ:10 eQ:11 eQ:12 eQ:13 eQ:14 eQ:15 eQ:16 eQ:17 eQ:18 eQ:19 
remove 10
dQ:0 dQ:1 dQ:2 dQ:3 dQ:4 dQ:5 dQ:6 dQ:7 dQ:8 dQ:9 
add 20
eQ:20 eQ:21 eQ:22 eQ:23 eQ:24 eQ:25 eQ:26 eQ:27 eQ:28 eQ:29 eQ:30 eQ:31 eQ:32 eQ:33 eQ:34 eQ:35 eQ:36 eQ:37 eQ:38 eQ:39 
front:10 tail:40
printing all data
10: 11: 12: 13: 14: 15: 16: 17: 18: 19: 20: 21: 22: 23: 24: 25: 26: 27: 28: 29: 30: 31: 32: 33: 34: 35: 36: 37: 38: 39: 
one more dQue
front:11 tail:40
printing all data
11: 12: 13: 14: 15: 16: 17: 18: 19: 20: 21: 22: 23: 24: 25: 26: 27: 28: 29: 30: 31: 32: 33: 34: 35: 36: 37: 38: 39: 
ele[front -1]:-1 ele[front]:11 ele[tail]:-1

#endif
