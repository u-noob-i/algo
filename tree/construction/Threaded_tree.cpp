#include<iostream>

using namespace std;

struct Threaded{
    int data;
    bool rightThread,leftThread;
    Threaded *left, *right;
    Threaded(int x){
        this->data=x;
        this->left=nullptr;
        this->right=nullptr;
        this->rightThread=this->leftThread=1;
    }
};
void insert(int x, Threaded *&root)
{

    Threaded *temp = new Threaded(x);

    if (root == nullptr) {

        root=temp;
        root->right=nullptr;
        root->left=nullptr;
        return;
    }
 
    Threaded *cur = root;
    while (1) {

        if (cur->data < x) {
            
            if (cur->rightThread == 1) {
                temp->right = cur->right;
                temp->rightThread = cur->rightThread;
                temp->leftThread = 1;
                temp->left = cur;
 
                cur->rightThread = 0;
                cur->right = temp;
                return;
            }
            
            else
            {
                cur = cur->right;
            }
        }
 
        if (cur->data > x) {

            if (cur->leftThread == 1) {
                temp->left = cur->left;
                temp->leftThread = cur->leftThread;
                temp->rightThread = 1;
 
                temp->right = cur;
                cur->leftThread = 0;
                cur->left = temp;
                return;
            }
            else
            {
                cur = cur->left;
            }
        }
    }
    return;
}

void remove(Threaded *node, int x)
{
    if(node==nullptr)
    {
        return;
    }
    
    return;
}

Threaded* getInorderSuccesor(Threaded *cur)
{
    if(cur->rightThread==1)
    {
        cur=cur->right;
        return cur;
    }

    cur=cur->right;

    while(cur->leftThread==0)
    {
        cur=cur->left;
    }
    return cur;
}

Threaded* getPreorderSuccesor(Threaded *cur)
{
    if(cur->leftThread==0)
    {
        return cur->left;
    }
    while(cur->rightThread==1)
    {
        cur=cur->right;
    }
    return cur->right;
}

void printInorder(Threaded* node)
{
    if (node == nullptr)
    {
        return;     
    }

    Threaded *cur=node;

    while(cur->leftThread==0)
    {
        cur=cur->left;
    }

    while(cur!=nullptr)
    {
        cout<<cur->data<<" ";
        cur=getInorderSuccesor(cur);
    }

    return;
}

void printPreorder(Threaded *node)
{
    if(node==nullptr)
    {
        return;
    }

    Threaded *cur=node;

    while(cur!=nullptr)
    {
        cout<<cur->data<<" ";
        cur=getPreorderSuccesor(cur);
    }

}

int main()
{
    Threaded* root = nullptr;
    insert(4,root);
    insert(6,root);
    insert(5,root);
    insert(2,root);
    insert(1,root);
    insert(3,root);

    cout<<"Inorder: \n";
    printInorder(root);

    remove(root, 5);
    remove(root ,2);

    cout<<"\nPreorder: \n";
    printPreorder(root);

}