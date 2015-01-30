#include<stdio.h>
#include<stdlib.h>
typedef struct term
{
    int e;
    int c;
    struct term* next;
    struct term* prev;
}term;


term * insertNode(term *HEAD,int e, int c)
{
    if(HEAD == NULL)
    {
        //printf("\n FIRST adding e:%d,c:%d",e,c);
        term * node = malloc(sizeof(term));
        node->e = e;
        node->c = c;
        node->next = NULL;
        node->prev = NULL;
        HEAD = node;
        //printf("HEAD:%p",HEAD);
        return HEAD;
    }
    else/*list already initialized.. find a place to insert.*/
    {
        term * node = HEAD;
        while(node)/*traverse and find place for insertion in descending order.*/
        {
            if(node->e <= e)/*found create and insert the new term here.*/
            {
                //printf("\n adding e:%d,c:%d",e,c);
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
                return HEAD;/*inserted at correct place, now no need to traverse rest of the list.*/
            }
            if(node->next == NULL)
            {
                //printf("\n adding to last e:%d,c:%d",e,c);
                term * newTerm = malloc(sizeof(term));
                newTerm->e = e;
                newTerm->c = c;
                newTerm->next = NULL;
                newTerm->prev = node;
                node->next = newTerm;
                return HEAD;/* added last so this end of list now.*/
            }
            node=node->next;
        }
    }
}
term * Multiply(term *first, term *second)
{
    term *iter1 = first, *iter2 = second, *answer = NULL, *answerFinal = NULL;
    while(iter1 )
    {
        int c,e;
        while(iter2)
        {
            c = iter1->c * iter2->c;
            e = iter1->e + iter2->e;
            answer = insertNode(answer,e,c);
            iter2 = iter2->next;
        }
        iter2 = second;
        iter1 = iter1->next;
    }
/*arrange answer terms now.*/
    iter1 = answer;
    int C=answer->c,E=answer->e;
    iter1=iter1->next;
    while(iter1)
    {
        if(iter1->e == E)
        {
            C+=iter1->c;
        }
        else
        {
            answerFinal = insertNode(answerFinal,E,C);
            C=iter1->c;
            E=iter1->e;
        }
        iter1 = iter1->next;
    }
    answerFinal = insertNode(answerFinal,E,C);
    iter1=answer;
    /*free temp answer*/
while(iter1)
{
    term * node = iter1;
    iter1 = iter1->next;
    free(node);
} 
return answerFinal;
}

void freeAll(term * one,term * two,term * three)
{
    term * iter1=one;
    while(iter1)
    {
        term * node = iter1;
        iter1 = iter1->next;
        free(node);
    }
    iter1=two;
    while(iter1)
    {
        term * node = iter1;
        iter1 = iter1->next;
        free(node);
    }
    iter1=three;
    while(iter1)
    {
        term * node = iter1;
        iter1 = iter1->next;
        free(node);
    }
}

int main()
{
    int i,j,k;
    int nMcnd,nMler;
    term * iter =NULL;
    term * Multiplicand = NULL, *Multiplier = NULL, *Answer = NULL;
    scanf("%d",&nMcnd);
    for(i=0;i<nMcnd;i++)
    {
        int c,e;
        scanf("%d%d",&c,&e);
        Multiplicand = insertNode(Multiplicand,e,c);
    }
    scanf("%d",&nMler);
    for(i=0;i<nMler;i++)
    {
        int c,e;
        scanf("%d%d",&c,&e);
        Multiplier = insertNode(Multiplier,e,c);
    }
    Answer = Multiply(Multiplicand,Multiplier);
    iter=Answer;
    if(iter->c != 0)
    {
        if( iter->e > 1 && iter->c != 1 )
            printf("%dx^%d",iter->c,iter->e);
        else if (iter->e > 1 && iter->c == 1)
            printf("x^%d",iter->e);
        else if (iter->e == 1 && iter->c == 1)
            printf("x");
        else if (iter->e == 1 && iter->c != 1)
            printf("%dx",iter->c);
        if( iter->e == 0)
            printf("%d",iter->c);
    }
    iter=iter->next;
    while(iter)
    {
        if(iter->c != 0)
        {
            if( iter->e > 1 && iter->c != 1 )
                printf("%+dx^%d",iter->c,iter->e);
            else if (iter->e > 1 && iter->c == 1)
                printf("x^%d",iter->e);
            else if (iter->e == 1 && iter->c == 1)
                printf("x");
            else if (iter->e == 1 && iter->c != 1)
                printf("%+dx",iter->c);
            if( iter->e == 0)
                printf("%+d",iter->c);
        }
        else if (iter->next == NULL)
        {
            printf("0");
        }
        iter=iter->next;
    }
    freeAll(Multiplicand,Multiplier,Answer);
    return 0;
}
