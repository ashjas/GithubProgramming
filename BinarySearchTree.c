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
Node * initializeBinaryTree()
{
    Node * tree = (Node*) malloc(sizeof(Node));
    tree->parent = tree->lChild = tree->rChild = NULL;
    tree->data = -1;
    return tree;
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
Node * LastParentForInsert(Node * tree ,int val)/*this is used for insertion, to get to the last parent, to which new node will be added as a child.*/
{
    if(!tree || tree->data == val)
        return NULL;
    if(tree->lChild == NULL && tree->data > val)
        return tree;
    if(tree->rChild == NULL && tree->data < val)
        return tree;
    if(tree->data < val)
        LastParentForInsert(tree->rChild,val);
    else
        LastParentForInsert(tree->lChild,val);
}
Node * LastParentForRemove(Node * tree )/*this gives the largest labled parent whose left/right gets deleted after swapping its value with key to be deleted.*/
{
    Queue *Q = NULL;
    Node * lastParent = tree;;
    pushToQ(&Q,tree);
    while(!isQempty(Q))
    {
        Node* nn = popQ(&Q);
        if(nn)
        {
            if(nn->lChild == NULL)
                return lastParent;
            else
                pushToQ(&Q,nn->lChild);
            if(nn->rChild == NULL)
                return nn;
            else
                pushToQ(&Q,nn->rChild);
        }
        lastParent = nn;
    }
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
void insertNode(Node * tree, int data)
{
    static int level = 0;
    static int count = 0;
    int a;
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

        Node * p = LastParentForInsert(tree,data);
        if(p == NULL)
        {
            printf("\nerror: last parent is NULL!!\n");
            //print postOrderTraversal.
            postOrderTraversal(tree,&a,1);
            free(n);
            return;
            //exit(0);
        }
        if(p->data > data)
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
int Query(Node * tree,int val,int reset)
{
    static int ans = 0;
    if(reset)
        ans = 0;
    if(!tree)
        return 0;
    Query(tree->lChild,val,0);
    if(tree->data == val)
        ans++;
    Query(tree->rChild,val,0);
    return ans;
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
void Remove(Node * tree, int val)
{
    if(!tree)
        return;
    Node * p = LastParentForRemove(tree);
    if(p->rChild == NULL)
        p = p->lChild;// this has to be the last leaf to be swapped and deleted.
    else
        p = p->rChild;// otherwise this would be it.


    Queue *Q = NULL;
    pushToQ(&Q,tree);
    while(!isQempty(Q))
    {
        Node* nn = popQ(&Q);
        if(nn)
        {
            if(nn->data == val)/* this is for checking if the current visited node has the key to be deleted.*/
            {
                nn->data = p->data;
                if(nn->data == p->data)
                    pushToQ(&Q,nn);
                //printf("\nremoving b/w levels:%d,%d",nn->lChild->level,p->level);
                if(p->parent->lChild == p)
                {
                    p->parent->lChild = NULL;
                    free(p);
                }
                else
                {
                    p->parent->rChild = NULL;
                    free(p);
                }
                {
                    p = LastParentForRemove(tree);
                    if(p->rChild == NULL)
                        p = p->lChild;// this has to be the last leaf to be swapped and deleted.
                    else
                        p = p->rChild;// otherwise this would be it.
                }
            }
            if(nn->lChild && nn->lChild->data == val)
            {
                nn->lChild->data = p->data;
                if(nn->lChild->data == p->data)
                    pushToQ(&Q,nn);
                //printf("\nremoving b/w levels:%d,%d",nn->lChild->level,p->level);
                if(p->parent->lChild == p)
                {
                    p->parent->lChild = NULL;
                    free(p);
                }
                else
                {
                    p->parent->rChild = NULL;
                    free(p);
                }
                {
                    p = LastParentForRemove(tree);
                    if(p->rChild == NULL)
                        p = p->lChild;// this has to be the last leaf to be swapped and deleted.
                    else
                        p = p->rChild;// otherwise this would be it.
                }
            }
            pushToQ(&Q,nn->lChild);
            if(nn->rChild && nn->rChild->data == val)
            {
                nn->rChild->data = p->data;
                if(nn->rChild->data == p->data)
                    pushToQ(&Q,nn);
                if(p->parent->rChild == p)
                {
                    p->parent->rChild = NULL;
                    free(p);
                }
                else
                {
                    p->parent->lChild = NULL;
                    free(p);

                }
                {
                    p = LastParentForRemove(tree);
                    if(p->rChild == NULL)
                        p = p->lChild;// this has to be the last leaf to be swapped and deleted.
                    else
                        p = p->rChild;// otherwise this would be it.
                }
            }
            pushToQ(&Q,nn->rChild);
        }
    }
}
int main()
{
    int N,i,t,nOps,a,size=0;
    char c;
    Node* tree = initializeBinaryTree();
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        scanf("%d",&t);
        insertNode(tree,t);
    }
    printf("\n");
    postOrderTraversal(tree,&a,1);
    scanf("%d",&nOps);
    for(i=0;i<nOps;i++)
    {
        scanf(" %c",&c);
        switch(c)
        {
            case 'i':
                scanf("%d",&t);
                insertNode(tree,t);
                printf("\n");
                postOrderTraversal(tree,&a,1);
                printf("\nPrint: ");
                PrintTree(tree);
                break;
            case 'r':
                scanf("%d",&t);
                Remove(tree,t);
                printf("\n");
                inOrderTraversal(tree,&a,1);
                break;
            case 'q':
                scanf("%d",&t);
                printf("\n");
                printf("%d",Query(tree,t,1));
                break;
            case 's':
                scanf("%d",&t);
                printf("\n");
                Size(tree,t);
                break;
        }
    }
}
