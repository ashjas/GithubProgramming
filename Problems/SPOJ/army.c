#include<stdio.h>
#include<stdlib.h>
void mergeSort(int arr[],int low,int mid,int high,int len){

    int i,m,k,l;
    int *temp = malloc(len * sizeof(int));


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
void partition(int arr[],int low,int high,int len){

    int mid;

    if(low<high){
        mid=(low+high)/2;
        partition(arr,low,mid,len);
        partition(arr,mid+1,high,len);
        mergeSort(arr,low,mid,high,len);
    }
}
int max(int a,int b)
{
    return a>b?a:b;
}
int main()
{
    int i,j,k,l,T,NG=0,NM=0,dG=0,dM=0;
    int * Garray = NULL;
    int * Marray = NULL;
    //freopen("in","r",stdin);
    scanf("%d",&T);
    for (i=0;i<T;i++)
    {
        scanf("%d %d",&NG,&NM);
        int nMax=-1,mMax=-1;
        Garray = malloc(sizeof(int) * NG);
        Marray = malloc(sizeof(int) * NM);
        for(j=0;j<NG;j++)
            scanf("%d",&Garray[j]);
        for(j=0;j<NM;j++)
            scanf("%d",&Marray[j]);
        partition(Garray,0,NG-1,NG);
        partition(Marray,0,NM-1,NM);
        //printf("\n");
        for(j=0;j<NG;j++)
        {
            //printf("%d",Garray[j]);
            if(Garray[j] > nMax)
                nMax = Garray[j];
        }
        //printf("\n");
        for(j=0;j<NM;j++)
        {
            //printf("%d",Marray[j]);
            if(Marray[j] > mMax)
                mMax = Marray[j];
        }
        if(nMax==mMax)
                printf("Godzilla\n");
        else if(nMax>mMax)
                printf("Godzilla\n");
        else
                printf("MechaGodzilla\n");

        /*
        for(k=0,l=0;;)
        {
            if(Garray[k] >= Marray[l])
            {
                Marray[l] = -1;
                l++;dM++;
            }
            else if(Garray[k] < Marray[l])
            {
                Garray[k] = -1;
                k++;dG++;
            }
            if(dM >= NM )
            {
                printf("Godzilla\n");
                break;
            }
            if(dG >= NG )
            {
                printf("MechaGodzilla\n");
                break;
            }
        }*/
    }

}
