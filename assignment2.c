#include<stdio.h>
#include<stdlib.h>
typedef struct term
{
    int e;
    int c;
    struct term* next;
    struct term* prev;
}term;

//term * HEAD = NULL;

term * insertNode(term *HEAD,int e, int c)
{
    //term * HEAD = LIST_HEAD;
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
//return answer;
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

return answerFinal;
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
       // printf("Multiplicand:%p",Multiplicand);
    }
    scanf("%d",&nMler);
    for(i=0;i<nMler;i++)
    {
        int c,e;
        scanf("%d%d",&c,&e);
        Multiplier = insertNode(Multiplier,e,c);
        //printf("Multiplier:%p",Multiplier);
    }
    Answer = Multiply(Multiplicand,Multiplier);
    iter=Answer;
//    printf("\n");
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
    /*test*/
    /*
    printf("\nMultiplicand:%p,Multiplier:%p\n",Multiplicand,Multiplier);
    printf("\nMultiplicand:\n");
    iter=Multiplicand;
    while(iter)
    {
        printf("\ne:%d,c:%d",iter->e,iter->c);
        iter=iter->next;
        printf("\nNode:%p",iter);
    }
    printf("\nMultiplier:\n");
    iter = Multiplier;
    while(iter)
    {
        printf("\ne:%d,c:%d",iter->e,iter->c);
        iter=iter->next;
        printf("\nNode:%p",iter);
    }*/
/*    for(i=0;i<300;i++ )
    {
        int e,c;
        e = rand() % 1000;c = rand() % 200;

        insertNode(e, c);
    }
    term* Node = HEAD;
    while(Node)
    {
        printf("\ne:%d,c:%d",Node->e,Node->c);
        Node=Node->next;
        printf("\nNode:%p",Node);
    }
    */
}
