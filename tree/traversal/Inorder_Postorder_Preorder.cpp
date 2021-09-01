#include<iostream>

using namespace std;

struct Node{
    int data;
    Node *left, *right;
    Node(int x){
        this->data=x;
        this->left=NULL;
        this->right=NULL;
    }
};

void Inorder(Node *root)
{
    if(root==NULL){
        return;
    }
    Inorder(root->left);
    cout<<root->data<<" ";
    Inorder(root->right);
    return;
}

void Preorder(Node *root)
{
    if(root==NULL){
        return;
    }
    cout<<root->data<<" ";
    Preorder(root->left);
    Preorder(root->right);
    return;
}

void Postorder(Node *root)
{
    if(root==NULL){
        return;
    }
    Postorder(root->left);
    Postorder(root->right);
    cout<<root->data<<" ";
    return;
}

int main()
{
    struct Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout<<"Inorder: ";
    Inorder(root);

    cout<<"\nPostorder: ";
    Postorder(root);

    cout<<"\nPreorder: ";
    Preorder(root);
}