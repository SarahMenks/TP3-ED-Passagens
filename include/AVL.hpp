#ifndef AVL_HPP
#define AVL_HPP

#define MAX_VOOS 1000

typedef struct Node
{
    std::string key;
    int pos = 0;
    int *flight_index = new int[MAX_VOOS];
    Node *left;
    Node *right;
    int height;

    // Node(int size) : flight_index(new int[size]), left(nullptr), right(nullptr), height(1) {}
    // ~Node() { delete[] flight_index; }

} Node;
 
//void IndexSize(Node *node, int size);
Node *NewNode(std::string key, int index);
int GetBalance(Node *N);
int GetHeight(Node *N);
Node *RightRotate(Node *y);
Node *LeftRotate(Node *x);
Node *Insert(Node* node, std::string key, int const index);
Node *DeleteNode(Node* root, std::string key);
int *FindKey(Node *root, std::string key);
void FindAndInsert(Node *root, std::string key, int index);
void PostOrder(Node* root);

#endif