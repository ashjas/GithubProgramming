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
}
void preOrder(Node * tree)
{
    if(tree == NULL)
        return;
    printf("%c ",tree->data);
    preOrder(tree->left);
    preOrder(tree->right);
}
int len;
Node * buildNiceTree(Node * tree, char * str, int i)
{
    if(str[i] == '\0')
        return NULL;
    if(tree == NULL)
    {
            tree = newNode(str[i]);
    }
    if(tree->data == 'n' && str[i] != '\0')
    {
        tree->left = buildNiceTree(tree->left,str,i+1);
        if(tree->left)
            tree->left->parent = tree;
        tree->right = buildNiceTree(tree->right,str,i+2);
        if(tree->right)
            tree->right->parent = tree;
    }
    return tree;

}
char * str = NULL;
int main()
{
    Node * tree = NULL;
    str = malloc(sizeof(char) * 10000);
    scanf("%s",str);
    len=strlen(str);
    printf("\nlen:%d\n",len);
    tree = buildNiceTree(tree,str,0);
    printf("\nPre:");
    preOrder(tree);
    return 0;
}
