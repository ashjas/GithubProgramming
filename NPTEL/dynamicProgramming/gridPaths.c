#include<stdio.h>
#include<stdlib.h>
void print(int ar[][6])
{
    int i,j;
    for(i=0;i<11;i++)
    {
        for(j=0;j<6;j++)
        {
            printf("%d ",ar[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int i,j;
    int ar[11][6] = {
                        -1,0,0,0,0,0,
                        -1,0,0,0,0,0,
                        -1,0,0,0,0,0,
                        -1,0,0,0,0,0,
                        -1,0,0,0,0,0,
                        -1,0,0,0,0,0,
                        //0,0,-1,0,-1,0,
                        -1,0,-1,0,-1,0,
                        -1,0,0,0,0,0,
                        -1,0,0,0,0,0,
                        -1,0,0,0,0,0,
                        0,0,0,0,0,0
                    };
    if(ar[10][0] != -1)
        ar[10][0] = 1;
    else 
        ar[10][0] = 0;
    print(ar);
    printf("\n");
    for(i=10;i>=0;i--)
    {
        for(j=0;j<6;j++)
        {
            if(i==10 && j>0 )
            {
                if(ar[i][j] != -1)
                    ar[i][j] = ar[i][j-1];
                else
                    ar[i][j] = 0;
            }
            else if(j==0 && i<10 )
            {
                if(ar[i][j] != -1)
                    ar[i][j] = ar[i+1][j];
                else
                    ar[i][j] = 0;
            }
            else if(i<10 && j>0 )
            {
                if(ar[i][j] != -1)
                    ar[i][j]= ar[i][j-1] + ar[i+1][j];
                else
                    ar[i][j] = 0;
            }
            else if(ar[i][j] == -1)
                ar[i][j] = 0;
        }
    }
    print(ar);

}
