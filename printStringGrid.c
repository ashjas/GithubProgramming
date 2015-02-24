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
nodeStr *StrArrVertSubstr = NULL;
nodeStr *StrArrAns;
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

struct nodeStr* SortedMerge(struct nodeStr* a, struct nodeStr* b);
void FrontBackSplit(struct nodeStr* source,
        struct nodeStr** frontRef, struct nodeStr** backRef);

void MergeSort(struct nodeStr** headRef)
{
    struct nodeStr* head = *headRef;
    struct nodeStr* a;
    struct nodeStr* b;

    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    FrontBackSplit(head, &a, &b); 

    MergeSort(&a);
    MergeSort(&b);

    *headRef = SortedMerge(a, b);
}

struct nodeStr* SortedMerge(struct nodeStr* a, struct nodeStr* b)
{
    struct nodeStr* result = NULL;

    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    //if (a->data <= b->data)
    if (strcmp(a->str,b->str) <= 0)
    {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
}

void FrontBackSplit(struct nodeStr* source,
        struct nodeStr** frontRef, struct nodeStr** backRef)
{
    struct nodeStr* fast;
    struct nodeStr* slow;
    if (source==NULL || source->next==NULL)
    {
        *frontRef = source;
        *backRef = NULL;
    }
    else
    {
        slow = source;
        fast = source->next;

        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }
}
int valid(int i, int j)
{
    if(i >= 0 && i <M && j >= 0 && j < N)
        return 1;
    else return 0;
}
void AllPaths(int i, int j, int way)
{
    int k,flag=0;
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
            for(k=0;k<strlen(node->str);k++)
            {
                if(node->str[k] == c)
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 1)
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


//void substrings(char arr[], int n)
void substrings()
{
    int i;
    for(i=0;i<IDX;i++)
    {
        nodeStr * n = StrArrVert[i];
        while(n)
        {
            int pass,j,start,end,i;
            int no_of_strings = strlen(n->str) - 1;

            for(pass=0;pass<strlen(n->str);pass++)
            {
                start = 0;
                end = start+pass;
                for(j=no_of_strings;j>=0;j--)
                {
                    //print(arr,start, end);
                    nodeStr * sub = malloc(sizeof(nodeStr));
                    sub->str = malloc(sizeof(char) * 10);
                    sub->str[0]='\0';
                    sub->next = NULL;

                    for(i=start;i<=end;i++)
                    {
                        sprintf(sub->str + strlen(sub->str),"%c",n->str[i] );
                    }
                    if(StrArrVertSubstr == NULL)
                        StrArrVertSubstr = sub;
                    else
                    {
                        nodeStr* n = StrArrVertSubstr;
                        while(n)
                        {
                            if(n->next == NULL)
                            {
                                n->next = sub;
                                break;
                            }
                            n = n->next;
                        }
                    }
                    //printf("\n");
                    count ++;
                    start++;
                    end = start+pass;
                }
                no_of_strings--;
            }
            n = n->next;
        }
    }

}
/*void Sort-Remove-Dupes()
{

}*/
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
    //generate substrs with no duplicates.
    substrings();
    nodeStr * n = StrArrVertSubstr;
    printf("\n\nSubstrs:");
    while(n)
    {
        printf("|%s|",n->str);
        n = n->next;
    }
    MergeSort(&StrArrVertSubstr);
    n = StrArrVertSubstr;
    printf("\n\nSorted Substrs:");
    while(n)
    {
        printf("|%s|",n->str);
        n = n->next;
    }
    // no remove dupes.
    n = StrArrVertSubstr;
    StrArrAns = malloc(sizeof(nodeStr));
    StrArrAns->str = StrArrVertSubstr->str;
    StrArrAns->next = NULL;
    nodeStr * last = StrArrAns;
    n=n->next;
    while(n)
    {
        if(strcmp(n->str,last->str) != 0)
        {
            nodeStr * t = malloc(sizeof(nodeStr));
            t->next = NULL;
            t->str = n->str;
            last->next = t;
            last = last->next;
        }
        n= n->next;
    }
    printf("\n\nNo dupes Substrs:");
    n = StrArrAns;
    while(n)
    {
        printf("|%s|",n->str);
        n = n->next;
    }
   /* 
       char *str = malloc(100);
       scanf("%s",str);
       substrings(str,strlen(str));
       printf("count:%d",count);/**/
    return 0;
}
