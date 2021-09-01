#include<iostream>

using namespace std;

struct AVL{
    int data,height;
    AVL *left, *right;
    AVL(int x){
        this->data=x;
        this->left=nullptr;
        this->right=nullptr;
        this->height=0;
    }
};

int height( AVL *t )
{
    return t == nullptr ? -1 : t->height;
}

AVL* findMin(AVL *node)
{
    while(node->left!=nullptr)
    {
        node=node->left;
    }

    return node;
}

void rotateWithLeft(AVL *&node)
{
    AVL *t=node->left;

    node->left=t->right;

    t->right=node;

    node->height=max(height(node->left),height(node->right))+1;
    t->height=max(height(t->left),node->height)+1;
    
    node=t;
    
    return;
}

void rotateWithRight(AVL *&node)
{
    AVL *t=node->right;

    node->right=t->left;

    t->left=node;

    node->height=max(height(node->left),height(node->right))+1;
    t->height=max(height(t->right),node->height)+1;

    node=t;

    return;
}

void doubleWithLeft(AVL *&node)
{
    rotateWithRight(node->left);
    rotateWithLeft(node);

    return;
}

void doubleWithRight(AVL *&node)
{
    rotateWithLeft(node->right);
    rotateWithRight(node);

    return;
}

void balance(AVL *&node)
{
    if(node==nullptr)
    {
        return;
    }

    if(height(node->left)-height(node->right)>1)
    {
        if(height(node->left->left)>=height(node->left->right))
        {
            rotateWithLeft(node);
        }
        else
        {
            doubleWithLeft(node);
        }
    }

    else if(height(node->right)-height(node->left)>1)
    {
        if(height(node->right->right)>=height(node->right->left))
        {
            rotateWithRight(node);
        }
        else
        {
            doubleWithRight(node);
        }
    }

    node->height=max(height(node->left),height(node->right))+1;

    return;
}

void insert(int x, AVL *&node)
{
    if(node==nullptr)
    {
        node=new AVL(x);
    }
    
    else if(node->data<x)
    {
        insert(x,node->right);
    }
    
    else 
    {
        insert(x,node->left);
    }
    
    balance(node);
    
    return;
}

void remove(AVL *&node, int x)
{
    if(node==nullptr)
    {
        return;
    }

    if(x<node->data)
    {
        remove(node->left,x);
    }
    
    else if(x>node->data)
    {
        remove(node->right,x);
    }
    
    else if(node->left!=nullptr&&node->right!=nullptr)
    {
        node->data=findMin(node->right)->data;
        remove(node->right,node->data);
    }

    else
    {
        AVL* t=node;
        node=(node->left!=nullptr)?node->left:node->right;
        delete t;
    }

    balance(node);

    return;
}

void printInorder(AVL* node)
{
    if (node == NULL)
    {
        return;     
    }

    printInorder(node->left);
    
    cout<<node->data<<" ";
    
    printInorder(node->right);

    return;
}

int maxheightdiff(AVL *node)
{
    if(node==nullptr)
    {
        return 0;
    }
    
    int h=abs(height(node->left)-height(node->right));
    h=max(h,maxheightdiff(node->left));
    h=max(h,maxheightdiff(node->right));

    return h;
}

int main()
{
    AVL* root = nullptr;
    insert(4,root);
    insert(6,root);
    insert(5,root);
    insert(2,root);
    insert(1,root);
    insert(3,root);
    
    cout<<"Inorder: \n";
    printInorder(root);

    cout<<"\nMax height diff: "<<maxheightdiff(root)<<"\n";

    remove(root, 5);
    remove(root ,2);

    cout<<"\nInorder: \n";
    printInorder(root);

    cout<<"\nMax height diff: "<<maxheightdiff(root)<<"\n";
}