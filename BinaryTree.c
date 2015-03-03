#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    int level;
    struct node * parent;
    struct node * lChild;
    struct node * rChild;
}Node;
int POW(int x, int y)
{
    int i,ans=1;
    for(i=0;i<y;i++)
        ans=ans*x;
    return ans;

}
Node * initializeBinaryTree()
{
    Node * tree = (Node*) malloc(sizeof(Node));
    tree->parent = tree->lChild = tree->rChild = NULL;
    tree->data = -1;
    return tree;
}
void inOrderTraversal(Node * tree)
{
    if(!tree)
        return;
    inOrderTraversal(tree->lChild);
    printf("%d ",tree->data);
    inOrderTraversal(tree->rChild);
}
Node * findParent(Node* tree, int level)
{
    Node* n = tree;
    Node* ans=NULL;
    if(!n)
        return NULL;
    if(n->level == level && (n->lChild == NULL || n->rChild == NULL))
    {
        return n;
    }
    ans = findParent(n->lChild,level);
    if(!ans)
        ans = findParent(n->rChild,level);
    return ans;
}
Node * LastLevel(Node * tree, Node * node,int reset)
{
    static int lastLevel = 0;
    if(reset)
        lastLevel = 0;
    Node * ans= NULL;
    if(!node)
        return NULL;
    if(node->lChild == NULL || node->rChild == NULL )
    {
        lastLevel = node->level;
        return findParent(tree,lastLevel);
    }
    if(lastLevel == 0)
    {
        ans = LastLevel(tree,node->lChild,0);
        if(!ans)
            ans = LastLevel(tree,node->rChild,0);
    }
    return ans;
}
void insertNode(Node * tree, int data)
{
    static int level = 0;
    static int count = 0;
    if(!tree)
    {
        printf("\nTree not initialized!\n");
        return;
    }
    count++;
    Node * t = tree;
    if(count == 1)
    {
        t->data = data;
        t->level = level++;
    }
    else
    {
        if(count >= POW(2,level+1)  )
            level++;
        Node * n = (Node*) malloc(sizeof(Node));
        n->data = data;
        n->level = level;
        n->lChild = n->rChild = NULL;

        Node * p = LastLevel(tree,tree,1);
        if(p == NULL)
        {
            printf("\nerror: last parent is NULL!!\n");
            free(n);
            exit(0);
        }
        if(p->lChild == NULL)
        {
            p->lChild = n;
            n->parent = p;
        }
        else
        {
            p->rChild = n;
            n->parent = p;
        }
    }
}
int main()
{
    int N,i,t;
    Node* tree = initializeBinaryTree();
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        scanf("%d",&t);
        insertNode(tree,t);
    }
    inOrderTraversal(tree);

}
