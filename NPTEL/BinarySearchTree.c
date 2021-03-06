#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    int level;/*added initially.. but its not really used in any usefull calculation problem output*/
    struct node * parent;
    struct node * lChild;
    struct node * rChild;
}Node;
typedef struct list
{
    Node* nd;
    struct list* next;
}List;
List * list = NULL;
List * tail = NULL;
int POW(int x, int y)
{
    int i,ans=1;
    for(i=0;i<y;i++)
        ans=ans*x;
    return ans;

}
int printPostOrder= 0;
int depth = 0;
typedef struct Queue
{
    Node * n;
    struct Queue * tail;
    struct Queue * next;
}Queue;
int isQempty(Queue * Q)
{
    if(Q == NULL)
        return 1;
    else 
        return 0;
}
void pushToQ(Queue ** QQ, Node* n)
{
    Queue *Q = *QQ;
    Queue *node = (Queue*) malloc(sizeof(Queue));
    node->n=n;
    if(Q == NULL)
    {
        node->next = NULL;
        node->tail = node;
        Q = node;
    }
    else
    {
        node->next = NULL;
        Q->tail->next = node;
        Q->tail = node;
    }
    *QQ = Q;
}
Node* popQ(Queue ** QQ)
{
    if(*QQ == NULL)
        return NULL;
    else
    {
        Queue *Q = *QQ;
        Queue * node = Q;
        Node * val = Q->n;
        Queue * tail = Q->tail;
        Q = Q->next;
        if(Q)
            Q->tail = tail;
        free(node);
        *QQ = Q;
        return val;
    }
}
void postOrderTraversal(Node * tree,int *sum,int print)
{
    if(!tree)
        return ;
    postOrderTraversal(tree->lChild,sum,print);
    (*sum)++;
    postOrderTraversal(tree->rChild,sum,print);
    if(print)
        printf("%d ",tree->data);
}
void preOrderTraversal(Node * tree,int *sum,int print)
{
    if(!tree)
        return ;
    if(print)
        printf("%d ",tree->data);
    preOrderTraversal(tree->lChild,sum,print);
    (*sum)++;
    preOrderTraversal(tree->rChild,sum,print);
}
void inOrderTraversal(Node * tree,int *sum,int print)
{
    if(!tree)
        return ;
    inOrderTraversal(tree->lChild,sum,print);
    (*sum)++;
    if(print)
        printf("%d ",tree->data);
    inOrderTraversal(tree->rChild,sum,print);
}
Node * PrintTree(Node * tree )
{
    Queue *Q = NULL;
    pushToQ(&Q,tree);
    while(!isQempty(Q))
    {
        Node* nn = popQ(&Q);
        printf("%d ",nn->data);
        if(nn)
        {
            if(nn->lChild)
                pushToQ(&Q,nn->lChild);
            if(nn->rChild)
                pushToQ(&Q,nn->rChild);
        }
    }
}
Node * NewNode(int val)
{
    Node * temp = malloc(sizeof(Node));
    temp->data = val;
    temp->lChild = temp->rChild = NULL;
    return temp;
}
Node* insertNode(Node * tree, int data)
{
    if(tree == NULL)
        return NewNode(data);
    if(data < tree->data)
        tree->lChild = insertNode(tree->lChild,data);
    if(data > tree->data)
        tree->rChild = insertNode(tree->rChild,data);
    return tree;
}
int Query(Node * tree,int val)
{
    if(!tree)
        return depth = -1;
    if(tree->data == val)
        return depth;
    depth++;
    if(tree->data > val)
        Query(tree->lChild,val);
    else if(tree->data < val)
        Query(tree->rChild,val);
    return depth;
}
void Size(Node * tree, int val)
{
    int sum =0;
    if(!tree)
        return;
    Queue *Q = NULL;
    pushToQ(&Q,tree);
    while(!isQempty(Q))
    {
        Node* nn = popQ(&Q);
        if(nn)
        {
            if(nn->data == val)
            {
                inOrderTraversal(nn,&sum,0);
                printf("%d",sum);
                break;
            }
            if(nn->lChild && nn->lChild->data == val)
            {
                inOrderTraversal(nn->lChild,&sum,0);
                printf("%d",sum);
                break;
            }
            pushToQ(&Q,nn->lChild);
            if(nn->rChild && nn->rChild->data == val)
            {
                inOrderTraversal(nn->rChild,&sum,0);
                printf("%d",sum);
                break;
            }
            pushToQ(&Q,nn->rChild);
        }
    }
}
Node * inOrderSuccessor(Node * tree)
{
    Node * temp = tree;
    while(temp->lChild)
    {
        temp = temp->lChild;
    }
    return temp;

}
Node* removeNode(Node * tree, int val)
{
    if(tree == NULL)
        return tree;
    if(tree->data < val)
        tree->rChild = removeNode(tree->rChild, val);
    else if(tree->data > val)
        tree->lChild = removeNode(tree->lChild, val);
    else
    {
        if(tree->lChild == NULL)
        {
            Node * temp = tree->rChild;
            free(tree);
            return temp;
        }
        else if(tree->rChild == NULL)
        {
            Node * temp = tree->lChild;
            free(tree);
            return temp;
        }
        Node * temp = inOrderSuccessor(tree->rChild);
        tree->data = temp->data;
        tree->rChild = removeNode(tree->rChild,temp->data);
    }
    return tree;
}
int MAX(int a,int b)
{
    return a>b?a:b;
}
int height(Node * tree)
{
    if(!tree)
        return 0;
    int lHeight=0;
    int rHeight=0;
    lHeight = height(tree->lChild);
    rHeight = height(tree->rChild);

    return (1 + MAX(lHeight,rHeight));

}
int Diameter(Node * tree)
{
    if(!tree)
        return 0;
    int lHeight = 0;
    int rHeight = 0;
    int ld=0,rd=0;
    lHeight = height(tree->lChild);
    rHeight = height(tree->rChild);
    
    ld = Diameter(tree->lChild);
    rd = Diameter(tree->rChild);

    return (MAX(lHeight + rHeight+1,MAX(ld,rd)));

}
int main()
{
    int N,i,t,nOps,a,size=0;
    char c;
    Node * tree = NULL;
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        scanf("%d",&t);
        tree = insertNode(tree,t);
    }
    printf("\n");
    postOrderTraversal(tree,&a,1);
    printf("pre:\n");
    preOrderTraversal(tree,&a,1);
    printf("in:\n");
    inOrderTraversal(tree,&a,1);
    scanf("%d",&nOps);
    for(i=0;i<nOps;i++)
    {
        scanf(" %c",&c);
        switch(c)
        {
            case 'i':
                scanf("%d",&t);
                tree = insertNode(tree,t);
                printf("\n");
                postOrderTraversal(tree,&a,1);
                break;
            case 'r':
                scanf("%d",&t);
                tree = removeNode(tree,t);
                printf("\n");
                postOrderTraversal(tree,&a,1);
                break;
            case 'q':
                scanf("%d",&t);
                printf("\n");
                printf("%d",Query(tree,t));
                depth = 0;
                break;
            case 's':
                scanf("%d",&t);
                printf("\n");
                Size(tree,t);
                break;
            case 'w':
                printf("Dia:%d\n",Diameter(tree));
                inOrderTraversal(tree,&a,1);
                printf("\n");
                postOrderTraversal(tree,&a,1);
                break;
        }
    }
}
