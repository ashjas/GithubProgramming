#include<stdio.h>
int exp(int a, int pow)
{
    if(pow<1)
        return 1;
    return a * exp(a,pow-1);
}
int main()
{
    int num_of_words=0,i;
    int ar[26]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
    scanf("%d",&num_of_words);
    int *keySequence[num_of_words];
    for (i=0;i<num_of_words;i++)
    {
        int j=0;
        char aWord[50];
        scanf("%s",aWord);
        int wordLen= strlen(aWord);
        char a=*aWord;
        int aWordInt=0;
        while(a != '\0')
        {
            aWordInt += ar[a -97] * exp(10,wordLen - 1 - j);
            j++;
            a = *(aWord + j);
        }
        keySequence[i]=aWordInt;
    }
    for(i=0;i<num_of_words;i++)
    {
        printf("\n%d",keySequence[i]);
    }

}
