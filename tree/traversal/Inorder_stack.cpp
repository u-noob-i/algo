#include<iostream>
#include<stack>

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
    stack<Node *> s;
    Node *cur = root;
    while(cur!=NULL||!s.empty())
    {
        while(cur!=NULL)
        {
            s.push(cur);
            cur=cur->left;
        }
        cur=s.top();
        s.pop();
        cout<<cur->data<<" ";
        cur=cur->right;
    }
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

}