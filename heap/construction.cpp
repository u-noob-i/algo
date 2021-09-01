#include<iostream>
#include<vector>

using namespace std;

class BinaryHeap{
    private:

    vector<int> array;
    unsigned int cursize;

    public:

    bool isEmpty() const
    {
        return !cursize;
    }

    void percolateDown(int hole)
    {
        int child;
        int temp=array[hole];

        for(;hole*2<=cursize;hole=child)
        {
            child=hole*2;
            if(child!=cursize&&array[child+1]<array[child])
            {
                ++child;
            }
            if(array[child]<temp)
            {
                array[hole]=array[child];
            }
            else
            {
                break;
            }
        }
        array[hole]=temp;
        
        return;
    }

    void percolateUp(int hole)
    {
        int copy;
        array[0]=copy=array[hole];
        for(;copy<array[hole/2];hole/=2)
        {
            array[hole]=array[hole/2];
        }
        array[hole]=copy;
    }

    void buildheap()
    {
        for(int i=cursize/2;i>0;i--)
        {
            percolateDown(i);
        }
    }

    explicit BinaryHeap()
    {
        array.resize(sizeof(int)*100);
        cursize=0;
    }

    explicit BinaryHeap(vector<int> &arr) :array(arr.size()*2),cursize{arr.size()}
    {
        for(int i=0;i<arr.size();i++)
        {
            array[i+1]=arr[i];
        }

        buildheap();
    }

    void insert(int x)
    {
        if(cursize==array.size()-1)
        {
            array.resize(array.size()*2);
        }

        int hole=++cursize;

        array[hole]=x;

        percolateUp(hole);
        return;
    }

    int deleteMin()
    {
        if(isEmpty())
        {
            return -1;
        }

        int x=array[1];

        array[1]=array[cursize--];
        percolateDown(1);

        return x;
    }

    void decreaseKey(int i, int d)
    {
        if(i>cursize)
        {
            return;
        }
        
        array[i]-=d;
        percolateUp(i);
        
        return;
    }

    void print()
    {
        for(int i=1;i<=cursize;i++)
        {
            cout<<array[i]<<" ";
        }
        cout<<"\n";
    }
};

int main()
{
    vector<int> arr={6,9,2,4,1,5};
    BinaryHeap *heap=new BinaryHeap(arr);

    for(int i=0;i<6;i++)
    {
        cout<<heap->deleteMin()<<" ";
    }
}