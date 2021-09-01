#include<iostream>
#include<stack>

using namespace std;

struct Node{
    char data;
    Node *left, *right;
    Node(int x){
        this->data=x;
        this->left=NULL;
        this->right=NULL;
    }
};

int search(char ch, char in[], int start, int end)
{
    for(int i=start;i<=end;i++)
    {
        if(in[i]==ch)
        {
            return i;
        }
    }
    return 0;
}

Node* construct(Node *root, char in[], char pre[], int start, int end)
{
    static int preind = 0;

    if(start > end)
    {
        return NULL;
    }

    Node *newnode = new Node(pre[preind++]);
     
    if(start==end)
    {
        return newnode;
    }
    
    int ind = search(newnode->data, in, start, end);

    newnode->left = construct(newnode, in, pre, start, ind - 1);
    newnode->right = construct(newnode, in ,pre, ind + 1, end);

    return newnode;
}

void printInorder(Node* node)
{
    if (node == NULL)
    {
        return;     
    }

    printInorder(node->left);
    cout<<node->data<<" ";
    printInorder(node->right);

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
    struct Node* root = NULL;
    char in[] = { 'l', 'j', 'm', 'i', 'n', 'k' , 'o'};
    char pre[] = { 'i', 'j', 'l', 'm', 'k', 'n' , 'o'};

    root = construct(root, in ,pre, 0, 6);

    cout << "Inorder: \n";
    Postorder(root);
    
}