#ifndef AVL_HPP
#define AVL_HPP

class AVL {
    private:
        int key;
        int *flight_index;
        AVL *left;
        AVL *right;
        int height;

    public:
        AVL* NewNode(int key);
        int GetBalance(AVL *N);
        int GetHeight(AVL *N);
        AVL *RightRotate(AVL *y);
        AVL *LeftRotate(AVL *x);
        AVL *Insert(AVL* node, int key);
        AVL *DeleteNode(AVL* root, int key);
        AVL *FindKey(int key);
        void PostOrder(AVL* root);
};

#endif