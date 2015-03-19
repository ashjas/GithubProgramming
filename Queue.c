#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node* head;
    struct node* tail;
    struct node* next;
}Node;
int popQ(Node ** queue)
{

    if(!*queue)
        return -1;
    Node * head = *queue;
    Node * Q = head;
    int ret = head->data;
    Node * tail = head->tail;
    head = head->next;
    if(head)
        head->tail = tail;
    free(Q);
    *queue = head;
    return ret;
}
void pushToQ(Node ** queue ,int val)
{
    Node * head = *queue;
    Node * t = malloc(sizeof(Node));
    t->data = val;
    t->next = NULL;
    if(head == NULL)
    {
        t->tail = t;
        head = t;
    }
    else
    {
        head->tail->next = t;
        head->tail = t;
    }
    *queue = head;
}
int isQueueEmpty(Node * queue)
{
    if(queue == NULL)
        return 1;
    else return 0;
}
void print(Node * Q)
{
    Node * q = Q;
    printf("\n");
    while(q)
    {
        printf("%d ",q->data);
        q=q->next;
    }
}
int main()
{
    Node * Queue = NULL;
    int i;
    for(i=1;i<31;i++)
    {
        pushToQ(&Queue,i);
        print(Queue);
    }
    for(i = 1;i<31;i++)
    {
        popQ(&Queue);
        print(Queue);
    }
}
