#include<stdlib.h>
#include<stdio.h>

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
    printf("%d ",tree->data);
    preOrder(tree->left);
    preOrder(tree->right);
}
Node * buildNiceTree(Node * tree, char * str)
{
    if(tree == NULL)
    {
        if(str[0] != '\n')
            tree = newNode(str[0]);
        else 
            return NULL;
    }
    if(tree->data != 'l')
    {
        tree->left = buildNiceTree(tree->left,str++);
        if(tree->left)
            tree->left->parent = tree;
        tree->right = buildNiceTree(tree->right,str++);
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

    tree = buildNiceTree(tree,str);
    printf("\nPre:");
    preOrder(tree);
    return 0;
}
