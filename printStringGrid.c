#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int count = 0,M,N,IDX=0;
char **ARR;
typedef struct nodeStr
{
    char * str;
    struct nodeStr* next;
}nodeStr;
nodeStr **StrArrVert;
nodeStr **StrArrAns;
typedef struct coeff
{
    int x,y;
}coeff;
coeff A[9] ={
            {-1,-1},//0
            {-1,0},//1
            {-1,1},//2
            {0,-1},//3
            {0,0},//4
            {0,1},//5
            {1,-1},//6
            {1,0},//7
            {1,1},//8
            };

int PATH[8][8]={
                {1,2,5,8,7,6,3,0},//UR
                {1,0,3,6,7,8,5,2},//UL
                {3,0,1,2,5,8,7,6},//LU
                {5,2,1,0,3,6,7,8},//RU
                {7,8,5,2,1,0,3,6},//DR
                {7,6,3,0,1,2,5,8},//DL
                {3,6,7,8,5,2,1,0},//LD
                {5,8,7,6,3,0,1,2},//RD
                };

int valid(int i, int j)
{
    if(i >= 0 && i <M && j >= 0 && j < N)
        return 1;
    else return 0;
}
void AllPaths(int i, int j, int way)
{
    nodeStr * node = malloc(sizeof(nodeStr));
    node->str = malloc(sizeof(char) * 10);
    node->next = NULL;
    if(StrArrVert[IDX] == NULL)
        StrArrVert[IDX] = node;
    else
    {
        nodeStr * n = StrArrVert[IDX];
        while(n)
        {
            if(n->next == NULL)
            {
                n->next = node;
                break;
            }
            n = n->next;
        }
    }

    node->str[0]=ARR[i][j];
    node->str[1]='\0';
    int m,n;
    for(m=0; m<8; m++)
    {
        if(valid(i + A[PATH[way][m]].x , j + A[PATH[way][m]].y))
        {
            char c = ARR[i + A[PATH[way][m]].x]  [j + A[PATH[way][m]].y];
            if(node->str[strlen(node->str) - 1] == c)
                break;
            sprintf(node->str + strlen(node->str),"%c",c );
        }
        else break;
    }
}
void UR(int i, int j)
{
    nodeStr * node = malloc(sizeof(nodeStr));
    node->str = malloc(sizeof(char) * 10);
    node->next = NULL;
    if(StrArrVert[IDX] == NULL)
        StrArrVert[IDX] = node;
    else
    {
        nodeStr * n = StrArrVert[IDX];
        while(n)
        {
            if(n->next == NULL)
            {
                n->next = node;
                break;
            }
            n = n->next;
        }
    }

    node->str[0]=ARR[i][j];
    node->str[1]='\0';
    int m,n;
    for(m=0; m<8; m++)
    {
        if(valid(i + A[PATH[0][m]].x , j + A[PATH[0][m]].y))
        {
            char c = ARR[i + A[PATH[0][m]].x]  [j + A[PATH[0][m]].y];
            if(node->str[strlen(node->str) - 1] == c)
                break;
            sprintf(node->str + strlen(node->str),"%c",c );
        }
        else break;
    }
}
void UL(int i, int j)
{
    nodeStr * node = malloc(sizeof(nodeStr));
    node->str = malloc(sizeof(char) * 10);
    node->next = NULL;
    if(StrArrVert[IDX] == NULL)
        StrArrVert[IDX] = node;
    else
    {
        nodeStr * n = StrArrVert[IDX];
        while(n)
        {
            if(n->next == NULL)
            {
                n->next = node;
                break;
            }
            n = n->next;
        }
    }

    node->str[0]=ARR[i][j];
    node->str[1]='\0';
    int m,n;
    for(m=0; m<8; m++)
    {
        if(valid(i + A[PATH[1][m]].x , j + A[PATH[1][m]].y))
        {
            char c = ARR[i + A[PATH[1][m]].x]  [j + A[PATH[1][m]].y];
            if(node->str[strlen(node->str) - 1] == c)
                break;
            sprintf(node->str + strlen(node->str),"%c",c );
        }
        else break;
    }
}
void LU(int i, int j)
{
    nodeStr * node = malloc(sizeof(nodeStr));
    node->str = malloc(sizeof(char) * 10);
    node->next = NULL;
    if(StrArrVert[IDX] == NULL)
        StrArrVert[IDX] = node;
    else
    {
        nodeStr * n = StrArrVert[IDX];
        while(n)
        {
            if(n->next == NULL)
            {
                n->next = node;
                break;
            }
            n = n->next;
        }
    }

    node->str[0]=ARR[i][j];
    node->str[1]='\0';
    int m,n;
    for(m=0; m<8; m++)
    {
        if(valid(i + A[PATH[2][m]].x , j + A[PATH[2][m]].y))
        {
            char c = ARR[i + A[PATH[2][m]].x]  [j + A[PATH[2][m]].y];
            if(node->str[strlen(node->str) - 1] == c)
                break;
            sprintf(node->str + strlen(node->str),"%c",c );
        }
        else break;
    }
}
void RU(int i, int j)
{
    nodeStr * node = malloc(sizeof(nodeStr));
    node->str = malloc(sizeof(char) * 10);
    node->next = NULL;
    if(StrArrVert[IDX] == NULL)
        StrArrVert[IDX] = node;
    else
    {
        nodeStr * n = StrArrVert[IDX];
        while(n)
        {
            if(n->next == NULL)
            {
                n->next = node;
                break;
            }
            n = n->next;
        }
    }

    node->str[0]=ARR[i][j];
    node->str[1]='\0';
    int m,n;
    for(m=0; m<8; m++)
    {
        if(valid(i + A[PATH[3][m]].x , j + A[PATH[3][m]].y))
        {
            char c = ARR[i + A[PATH[3][m]].x]  [j + A[PATH[3][m]].y];
            if(node->str[strlen(node->str) - 1] == c)
                break;
            sprintf(node->str + strlen(node->str),"%c",c );
        }
        else break;
    }
}
void DR(int i, int j)
{
    nodeStr * node = malloc(sizeof(nodeStr));
    node->str = malloc(sizeof(char) * 10);
    node->next = NULL;
    if(StrArrVert[IDX] == NULL)
        StrArrVert[IDX] = node;
    else
    {
        nodeStr * n = StrArrVert[IDX];
        while(n)
        {
            if(n->next == NULL)
            {
                n->next = node;
                break;
            }
            n = n->next;
        }
    }

    node->str[0]=ARR[i][j];
    node->str[1]='\0';
    int m,n;
    for(m=0; m<8; m++)
    {
        if(valid(i + A[PATH[4][m]].x , j + A[PATH[4][m]].y))
        {
            char c = ARR[i + A[PATH[4][m]].x]  [j + A[PATH[4][m]].y];
            if(node->str[strlen(node->str) - 1] == c)
                break;
            sprintf(node->str + strlen(node->str),"%c",c );
        }
        else break;
    }
}
void DL(int i, int j)
{
    nodeStr * node = malloc(sizeof(nodeStr));
    node->str = malloc(sizeof(char) * 10);
    node->next = NULL;
    if(StrArrVert[IDX] == NULL)
        StrArrVert[IDX] = node;
    else
    {
        nodeStr * n = StrArrVert[IDX];
        while(n)
        {
            if(n->next == NULL)
            {
                n->next = node;
                break;
            }
            n = n->next;
        }
    }

    node->str[0]=ARR[i][j];
    node->str[1]='\0';
    int m,n;
    for(m=0; m<8; m++)
    {
        if(valid(i + A[PATH[5][m]].x , j + A[PATH[5][m]].y))
        {
            char c = ARR[i + A[PATH[5][m]].x]  [j + A[PATH[5][m]].y];
            if(node->str[strlen(node->str) - 1] == c)
                break;
            sprintf(node->str + strlen(node->str),"%c",c );
        }
        else break;
    }
}
void LD(int i, int j)
{
    nodeStr * node = malloc(sizeof(nodeStr));
    node->str = malloc(sizeof(char) * 10);
    node->next = NULL;
    if(StrArrVert[IDX] == NULL)
        StrArrVert[IDX] = node;
    else
    {
        nodeStr * n = StrArrVert[IDX];
        while(n)
        {
            if(n->next == NULL)
            {
                n->next = node;
                break;
            }
            n = n->next;
        }
    }

    node->str[0]=ARR[i][j];
    node->str[1]='\0';
    int m,n;
    for(m=0; m<8; m++)
    {
        if(valid(i + A[PATH[6][m]].x , j + A[PATH[6][m]].y))
        {
            char c = ARR[i + A[PATH[6][m]].x]  [j + A[PATH[6][m]].y];
            if(node->str[strlen(node->str) - 1] == c)
                break;
            sprintf(node->str + strlen(node->str),"%c",c );
        }
        else break;
    }
}
void RD(int i, int j)
{
    nodeStr * node = malloc(sizeof(nodeStr));
    node->str = malloc(sizeof(char) * 10);
    node->next = NULL;
    if(StrArrVert[IDX] == NULL)
        StrArrVert[IDX] = node;
    else
    {
        nodeStr * n = StrArrVert[IDX];
        while(n)
        {
            if(n->next == NULL)
            {
                n->next = node;
                break;
            }
            n = n->next;
        }
    }

    node->str[0]=ARR[i][j];
    node->str[1]='\0';
    int m,n;
    for(m=0; m<8; m++)
    {
        if(valid(i + A[PATH[7][m]].x , j + A[PATH[7][m]].y))
        {
            char c = ARR[i + A[PATH[7][m]].x]  [j + A[PATH[7][m]].y];
            if(node->str[strlen(node->str) - 1] == c)
                break;
            sprintf(node->str + strlen(node->str),"%c",c );
        }
        else break;
    }
}
void print(char arr[], int start, int end)
{
    int i;
    for(i=start;i<=end;i++)
    {
        printf("%c",arr[i]);
    }
    printf("\n");
    count++;
}


