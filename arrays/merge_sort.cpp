#include<iostream>
using namespace std;

void merge(int arr[],int l,int m,int r)
{
    int n1=m-l+1;
    int n2=r-m;
    int* a=new int[n1];
    int* b=new int[n2];
    for(int i=0;i<n1;i++)
    {
        a[i]=arr[l+i];
    }
    for(int i=0;i<n2;i++)
    {
        b[i]=arr[m+1+i];
    }
    int i=0,j=0,k=l;
    while(i<n1&&j<n2)
    {
        if(a[i]<=b[j])
        {
            arr[k]=a[i];
            i++;
            k++;
        }
        else
        {
            arr[k]=b[j];
            k++;
            j++;
        }
    }
    while(i<n1)
    {
        arr[k]=a[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        arr[k]=b[j];
        j++;
        k++;
    }
    return;
}

void mergesort(int arr[],int l,int r)
{
    if(l>=r)
    {
        return;
    }
    int m=(l+r)/2;
    mergesort(arr,l,m);
    mergesort(arr,m+1,r);
    merge(arr,l,m,r);
    return;
}

int main()
{
    int arr[]={5,1,1,2,3};
    mergesort(arr,0,4);
    for(int i=0;i<5;i++)
    {
        cout<<arr[i];
    }
}