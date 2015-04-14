#include <stdio.h>

#include <string.h>

int N,S;

unsigned int data[1005];

unsigned int cost[1005][1005][2]={0};

unsigned int Answer;

unsigned int GetMinCost(int left, int cur, int right, int isleft)

{

    if(cost[left][right][isleft]!=-1)

        return cost[left][right][isleft];



    unsigned int lCost=0,rCost=0;

    int remainSwitch;

    remainSwitch=N-(right-left-1);



    if(left>0)

    {

        lCost=GetMinCost(left-1,left,right,1)+(data[cur]-data[left])*remainSwitch;

    }

    if(right<N+1)

    {

        rCost=GetMinCost(left,right,right+1,0)+(data[right]-data[cur])*remainSwitch;

    }

    if(lCost==0)

        cost[left][right][isleft]=rCost;

    else if(rCost==0)

        cost[left][right][isleft]=lCost;

    else

        cost[left][right][isleft]=lCost<rCost?lCost:rCost;

    //printf("left:%d,right=%d,")

    return cost[left][right][isleft];

}

int main(void)

{

    int tc, T, i,j,temp,index;



    setbuf(stdout, NULL);

    freopen("in", "r", stdin);


    scanf("%d", &T);

    for(tc = 0; tc < T; tc++)

    {

        scanf("%d %d", &N, &S);

        for(i=1;i<=N;i++) {

            scanf("%d", &data[i]);

        }



        data[++N]=S;

        //Sort

        for(i=1;i<N;i++)

        {

            index=i;

            for(j=i+1;j<=N;j++)

            {

                if(data[index]>data[j])

                    index=j;

            }

            if(index!=i)

            {

                temp=data[index];

                data[index]=data[i];

                data[i]=temp;

            }

        }



        Answer = 0;

        memset(cost,-1,sizeof(cost));

        for(i=1;i<=N;i++)

        {

            if(data[i]==S)

                break;

        }



        index=i;



        Answer=GetMinCost(index-1,index,index+1,0);





        // Print the answer to standard output(screen).

        printf("%d\n", Answer);

    }



    return 0;//Your program should return 0 on normal termination.

}
