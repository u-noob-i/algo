#include<iostream>
using namespace std;

int partition(int arr[],int l,int r)
{
    int key=arr[r];
    int j=l-1,i=l;
    while(i<r)
    {
        if(arr[i]<key)
        {
            j++;
            swap(arr[i],arr[j]);
        }
        i++;
    }
    swap(arr[j+1],arr[r]);
    return j+1;
}

void quicksort(int arr[],int l,int r)
{
    if(l<r)
    {
        int i=partition(arr,l,r);
        quicksort(arr,l,i-1);
        quicksort(arr,i+1,r);
    }
}

int main()
{
    int arr[]={5,1,1,2,3};
    quicksort(arr,0,4);
    for(int i=0;i<5;i++)
    {
        cout<<arr[i];
    }
}