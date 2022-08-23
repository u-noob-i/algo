#include <iostream>
#include <queue>

using namespace std;

#define INT_MAX 2147483647

enum Color
{
    black, // 0
    red    // 1
};

struct Node
{
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int x)
    {
        left = right = parent = nullptr;
        data = x;
        color = red;
    }
};

class RedBlack
{
private:
    Node *root;

protected:
    void rotateleft(Node *x);
    void rotateright(Node *x);
    void Fix(Node *x);
    void fixdoubleblack(Node *x);

public:
    RedBlack()
    {
        root = nullptr;
    }
    void insert(const int &n);
    void Delete(Node *v);
    void Deletevalue(const int &n);
    void inorder(Node *x);
    void inorderUtil();
    void levelorder(Node *x);
    void levelorderUtil();
};

Node *BSTInsert(Node *cur, int x)
{

    if (cur->data < x)
    {
        if (cur->right == nullptr)
        {
            return cur;
        }
        return BSTInsert(cur->right, x);
    }
    else if (cur->data > x)
    {
        if (cur->left == nullptr)
        {
            return cur;
        }
        return BSTInsert(cur->left, x);
    }

    return cur;
}

void RedBlack::rotateleft(Node *x)
{
    Node *xright = x->right;
    x->right = xright->left;

    if (x->right != nullptr)
    {
        x->right->parent = x;
    }

    xright->parent = x->parent;

    if (x->parent == nullptr)
    {
        root = xright;
    }

    else if (x == x->parent->left)
    {
        x->parent->left = xright;
    }

    else
    {
        x->parent->right = xright;
    }

    xright->left = x;
    x->parent = xright;

    return;
}

void RedBlack::rotateright(Node *x)
{
    Node *xleft = x->left;
    x->left = xleft->right;

    if (x->left != nullptr)
    {
        x->left->parent = x;
    }

    xleft->parent = x->parent;

    if (x->parent == nullptr)
    {
        root = xleft;
    }

    else if (x->parent->right == x)
    {
        x->parent->right = xleft;
    }
    else
    {
        x->parent->left = xleft;
    }

    xleft->right = x;
    x->parent = xleft;

    return;
}

void RedBlack::Fix(Node *x)
{
    Node *xparent, *xgrandparent, *uncle;

    while (x != root && x->color == red && x->parent->color == red)
    {
        xparent = x->parent;
        xgrandparent = x->parent->parent;

        if (xparent == xgrandparent->left)
        {
            uncle = xgrandparent->right;

            if (uncle != nullptr && uncle->color == red)
            {
                xgrandparent->color = red;
                uncle->color = black;
                xparent->color = black;
                x = xgrandparent;
            }

            else
            {
                if (xparent->right == x)
                {
                    rotateleft(xparent);
                    x = xparent;
                    xparent = x->parent;
                }

                rotateright(xgrandparent);
                swap(xparent->color, xgrandparent->color);
                x = xparent;
            }
        }

        else
        {
            uncle = xgrandparent->left;

            if (uncle != nullptr && uncle->color == red)
            {
                xgrandparent->color = red;
                xparent->color = black;
                uncle->color = black;
                x = xgrandparent;
            }

            else
            {
                if (xparent->left == x)
                {
                    rotateright(xparent);
                    x = xparent;
                    xparent = x->parent;
                }
                rotateleft(xgrandparent);
                swap(xparent->color, xgrandparent->color);
                x = xparent;
            }
        }
    }
    root->color = black;

    return;
}

void RedBlack::insert(const int &x)
{
    Node *temp = new Node(x);

    if (root == nullptr)
    {
        root = temp;
        root->color = black;
        return;
    }

    Node *last = BSTInsert(root, x);
    temp->parent = last;
    if (x < last->data)
    {
        last->left = temp;
    }
    else
    {
        last->right = temp;
    }
    Fix(temp);
    return;
}

Node *find(Node *cur, const int &n)
{
    if (cur == nullptr)
    {
        return nullptr;
    }
    if (cur->data < n)
    {
        return find(cur->right, n);
    }
    else
    {
        return find(cur->left, n);
    }
}

Node *succesor(Node *cur)
{
    while (cur->left != nullptr)
    {
        cur = cur->left;
    }
    return cur;
}

