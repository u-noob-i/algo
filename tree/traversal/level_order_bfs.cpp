#include<iostream>
#include<queue>

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

void BFS(Node *root)
{
    queue<Node *> q;
    Node *cur = root;
    q.push(cur);
    while(!q.empty())
    {
        cur=q.front();
        q.pop();
        cout<<cur->data<<" ";

        if(cur->left!=nullptr)
        {
            q.push(cur->left);
        }

        if(cur->right!=nullptr)
        {
            q.push(cur->right);
        }

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
    BFS(root);

}