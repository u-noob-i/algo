#include<iostream>
#include<stack>

using namespace std;

struct Node{
    int data;
    Node *left, *right;
    Node(int x){
        this->data=x;
        this->left=nullptr;
        this->right=nullptr;
    }
};

void insert(Node *&root,int x)
{
    if(root==nullptr)
    {
        root=new Node(x);
        return;
    }
    if(root->data==x)
    {
        return;
    }
    if(x<root->data)
    {
        insert(root->left,x);
        return;
    }
    insert(root->right,x);
    return;
}

Node* findMin(Node *root)
{
    while(root->left!=nullptr)
    {
        root=root->left;
    }
    return root;
}

void remove(Node *&root,int x)
{
    if(root==nullptr)
    {
        return;
    }
    if(x<root->data)
    {
        return remove(root->left,x);
    }
    if(x>root->data)
    {
        return remove(root->right,x);
    }
    if(root->right==nullptr||root->left==nullptr)
    {
        Node *temp=root;
        root=(root->left==nullptr?root->right:root->left);
        delete temp;
        return;
    }
    root->data=findMin(root->right)->data;
    remove(root->right,root->data);
    return;
}

void Inorder(Node *node)
{
    if (node == nullptr)
    {
        return;     
    }

    Inorder(node->left);
    cout<<node->data<<" ";
    Inorder(node->right);

}

void Postorder(Node *root)
{
    if(root==nullptr){
        return;
    }
    Postorder(root->left);
    Postorder(root->right);
    cout<<root->data<<" ";
    return;
}

int main()
{
    struct Node *root = nullptr;
    
    insert(root,4);
    insert(root,2);
    insert(root,3);
    insert(root,5);
    insert(root,6);
    insert(root,1);

    cout << "Inorder: \n";
    Inorder(root);
    
    remove(root,6);
    remove(root,4);

    cout<<"\nInorder: \n";
    Inorder(root);
}