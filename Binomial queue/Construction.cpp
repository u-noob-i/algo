#include<iostream>
#include<vector>
#include<math.h>
#include<cmath>

using namespace std;

class BinomialQueue{
    private:

    struct Node{
        int data;
        Node *child;
        Node *sibling;

        Node(int x, Node *c = nullptr, Node *s = nullptr): data{x}, child{c}, sibling{s} {}
    };

    
    int cursize;
    vector<Node*> Trees;

    public:

    BinomialQueue()
    {
        cursize=0;
    }

    bool isEmpty()
    {
        return cursize==0;
    }

    int capacity()
    {
        return pow(2,Trees.size()) - 1;
    }

    int getMinIndex()
    {
        int i=0;
        for(;i<Trees.size() && Trees[i]==nullptr;i++);
        
        int mini=i;
        for(;i<Trees.size();i++)
        {
            if(Trees[i]!=nullptr&&Trees[i]->data<Trees[mini]->data)
            {
                mini = i;
            }
        }

        return mini;
    }
    
    Node* combineTrees(Node *t1, Node *t2)
    {
        if(t1->data>t2->data)
        {
            return combineTrees(t2, t1);
        }

        t2->sibling=t1->child;
        t1->child=t2;
        return t1;
    }

    void merge(BinomialQueue *&rhs)
    {
        if(this==rhs)
        {
            return;
        }

        cursize+=rhs->cursize;

        if(cursize>capacity())
        {
            size_t oldsize=Trees.size();
            size_t newsize=max(oldsize,rhs->Trees.size())+1;
            Trees.resize(newsize);

            for(size_t i=oldsize;i<newsize;i++)
            {
                Trees[i]=nullptr;
            }
        }

        Node *carry = nullptr;
        for(int i=0,j=1;j<=cursize;i++,j*=2)
        {
            Node *t1=Trees[i];
            Node *t2=i<rhs->Trees.size()?rhs->Trees[i]:nullptr;

            int check = t1==nullptr? 0: 1;
            check += t2==nullptr? 0: 2;
            check += carry==nullptr? 0: 4;

            switch(check)
            {
                case 0: break;
                case 1: break;
                
                case 2: Trees[i] = t2;
                    rhs->Trees[i] = nullptr;
                    break;

                case 3: carry = combineTrees(t1 ,t2);
                    Trees[i] = rhs->Trees[i] = nullptr;
                    break;
                
                case 4: Trees[i] = carry;
                    carry = nullptr;
                    break;

                case 5: carry = combineTrees(carry, t1);
                    Trees[i] = nullptr;
                    break;

                case 6: carry = combineTrees(carry, t2);
                    rhs->Trees[i] = nullptr;
                    break;

                case 7: Trees[i] = carry;
                    carry = combineTrees(t1, t2);
                    rhs->Trees[i] = nullptr;
                    break;              
            }
        }

        for(int i=0;i<rhs->Trees.size();i++)
        {
            rhs->Trees[i]=nullptr;
        }
        rhs->cursize=0;
            
        return;
    }

    void insert(int x)
    {
        if(isEmpty())
        {       
            Node *temp = new Node(x);

            cursize++;
            Trees.resize(1);
            Trees[0] = temp;
            return;
        }

        BinomialQueue *q = new BinomialQueue();
        q->insert(x);

        this->merge(q);
        delete(q);

        return;

    }

    int deleteMin()
    {
        if(isEmpty())
        {
            return -1;
        }

        int mini = getMinIndex();
        int ret = Trees[mini]->data;
        Node *deleted = Trees[mini]->child;
        Trees[mini] = nullptr;

        BinomialQueue *q = new BinomialQueue();
        q->Trees.resize(mini+1);
        q->cursize=(1<<mini)-1;
        for(int j=mini-1;j>=0;j--)
        {
            q->Trees[j]=deleted;
            deleted=deleted->sibling;
            q->Trees[j]->sibling=nullptr;
        }

        merge(q);   
        delete(q);

        return ret;
    }
};

int main()
{
    BinomialQueue *q = new BinomialQueue();
    q->insert(6);
    q->insert(1);
    q->insert(69);
    q->insert(4);

    for(int i=0;i<4;i++)
    {
        cout<<q->deleteMin()<<" ";
    }
}

