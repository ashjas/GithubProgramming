#include<stdio.h>
#include<stdlib.h>
typedef struct term
{
    int e;
    int c;
    struct term* next;
    struct term* prev;
}term;

term * HEAD = NULL;

void insertNode(int e, int c)
{
    if(HEAD == NULL)
    {
        printf("\n FIRST adding e:%d,c:%d",e,c);
        term * node = malloc(sizeof(term));
        node->e = e;
        node->c = c;
        node->next = NULL;
        node->prev = NULL;
        HEAD = node;
        return;
    }
    else/*list already initialized.. find a place to insert.*/
    {
        term * node = HEAD;
        while(node)/*traverse and find place for insertion in descending order.*/
        {
            if(node->e < e)/*found create and insert the new term here.*/
            {
                printf("\n adding e:%d,c:%d",e,c);
                term * newTerm = malloc(sizeof(term));
                newTerm->e = e;
                newTerm->c = c;
                newTerm->next = node;
                newTerm->prev = node->prev;
                if(node != HEAD)
                    newTerm->prev->next = newTerm;
                node->prev = newTerm;
                if(node == HEAD)/*this means we added at the start of the list, so update HEAD*/
                    HEAD=newTerm;
                break;/*inserted at correct place, now no need to traverse rest of the list.*/
            }
            if(node->next == NULL)
            {
                printf("\n adding to last e:%d,c:%d",e,c);
                term * newTerm = malloc(sizeof(term));
                newTerm->e = e;
                newTerm->c = c;
                newTerm->next = NULL;
                newTerm->prev = node;
                //newTerm->prev->next = newTerm;
            }
            node=node->next;
        }
    }
}

int main()
{
    int i,j,k;
    for(i=0;i<10;i++ )
    {
        int e,c;
        e = rand() % 10;c = rand() % 20;

        insertNode(e, c);
    }
    term* Node = HEAD;
    while(Node)
    {
        printf("\nc:%d,e:%d",Node->c,Node->e);
        Node=Node->next;
        printf("\nNode:%p",Node);
    }
}
