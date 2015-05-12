#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int num_of_words = 0;
int expo(int a, int pow)
{
    if(pow<1)
        return 1;
    return a * expo(a,pow-1);
}
void mergeSort(int arr[],int low,int mid,int high){

    int i,m,k,l;
    int *temp = malloc(num_of_words * sizeof(int));


    l=low;
    i=low;
    m=mid+1;

    while((l<=mid)&&(m<=high)){

        if(arr[l]<=arr[m]){
            temp[i]=arr[l];
            l++;
        }
        else{
            temp[i]=arr[m];
            m++;
        }
        i++;
    }

    if(l>mid){
        for(k=m;k<=high;k++){
            temp[i]=arr[k];
            i++;
        }
    }
    else{
        for(k=l;k<=mid;k++){
            temp[i]=arr[k];
            i++;
        }
    }

    for(k=low;k<=high;k++){
        arr[k]=temp[k];
    }
    free(temp);
}
void partition(int arr[],int low,int high){

    int mid;

    if(low<high){
        mid=(low+high)/2;
        partition(arr,low,mid);
        partition(arr,mid+1,high);
        mergeSort(arr,low,mid,high);
    }
}

int main()
{
    int i,max,maxi,ans=0,j,counti,countans;
    int ar[26]={2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
    scanf("%d",&num_of_words);
    int *keySequence = malloc(num_of_words * sizeof(int));
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
            aWordInt += ar[a -97] * expo(10,wordLen - 1 - j);
            j++;
            a = *(aWord + j);
        }
        keySequence[i]=aWordInt;
    }
    //sequence found now sort ...
    partition(keySequence,0,num_of_words-1);
    ans=keySequence[0];
    countans=1;
    counti=1;
    for(i=1;i<num_of_words;i++)
    {
        if(keySequence[i] == keySequence[i-1] )
        {
            counti++;
            if(counti > countans)
            {
                ans=keySequence[i];
                countans = counti;
            }
        }
        else
        {
            counti = 1;
        }
    }
    printf("%d\n",ans);
    free(keySequence);
}
