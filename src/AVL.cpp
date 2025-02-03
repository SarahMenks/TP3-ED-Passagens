#include <iostream>
#include "AVL.hpp"

int max(int a, int b) {
    return (a > b) ? a : b;
}

// void IndexSize(Node *node, int size){
//     node->flight_index = new int[size];
//     node->pos = 0;
// }

int GetHeight(Node *N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

Node *NewNode(std::string key, int index) {
    //cria uma folha de altura 1
    Node* node = new Node();
    node->flight_index[node->pos] = index;
    node->pos++;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr; 
    node->height = 1; 
    return node;
}

int GetBalance(Node *N) {
    if (N == nullptr)
        return 0;

    return (GetHeight(N->left) - GetHeight(N->right));
}

//Rotacao para direita
Node* RightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x;
}

//Rotacao para esquerda
Node* LeftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

    return y;
}

Node* Insert(Node* node, std::string key, int const index) {
    if (node == nullptr){
        node = NewNode(key, index); 
        return node;
    }

    //procura lugar para inserir
    if (key < node->key)
        node->left = Insert(node->left, key, index);
    else if (key > node->key)
        node->right = Insert(node->right, key, index);
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

Node* DeleteNode(Node* root, std::string key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = DeleteNode(root->left, key);

    else if (key > root->key)
        root->right = DeleteNode(root->right, key);

    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node *temp = root->left ? root->left : root->right;

            //se nao tem filhos é nulo
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else //se tem exatamente um filho
                *root = *temp; 
            delete(temp);
        } else {
            // se tem dois filhos, pega o sucessor
            Node* temp = root->right;
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

int* FindKey(Node *root, std::string key) {
    //retorna o vetor de indices da chave correspondente 
    Node *current = root;
    while (current != nullptr) {
        if (key == current->key)
            return current->flight_index;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr; //se nao encontrar, retorna nulo
}

void FindAndInsert(Node *root, std::string key, int index){
    //funcao para encontrar e inserir um voo
    //se o voo ja existe, insere o indice no vetor de indices
    Node *current = root;
    while (current != nullptr) {
        if (key == current->key){
            current->flight_index[current->pos] = index;
            current->pos++;
            return;
        }
        if (key < current->key)
            current = current->left;
        else //current >= key
            current = current->right;
    }
    root = Insert(nullptr, key, index); //as vozes da minha cabeça deram uma surtada aqui

}


void PostOrder(Node *root) {
    if (root != nullptr) {
        PostOrder(root->left);
        PostOrder(root->right);
        std::cout << root->key;
    }
}