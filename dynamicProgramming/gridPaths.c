#include<stdio.h>
#include<stdlib.h>

int main()
{
    int i,j;
    int ar[11][6] = {
                        0,0,0,0,0,0,
                        0,0,-1,0,0,0,
                        0,0,0,0,0,0,
                        0,-1,0,0,0,0,
                        0,0,-1,0,0,0,
                        0,0,0,0,0,0,
                        //0,0,-1,0,-1,0,
                        0,0,-1,0,0,0,
                        0,0,0,0,-1,0,
                        0,0,-1,0,0,0,
                        0,0,-1,0,0,0
                    };
    ar[10][0] = 1;
    for(i=10;i>=0;i--)
    {
        for(j=0;j<6;j++)
        {
            if(i == 10 && ar[i][j] != 1/*this skips ar[10][0] so [j-1] is not -1 out of bound*/)/*for bottom row.*/
                ar[i][j] = ar[i][j-1];
            if(j == 0  && ar[i][j] != 1/*this skips ar[10][0] so [i+1] is not 11 out of bound.*/)/*for left column and bottom row.*/
                ar[i][j] = ar[i+1][j];
            else if(ar[i][j] == 0)
            {
                ar[i][j] = ar[i][j-1] + ar[i+1][j];
            }
            else if(ar[i][j] == -1)/*these are holes*/
                ar[i][j] =  0;
        }
    }
    for(i=0;i<11;i++)
    {
        for(j=0;j<6;j++)
        {
            printf("%d ",ar[i][j]);
        }
        printf("\n");
    }

}
