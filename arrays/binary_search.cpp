#include<iostream>
using namespace std;

int binarysearch(int arr[], int l, int r, long long x)
{

    if (l > r)
        return -1;
    int mid = (l + r) / 2;
    if (arr[mid] == x)
        return mid;
    if (arr[mid] < x)
    {
        return binarysearch(arr, mid + 1, r, x);
    }
    if (arr[mid] > x)
    {
        return binarysearch(arr, l, mid - 1, x);
    }
    return -1;
}

int main()
{
    int arr[]={5,1,1,2,3};
    cout<<binarysearch(arr,0,4,2);
}