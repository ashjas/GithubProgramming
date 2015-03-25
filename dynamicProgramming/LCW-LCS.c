#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char  str1[50],str2[50];
int MAX(int a,int b)
{
    return a>b?a:b;
}
int MIN(int a,int b)
{
    return a<b?a:b;
}
void print(int **arr,int len1,int len2)
{
    int i,j;
        printf("\n");
    for(i=0 ;i<len1 +1 ; i++)
    {
        for(j=0; j<len2 +1; j++)
        {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}
int LCW()
{
    int i,j,max=-1,imax,jmax;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int **arr = NULL;
    arr = (int **)malloc(sizeof(int*) * (len1 + 1));
    for(i=0;i < len1 + 1 ;i++)
        arr[i] = malloc(sizeof(int) * (len2 + 1));
    for(i=0;i<len1 +1;i++)
        arr[i][len2] = 0;
    for(i=0;i<len2 +1;i++)
        arr[len1][i] = 0;
    for(i=len1-1 ;i>=0 ; i--)
    {
        for(j=len2-1; j>=0; j--)
        {
            if(str1[i] == str2[j] )
                arr[i][j] = 1 + arr[i+1][j+1];
            else
                arr[i][j] = 0;
        }
    }

    for(i=len1-1 ;i>=0 ; i--)
    {
        for(j=len2-1; j>=0; j--)
            if(max < arr[i][j])
            {
                max = arr[i][j];
                imax = i;jmax=j;
            }
    }
    print(arr,len1,len2);
    printf("LCW String: ");
    for(i=0;i<max;i++)
    {
        printf("%c",str1[imax++]);
    }
    return max;
}
int LCS()
{
    int i,j,max=-1,k;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char  ans[50];int ansi=0;
    int **arr = NULL;
    arr = (int **)malloc(sizeof(int*) * (len1 + 1));
    for(i=0;i < len1 + 1 ;i++)
        arr[i] = malloc(sizeof(int) * (len2 + 1));
    for(i=0;i<len1 +1;i++)
        arr[i][len2] = 0;
    for(i=0;i<len2 +1;i++)
        arr[len1][i] = 0;
    for(i=len1-1 ;i>=0 ; i--)
    {
        int flag =0;
        for(j=len2-1; j>=0; j--)
        {
            if(str1[i] == str2[j] )
            {
                arr[i][j] = 1 + arr[i+1][j+1];
                printf("\n%d,%d",i,j);
                //printf("%c ",str1[i]);
                //if(flag == 0)
                {
                ans[arr[i][j]-1]=str1[i];
                flag++;
                }
                //break;
            }
            else
                arr[i][j] = MAX(arr[i][j+1],arr[i+1][j]);
        }
    }
    ans[arr[0][0]]='\0';
    print(arr,len1,len2);
    printf("LCS String: ");
    for(i=strlen(ans)-1;i>=0;i--)
        printf("%c",ans[i]);
printf("\n\n");
    for(i=len1-1,k=1 ;i>=0 ; i--)
    {
        for(j=len2-1; j>=0; j--)
        {
            if(arr[i][j] == k)
            {
                printf("%c ",str2[j]);
                k++;
                break;
            }
        }
    }
    /*
    for(j=0;j<len2 +1 ;j++)
    {
        for(i=0;i<len1 +1 ; i++)
        {
            //if(i+1 < len1+1 && str1[i] != str1[i+1])
            if(i> MIN(len1 +1, len2 +1))
            {
             j = len2 +2;
                break;
            }
            if(i+1 < len1 +1 && arr[i][j] != arr[i+1][j] )
            {
                printf("%c",str1[i]);
                break;
            }
        }
    }*/
    
    return arr[0][0];
}
int main()
{
    scanf("%s",str1);
    scanf("%s",str2);
    printf("\nLCW:%d",LCW());
    printf("\nLCS:%d",LCS());
}
