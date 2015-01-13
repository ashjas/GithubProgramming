#include<stdio.h>
#include<stdlib.h>
int fact(int n)
{
    if (n == 1 || n == 0)
        return 1;
    return n * fact(n-1);
}
int main()
{
    int Num_of_Rows=0,num_transactions=0;
    int i;int read_line[100];int ans[100]={-2};int sum=0;
    for(i=0;i<100;i++)
        read_line[i]=-1;
    scanf("%d",&Num_of_Rows);
    scanf("%d",&num_transactions);
    for(i=0; i<= num_transactions ;i++)
    {
        // read 
        int k=0;
        char line[1024], *p, *e;
        long v;int j=0;int flag=0;
        for(k=0;k<100;k++)
            read_line[k]=-1;
        fgets(line, sizeof(line), stdin);
        p = line;
        for (p = line; ; p = e) {
            v = strtol(p, &e, 10);
            if (p == e)
                break;
            read_line[j++]=(int)v;
        }
        j=0;
        if(read_line[0] > Num_of_Rows )
        {
            ans[i] = -1;
            continue;
        }
        //calculate sum of coefficients ith line now.
        while(read_line[j+1] != -1)
        {int a,b,c;
            if(read_line[j+1] > Num_of_Rows || read_line[j+1] > read_line[0])
            {
                flag = 1;
                break;
            }
            sum = sum + ( fact(read_line[0])/ ( fact(read_line[j+1]) * fact(read_line[0] - read_line[j+1]) )  );
            j++;
        }
        if(flag == 0)
            ans[i] = sum;
        else
            ans[i] = -1;
        sum = 0;


    }
    for (i=1;i<= num_transactions ; i++)
    {
        printf("%d ",ans[i]);
    }
}
