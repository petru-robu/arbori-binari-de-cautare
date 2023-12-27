#ifndef AVL
#define AVL

#include <iostream>
#include <queue>
#include <algorithm>

struct Node
{
    int val;
    int height;
    Node *left, *right;
    Node(int x)
    {
        val = x;
        left = right = 0;
        height = 1;
    }
};

void inorder(Node* root)
{
    //stanga, radacina, dreapta
    if(root == NULL)
        return;
    inorder(root->left);
    std::cout<<root->val<<' ';
    inorder(root->right);
}

void preorder(Node* root)
{
    //radacina, stanga, dreapta
    if(root == NULL)
        return;
    std::cout<<root->val<<' ';
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root)
{
    //stanga, dreapta, radacina
    if(root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    std::cout<<root->val<<' ';
}

void levelorder(Node* root)
{
    //parcurgere pe nivele
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

int height(Node* root)
{
    if(!root)
        return 0;
    else
        return root->height;
}

Node* rotateRight(Node* y)
{
   Node *x = y->left, *t3 = y->right;
   Node *t2 = x->right, *t1 = x->left;

   x->right = y;
   y->left = t2;

   y->height = std::max(height(y->left), height(y->right)) + 1;
   x->height = std::max(height(x->left), height(x->right)) + 1;
   return x;
}

Node* rotateLeft(Node* x)
{
   Node *y = x->right, *t1 = x->left;
   Node *t2 = y->left, *t3 = y->right;;

   y->left = x;
   x->right = t2;

   y->height = std::max(height(y->left), height(y->right)) + 1;
   x->height = std::max(height(x->left), height(x->right)) + 1;
   return y;
}

int balanceFactor(Node* root)
{
    if(!root)
        return 0;
    else
        return height(root->left) - height(root->right);
}

Node* insert(Node* root, int val)
{
    //aplicam insertia normala bst
    if(!root)
        return new Node(val);

    if(val < root->val)
        root->left = insert(root->left, val);
    else 
        if(val > root->val)
            root->right = insert(root->right, val);
    else
        return root;

    //in recursie ajustam nodurile aplicand rotatii
    root->height = std::max(height(root->left), height(root->right)) + 1;

    int bal = balanceFactor(root);

    //cazul ll
    if(bal > 1 && val < root->left->val)
        return rotateRight(root);

    //cazul rr
    if(bal < -1 && val > root->right->val)
        return rotateLeft(root);
    
    //cazul lr
    if(bal > 1 && val > root->left->val)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    //cazul rl
    if(bal < -1 && val < root->right->val)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Node* search(Node* root, int val)
{
    if(root == NULL || root->val == val) 
    {
        //am gasit nodul(il intoarcem)/nu am gasit nodul(intoarcem null)
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

Node* successor(Node* root)
{
    Node* succ = root;
    while(succ->left)
        succ = succ->left;
    return succ;
}

Node* erase(Node* root, int val)
{
    //aplicam stergerea standard BST
    if(root == NULL)
        return root;
    
    if(val < root->val)
        root->left = erase(root->left, val);
    else
        if(val > root->val)
            root->right = erase(root->right, val);
    else
    {
        //nodul nu are doi fii
        if(!root->left || !root->right)
        {
            Node *temp;
            if(root->left)
                temp = root->left;
            else
                temp = root->right;

            //nodul este frunza, doar stergem
            if(!temp)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            delete temp;
        }
        else
        {
            //nodul de sters are doi fii
            Node* succ = root->right;
            while(succ->left != NULL)
                succ = succ->left;
            
            root->val = succ->val;
            root->right = erase(root->right, succ->val);   
        }
        
    }

    if(root == NULL)
        return root;
    
    root->height = std::max(height(root->left), height(root->right)) + 1;

    int bal = balanceFactor(root);
    int bal_l = balanceFactor(root->left), bal_r = balanceFactor(root->right);

    //cazul ll 
    if(bal > 1 && bal_l >=0)
        return rotateRight(root);

    //cazul lr
    if(bal > 1 && bal_l < 0)
    {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    //cazul rr
    if(bal < -1 && bal_r <= 0)
        return rotateLeft(root);

    //cazul rl
    if(bal < -1 && bal_r > 0)
    {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}


class AVLTree
{
private:
    Node* root;

public:
    AVLTree();
    
    void Insert(int val);
    void Erase(int val);
    bool Search(int val);

    void Inorder();
    void Preorder();
    void Postorder();
    void LevelOrder();
};

AVLTree::AVLTree()
{
    root = NULL;
}

void AVLTree::Inorder()
{
    inorder(root);
    std::cout<<'\n';
}

void AVLTree::Preorder()
{
    preorder(root);
    std::cout<<'\n';
}

void AVLTree::LevelOrder()
{
    levelorder(root);
    std::cout<<'\n';
}

void AVLTree::Postorder()
{
    postorder(root);
    std::cout<<'\n';
}

void AVLTree::Insert(int val)
{
    root = insert(root, val);
}

void AVLTree::Erase(int val)
{
    root = erase(root, val);
}

bool AVLTree::Search(int val)
{
    return (search(root, val) != NULL);
}

#endif