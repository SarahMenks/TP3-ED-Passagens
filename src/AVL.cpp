#include <iostream>
#include "AVL.hpp"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int AVL::GetHeight(AVL *N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

AVL* AVL::NewNode(int key) {
    //cria uma folha de altura 1
    AVL* node = new AVL();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; 
    return(node);
}

int AVL::GetBalance(AVL *N) {
    if (N == nullptr)
        return 0;

    return (N->GetHeight(N->left) - N->GetHeight(N->right));
}

//Rotacao para direita
AVL* AVL::RightRotate(AVL *y) {
    AVL *x = y->left;
    AVL *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x;
}

//Rotacao para esquerda
AVL* AVL::LeftRotate(AVL *x) {
    AVL *y = x->right;
    AVL *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

    return y;
}

AVL* AVL::Insert(AVL* node, int key) {
    if (node == nullptr)
        return(NewNode(key));

    //procura lugar para inserir
    if (key < node->key)
        node->left = Insert(node->left, key);
    else if (key > node->key)
        node->right = Insert(node->right, key);
    else 
        return node;

    node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));

    int balance = GetBalance(node);


    //caso esquerda-esquerda
    if (balance > 1 && key < node->left->key)
        return RightRotate(node);

    //caso direita-direita
    if (balance < -1 && key > node->right->key)
        return LeftRotate(node);

    //caso esquerda-direita
    if (balance > 1 && key > node->left->key) {
        node->left = LeftRotate(node->left);
        return RightRotate(node);
    }

    //caso direita-esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }

    return node;
}

AVL* AVL::DeleteNode(AVL* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = DeleteNode(root->left, key);

    else if (key > root->key)
        root->right = DeleteNode(root->right, key);

    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AVL *temp = root->left ? root->left : root->right;

            //se nao tem filhos é nulo
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else //se tem exatamente um filho
                *root = *temp; 
            delete(temp);
        } else {
            // se tem dois filhos, pega o sucessor
            AVL* temp = root->right;
            while (temp->left != nullptr)
                temp = temp->left;

            root->key = temp->key;
            root->right = DeleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(GetHeight(root->left), GetHeight(root->right));
    
    int balance = GetBalance(root);

    //caso esquerda-esquerda
    if (balance > 1 && GetBalance(root->left) >= 0)
        return RightRotate(root);

    //caso esquerda-direita
    if (balance > 1 && GetBalance(root->left) < 0) {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    //caso direita-direita
    if (balance < -1 && GetBalance(root->right) <= 0)
        return LeftRotate(root);

    //caso direita-esquerda
    if (balance < -1 && GetBalance(root->right) > 0) {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

AVL* AVL::FindKey(int key) {
    //retorna o nó da chave correspondente 
    AVL *current = this;
    while (current != nullptr) {
        if (key == current->key)
            return current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

void AVL::PostOrder(AVL *root) {
    if (root != nullptr) {
        PostOrder(root->left);
        PostOrder(root->right);
        std::cout << root->key;
    }
}