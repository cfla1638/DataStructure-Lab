#include "avltree.h"
#include <iostream>

int avl_tree::Max(int a, int b)
{
    return (a > b ? a : b);
}

int avl_tree::height(imp_avl_tree pos)
{
    if (pos == nullptr)
        return -1;          // 定义: 根节点为nullptr的树的高度为-1
    else
        return pos->height;
}

void avl_tree::insert(elem_type elem)
{
    tree = imp_insert(tree, elem);
}

imp_avl_tree avl_tree::imp_insert(imp_avl_tree T, elem_type elem)
{
    if (T == nullptr) {
        T = new avl_node;
        T->elem = elem;
        T->height = 0;
        T->left = T->right = nullptr;
    }
    else if (elem < T->elem) {
        T->left = imp_insert(T->left, elem);
        if (height(T->left) - height(T->right) == 2)
            if (elem < T->left->elem)
                T = single_rotate_left(T);
            else
                T = double_rotate_left(T);
    }
    else {  // elem >= T->elem
        T->right = imp_insert(T->right, elem);
        if (height(T->right) - height(T->left) == 2)
            if (elem > T->right->elem)
                T = single_rotate_right(T);
            else
                T = double_rotate_right(T);
    }
    T->height = Max(height(T->left), height(T->right)) + 1;
    return T;
}

// 插入到K2的左子树的左子树上，导致K2不平衡
imp_avl_tree avl_tree::single_rotate_left(imp_avl_tree K2)
{
    imp_avl_tree K1;
    K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;

    /**
     * 1. 因为只有K1, K2两个结点的相对位置发生了变化，它们的子树并没有发生结构变化，
     *    故他们的子树的高度是正确的，不需要调整
     * 2. 因为调整完后，K1在K2的上面，故要先计算K2的高度，再去计算K1的高度
     */
    K2->height = Max(height(K2->left), height(K2->right)) + 1;
    K1->height = Max(height(K1->left), height(K1->right)) + 1;
    return K1;
}

// 插入到K2的右子树的右子树上，导致K2不平衡
imp_avl_tree avl_tree::single_rotate_right(imp_avl_tree K2)
{
    imp_avl_tree K1;
    K1 = K2->right;
    K2->right = K1->left;
    K1->left = K2;

    K2->height = Max(height(K2->left), height(K2->right)) + 1;
    K1->height = Max(height(K1->left), height(K1->right)) + 1;
    return K1;
}

// 插入到K3的左子树的右子树上，导致K3不平衡
imp_avl_tree avl_tree::double_rotate_left(imp_avl_tree K3)
{
    K3->left = single_rotate_right(K3->left);
    return single_rotate_left(K3);
}

imp_avl_tree avl_tree::double_rotate_right(imp_avl_tree K3)
{
    K3->right = single_rotate_left(K3->right);
    return single_rotate_right(K3);
}

void avl_tree::show_all()
{
    imp_show_all(tree, 0);
}

void avl_tree::imp_show_all(imp_avl_tree T, int d)
{
    if (T != nullptr) {
        for (int i = 0; i < d; i++)
            std::cout << '#';
        std::cout << T->elem.ISBN << std::endl;
        imp_show_all(T->left, d + 1);
        imp_show_all(T->right, d + 1);
    }
}