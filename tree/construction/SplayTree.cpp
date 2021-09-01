#include<iostream>

using namespace std;

struct Splay{
    int data,height;
    Splay *left, *right;
    Splay(int x){
        this->data=x;
        this->left=nullptr;
        this->right=nullptr;
        this->height=0;
    }
};

Splay* findMin(Splay *node)
{
    while(node->left!=nullptr)
    {
        node=node->left;
    }

    return node;
}

void rotateWithLeft(Splay *&node)
{
    Splay *t=node->left;

    node->left=t->right;

    t->right=node;
    
    node=t;
    
    return;
}

void rotateWithRight(Splay *&node)
{
    Splay *t=node->right;

    node->right=t->left;

    t->left=node;

    node=t;

    return;
}

void doubleWithLeft(Splay *&node)
{
    rotateWithRight(node->left);
    rotateWithLeft(node);

    return;
}

void doubleWithRight(Splay *&node)
{
    rotateWithLeft(node->right);
    rotateWithRight(node);

    return;
}



void insert(int x, Splay *&node)
{
    if(node==nullptr)
    {
        node=new Splay(x);
    }
    
    else if(node->data<x)
    {
        insert(x,node->right);
    }
    
    else 
    {
        insert(x,node->left);
    }  
    
    return;
}

void remove(Splay *&node, int x)
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
        Splay* t=node;
        node=(node->left!=nullptr)?node->left:node->right;
        delete t;
    }

    return;
}

void printInorder(Splay* node)
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

int main()
{
    Splay* root = nullptr;
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

    cout<<"\nInorder: \n";
    printInorder(root);

}