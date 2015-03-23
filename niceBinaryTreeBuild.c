#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct node
{
    char data;
    struct node* left;
    struct node* right;
    struct node* parent;
}Node;
Node * newNode(char c )
{
    Node * n = malloc (sizeof(Node));
    n->data = c;
    n->left = n->right = NULL;
    return n;
}
void preOrder(Node * tree)
{
    if(tree == NULL)
        return;
    printf("%c",tree->data);
    preOrder(tree->left);
    preOrder(tree->right);
}
int len;
int ii = -1;
int size =0;
int MAX(int a,int b)
{
    return a>b?a:b;
}
int Depth(Node * tree)
{
    if(!tree)
        return 0;
    int lH=0,rH=0;
    lH = Depth(tree->left);
    rH = Depth(tree->right);
    return (1+ MAX(lH,rH));

}
Node * buildNiceTree(Node * tree, char * str)
{
    ++ii;
    if(ii >len)
        return NULL;
    if(str[ii] == '\0')
        return NULL;
    if(tree == NULL)
    {
            tree = newNode(str[ii]);
    }
    if(tree->data == 'n' && str[ii] != '\0')
    {
        tree->left = buildNiceTree(tree->left,str);
        if(tree->left)
            tree->left->parent = tree;
        tree->right = buildNiceTree(tree->right,str);
        if(tree->right)
            tree->right->parent = tree;
    }
    return tree;

}
char ** strArray = NULL;
int main()
{
    int T=0,i;
    Node * tree[20] ;
    for(i=0;i<20;i++)
        tree[i] = NULL;
        //tree = (Node**)maloc (sizeof(Node*) * 20);
    scanf("%d",&T);
    strArray = (char **)malloc(sizeof(char*) * T);
    for(i=0;i<T;i++)
    {
        strArray[i] = malloc (sizeof(char) * 10000);
        scanf(" %s",strArray[i]);
        //printf("\nstr:%s",strArray[i]);
    }
    for(i=0;i<T;i++)
    {
        len = strlen(strArray[i]);
        tree[i] = buildNiceTree(tree[i],strArray[i]);
        //printf("\npre:");
        //preOrder(tree);
        printf("%d\n",Depth(tree[i])-1);
        //tree = NULL;
        ii=-1;
    }
    //len=strlen(str);
    //printf("\nlen:%d\n",len);
    //printf("\n");
    //preOrder(tree);
    return 0;
}
