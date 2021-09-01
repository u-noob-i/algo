#include<iostream>

using namespace std;

class LeftistHeap{
    private:

    struct LeftistNode{
        int data;
        LeftistNode *left;
        LeftistNode *right;
        int npl;

        LeftistNode(const int &x, LeftistNode *lt=nullptr, LeftistNode *rt=nullptr, int np=0) : data(x), left(lt), right(rt), npl(np) {}

    };
    
    LeftistNode *root=nullptr;

    public: 

    void swapChildren(LeftistNode *&h1)
    {
        LeftistNode *temp=h1->left;
        h1->left=h1->right;
        h1->right=temp;

        return;
    }

    bool isEmpty()
    {
        return root==nullptr;
    }

    LeftistNode* merge1(LeftistNode *h1, LeftistNode *h2)
    {
        if(h1->left==nullptr)
        {
            h1->left=h2;
        }
        else
        {
            h1->right=merge(h1->right,h2);
            if(h1->left->npl<h1->right->npl)
            {
                swapChildren(h1);
                h1->npl=h1->right->npl+1;
            }
        }

        return h1;
    }

    void merge(LeftistHeap  &rhs)
    {
        if(this==&rhs)
        {
            return;
        }
        root=merge(root,rhs.root);
        rhs.root=nullptr;
        return;
    }

    LeftistNode* merge(LeftistNode *h1, LeftistNode *h2)
    {
        if(h1==nullptr)
        {
            return h2;
        }
        if(h2==nullptr)
        {
            return h1;
        }
        if(h1->data<h2->data)
        {
            return merge1(h1,h2);
        }
        return merge1(h2,h1);
    }

    void insert(int x)
    {
        root=merge(new LeftistNode(x),root);
        return;
    }

    int deleteMin()
    {
        if(isEmpty())
        {
            return -1;
        }

        LeftistNode *temp=root;root=merge(root->left,root->right);
        int x=temp->data;
        delete temp;
        
        return x;
    }

};

int main()
{
    LeftistHeap *heap=new LeftistHeap();
    heap->insert(5);
    heap->insert(2);
    heap->insert(3);
    heap->insert(1);
    heap->insert(9);
    heap->insert(21);

    cout<<heap->deleteMin()<<" ";
    cout<<heap->deleteMin()<<" ";
    cout<<heap->deleteMin()<<" ";
    cout<<heap->deleteMin()<<" ";
    cout<<heap->deleteMin()<<" ";
    cout<<heap->deleteMin()<<" ";
    cout<<heap->deleteMin()<<" ";

    return 0;
}