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
       // return findParent(tree,lastLevel);
    }
    if(lastLevel == 0)
    {
        ans = LastLevel(tree,node->lChild,0);
        if(!ans)
            ans = LastLevel(tree,node->rChild,0);
    }
    return ans;
}
Node * LastLevel2(Node * tree )
{
    Queue *Q = NULL;
    pushToQ(&Q,tree);
    while(!isQempty(Q))
    {
        Node* nn = popQ(&Q);
        if(nn)
        {
            if(nn->lChild == NULL)
                return nn;
            else
                pushToQ(&Q,nn->lChild);
            if(nn->rChild == NULL)
                return nn;
            else
                pushToQ(&Q,nn->rChild);
        }
    }
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

        Node * p = LastLevel2(tree);
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
int Query(Node * tree,int val)
{
    static int ans = 0;
    if(!tree)
        return 0;
    Query(tree->lChild,val);
    if(tree->data == val)
    {
        if(list == NULL)
        {
            list = (List*)malloc(sizeof(List));
            list->nd = tree;
            list->next=NULL;
            tail = list;
        }
        else
        {
            List *ll = (List*)malloc(sizeof(List));
            ll->nd = tree;
            ll->next = NULL;
            tail->next = ll;
            tail = ll;
        }
        ans++;
    }
    Query(tree->rChild,val);
    return ans;
}
void Remove(Node * tree, int val)
{
    List *list = NULL;
    if(!tree)
        return;
    Node * p = LastLevel2(tree);
    List * ll = list;
    while(ll)
    {
        ll->nd->data = p->data;
        if(p->parent->lChild == p)
        {
            free(p);
            p->parent->lChild = NULL;
        }
        else
        {
            free(p);
            p->parent->rChild = NULL;
        }
        ll=ll->next;
        Node * p = LastLevel2(tree);
    }

}
int main()
{
    int N,i,t,nOps;
    char c;
    Node* tree = initializeBinaryTree();
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        scanf("%d",&t);
        insertNode(tree,t);
    }
    printf("\n");
    inOrderTraversal(tree);
    printf("\n");
    scanf("%d",&nOps);
    for(i=0;i<nOps;i++)
    {
        scanf(" %c",&c);
        switch(c)
        {
            case 'i':
                scanf("%d",&t);
                insertNode(tree,t);
                printf("\nInsert\n");
                inOrderTraversal(tree);
                break;
            case 'r':
                scanf("%d",&t);
                Query(tree,t);
                Remove(tree,t);
                printf("\nRemove\n");
                inOrderTraversal(tree);
                break;
            case 'q':
                scanf("%d",&t);
                printf("\n%d",Query(tree,t));
                break;
            case 's':
                scanf("%d",&t);
                printf("\nsize\n");
                inOrderTraversal(tree);
                break;
        }
    }

}
