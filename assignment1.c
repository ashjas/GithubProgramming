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
    int i;int ans[100]={-2};int sum=0;
    scanf("%d",&Num_of_Rows);
    scanf("%d",&num_transactions);
    for(i=0; i<= num_transactions ;i++)
    {
        // read 
        int k=0,row=0;
        char line[1024], *p, *e;
        long v;
        fgets(line, sizeof(line), stdin);
        p = line;k=0;
        for (p = line; ; p = e,k++) {
            v = strtol(p, &e, 10);
            if (p == e)
                break;
            if(k == 0)
            {
                if(v > Num_of_Rows)
                {
                    sum = -1;
                    break;
                }
                row = (int)v;
            }
            else
            {
                if(v > Num_of_Rows || v > row )
                {
                    sum = -1;
                    break;
                }
                else
                    sum = sum + ( fact(row) / ( fact(v) * fact( row - v ) )  );
            }
        }
        ans[i] = sum;
        sum = 0;
    }
    for (i=1;i<= num_transactions ; i++)
    {
        printf("%d ",ans[i]);
    }

}