void substrings(char arr[], int n)
{
    int pass,j,start,end;
    int no_of_strings = n-1;

    for(pass=0;pass<n;pass++)
    {
        start = 0;
        end = start+pass;
        for(j=no_of_strings;j>=0;j--)
        {
            print(arr,start, end);
            start++;
            end = start+pass;
        }
        no_of_strings--;
    }

}

int main()
{  
    int i,j,s1,s2i,way;
    scanf("%d%d",&M,&N); 
    //scanf("%d%d",&s1,&s2); 
    //printf("\n%d %d\n",M,N);
    ARR = (char **) malloc(sizeof(char*) * M);
    for(i=0;i<N;i++)
        ARR[i] = malloc(sizeof(char) * N);
    for(i =0;i<M;i++)
        for(j=0;j<N;j++)
            scanf(" %c",&ARR[i][j]);
    StrArrVert = (nodeStr**) malloc(sizeof(nodeStr*) * M * N);
    for(i = 0 ;i < M*N;i++)
    {
        StrArrVert[i] = NULL;// initialize linklist to be NULL initially.
    }
    printf("\n");
    for(i = 0; i< M;i++)
        for(j=0;j<N;j++)
        {
            for(way = 0;way<8;way++)
                AllPaths(i,j,way);
        /*    UR(i,j);
            UL(i,j);
            LU(i,j);
            RU(i,j);
            DR(i,j);
            DL(i,j);
            LD(i,j);
            RD(i,j);/**/
            IDX++;
        }
    for(i =0;i<M*N;i++)
        {
            printf("\n%d:",i);
            nodeStr * n = StrArrVert[i];
            while(n)
            {
                printf("|%s| ",n->str);
                n = n->next;
            }
        }
    /*
       char *str = malloc(100);
       scanf("%s",str);
    substrings(str,strlen(str));
    printf("count:%d",count);*/
    return 0;
}
