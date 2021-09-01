#include<iostream>
using namespace std;

void sieveoferatosthenes()
{
    int k ;
    cin >> k;
    bool* prime = new bool[k + 1];
    for (int i = 0; i <= 1000000; i++)
        prime[i] = true;

    for (int p = 2; p <= k; p++)
    {
        if (prime[p] == true)
        {
            for (int i = 2; i * p <= k; i++)
                prime[i * p] = false;
        }
    }
}

int main()
{
    int arr[]={5,1,1,2,3};
    sieveoferatosthenes();
}