void RedBlack::fixdoubleblack(Node *x)
{
    if (x == root)
    {
        return;
    }

    Node *parent = x->parent, *sibling;
    if (x->parent->left == nullptr || x->parent->right == nullptr)
    {
        sibling = nullptr;
    }
    else if (x->parent->left == x)
    {
        sibling = x->right;
    }
    else
    {
        sibling = x->left;
    }

    if (sibling == nullptr)
    {
        fixdoubleblack(parent);
    }
    if (sibling->color == red)
    {
        parent->color = red;
        sibling->color = black;
        if (sibling == parent->left)
        {
            rotateright(parent);
        }
        else
        {
            rotateleft(parent);
        }
        fixdoubleblack(x);
    }
    else
    {
        if ((sibling->right != nullptr && sibling->right->color == red) || (sibling->left != nullptr && sibling->left->color == red))
        {
            if (sibling->left != nullptr && sibling->left->color == red)
            {
                if (sibling == parent->left)
                {
                    sibling->left->color = sibling->color;
                    sibling->color = parent->color;
                    rotateright(parent);
                }
                else
                {
                    sibling->left->color = parent->color;
                    rotateright(sibling);
                    rotateleft(parent);
                }
            }
            else
            {
                if (sibling == parent->left)
                {
                    sibling->right->color = parent->color;
                    rotateleft(sibling);
                    rotateright(parent);
                }
                else
                {
                    sibling->right->color = sibling->color;
                    sibling->color = parent->color;
                    rotateleft(parent);
                }
            }
            parent->color = black;
        }
        else
        {
            sibling->color = red;
            if (parent->color == black)
            {
                fixdoubleblack(parent);
            }
            else
            {
                parent->color = black;
            }
        }
    }
}

void RedBlack::Delete(Node *v)
{
    Node *u;

    if (v->left != nullptr && v->right != nullptr)
    {
        u = succesor(v->right);
    }
    else if (v->left == nullptr && v->right == nullptr)
    {
        u = nullptr;
    }
    else if (v->left == nullptr)
    {
        u = v->right;
    }
    else
    {
        u = v->left;
    }

    if (u == nullptr)
    {
        if (v == root)
        {
            root = nullptr;
        }
        else
        {
            if (v->color == black)
            {
                fixdoubleblack(v);
            }
            else
            {
                if (v->parent->left != nullptr && v->parent->right != nullptr)
                {
                    if (v->parent->left == v)
                    {
                        v->parent->right->color = red;
                    }
                    else
                    {
                        v->parent->left->color = black;
                    }
                }
            }

            if (v == v->parent->left)
            {
                v->parent->left = nullptr;
            }
            else
            {
                v->parent->right = nullptr;
            }
        }
        delete v;
        return;
    }

    if (v->left == nullptr || v->right == nullptr)
    {
        if (v == root)
        {
            v->data = u->data;
            v->left = v->right = nullptr;
            delete u;
        }
        else
        {
            if (v->parent->left == v)
            {
                v->parent->left = u;
            }
            else
            {
                v->parent->right = u;
            }
            u->parent = v->parent;

            if (u->color == black && v->color == black)
            {
                fixdoubleblack(u);
            }
            else
            {
                u->color = black;
            }
            delete v;
        }
        return;
    }

    int temp = u->data;
    u->data = v->data;
    v->data = temp;

    Delete(u);
}

void RedBlack::Deletevalue(const int &n)
{
    Node *v = find(root, n);
    if (v == nullptr)
    {
        return;
    }
    Delete(v);
}

void RedBlack::inorder(Node *cur)
{
    if (cur == nullptr)
    {
        return;
    }
    inorder(cur->left);
    cout << cur->data << " ";
    inorder(cur->right);

    return;
}

void RedBlack::inorderUtil()
{

    inorder(root);

    return;
}

void RedBlack::levelorder(Node *cur)
{
    if (cur == NULL)
        return;

    std::queue<Node *> q;
    q.push(cur);

    while (!q.empty())
    {
        Node *temp = q.front();
        cout << temp->data << " ";
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);

        if (temp->right != NULL)
            q.push(temp->right);
    }
}

void RedBlack::levelorderUtil()
{
    levelorder(root);
}

int main()
{
    RedBlack *tree = new RedBlack();
    tree->insert(7);
    tree->insert(3);
    tree->insert(18);
    tree->insert(10);
    tree->insert(22);
    tree->insert(8);
    tree->insert(11);
    tree->insert(26);
    tree->insert(2);
    tree->insert(6);
    tree->insert(13);

    tree->inorderUtil();

    cout << "\n";

    tree->levelorderUtil();

    cout << "\n";

    tree->Deletevalue(18);
    tree->Deletevalue(11);
    tree->Deletevalue(3);
    tree->Deletevalue(10);
    tree->Deletevalue(22);

    tree->inorderUtil();

    cout << "\n";

    tree->levelorderUtil();

    cout << "\n";
}