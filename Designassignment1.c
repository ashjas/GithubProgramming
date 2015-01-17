#include<stdio.h>
int main()
{
    int num_of_words=0,i;
    int ar[26]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
    char aWord[50];
        int j=0;
    scanf("%d",&num_of_words);
    //int *keySequence = malloc(sizeof(int) * num_of_words);
    int *keySequence[num_of_words];
    for (i=0;i<num_of_words;i++)
    {
        char * seqStr=NULL;
        int * seqInt=NULL;
        scanf("%s",aWord);
        //seqStr = malloc(sizeof(char) * strlen(aWord) + 1);
        seqInt = malloc(sizeof(int) * strlen(aWord) + 1);
        char a=*aWord;
        while(a != '\0')
        {
            seqInt[j++] = ar[a - 97];
            a = *(aWord + j);
        }
        //for(i=0;i<strlen(aWord);i++)
          //  printf("%d",seqInt[i]);
        keySequence[i]=seqInt;
        //keySequence[i] = atoi(seqStr);
    }
        for(i=0;i<num_of_words;i++)
        {
            for(j=0;j<4;j++)
            {
                int * abc = keySequence[i];
                printf("%d",abc[j]);
            }
            printf("\n");
        }

}
