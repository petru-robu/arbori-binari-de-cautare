#ifndef BST
#define BST

#include <iostream>
#include <queue>

struct Node
{
    int val;
    Node *left, *right;
    Node(int x)
    {
        val = x;
        left = right = 0;
    }
};

void inorder(Node* root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    std::cout<<root->val<<' ';
    inorder(root->right);
}

void preorder(Node* root)
{
    if(root == NULL)
        return;
    std::cout<<root->val<<' ';
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root)
{
    if(root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    std::cout<<root->val<<' ';
}

void levelorder(Node* root)
{
    if(root == NULL)
        return;
    std::queue<Node*> Q;
    Q.push(root);
    
    while(!Q.empty())
    {
        Node* nod = Q.front();
        Q.pop();
        std::cout<<nod->val<<' ';
        if(nod->left != NULL)
            Q.push(nod->left);
        if(nod->right != NULL)
            Q.push(nod->right);
    }
}

Node* insert(Node*& root, int val)
{
    if(root == NULL)
    {
        return new Node(val);
    }
    
    if(val < root->val)
    {
        //nr mai mic, inseram in subarborele stang
        root->left = insert(root->left, val);
    }
    else
    {
        //nr mai mare, inseram in subarborele drept
        root->right = insert(root->right, val);
    }
    return root;
}

Node* erase(Node* root, int val)
{
    if(root == NULL)
        return root;
    
    if(val < root->val)
    {
        //nr mai mic, se afla in subarborele stang
        root->left = erase(root->left, val);
        return root;
    }
    else if(val > root->val)
    {
        //nr mai mare, se afla in subarborele drept
        root->right = erase(root->right, val);
        return root;
    }
    else if(val == root->val)
    {
        if(root->left == NULL)
        {
            //nodul de sters are doar fiul drept sau e frunza
            Node* t = root->right;
            delete root;
            return t;
        }
        else if(root->right == NULL)
        {
            //nodul de sters are doar fiul stang
            Node* t = root->left;
            delete root;
            return t;
        }

        //nodul de sters are doi fii
        Node* succ = root->right;
        while(succ->left != NULL)
            succ = succ->left;
        
        root->val = succ->val;
        root->right = erase(root->right, succ->val);
        return root;
    }
}

Node* search(Node* root, int val)
{
    if(root == NULL || root->val == val) 
    {
        //am gasit nodul(il intoarcem)/nu am gasit nodul(intoarcem 0)
        return root;
    }

    if(root->val < val)
    {
        //nodul cautat are valore mai mare, continuam in subarborele drept
        return search(root->right, val);
    }
    if(root->val > val)
    {
        //nodul cautat are valore mai mica, continuam in subarborele stang
        return search(root->left, val);
    }
}

class BinTree
{
private:
    Node* root;

public:
    BinTree();
    
    void Insert(int val);
    void Erase(int val);
    bool Search(int val);

    void Inorder();
    void Preorder();
    void Postorder();
    void LevelOrder();
};

BinTree::BinTree()
{
    root = NULL;
}

void BinTree::Insert(int val)
{
    root = insert(root, val);
}

void BinTree::Erase(int val)
{
    root = erase(root, val);
}

bool BinTree::Search(int val)
{
    return (search(root, val) != NULL);
}

void BinTree::Inorder()
{
    inorder(root);
    std::cout<<'\n';
}

void BinTree::Preorder()
{
    preorder(root);
    std::cout<<'\n';
}

void BinTree::LevelOrder()
{
    levelorder(root);
    std::cout<<'\n';
}
void BinTree::Postorder()
{
    postorder(root);
    std::cout<<'\n';
}

#endif