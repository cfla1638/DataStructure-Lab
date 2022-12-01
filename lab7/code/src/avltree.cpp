#include "avltree.h"

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


imp_avl_tree avl_tree::single_rotate_left(imp_avl_tree)
{

}

imp_avl_tree avl_tree::single_rotate_right(imp_avl_tree)
{

}

imp_avl_tree avl_tree::double_rotate_left(imp_avl_tree)
{

}

imp_avl_tree avl_tree::double_rotate_right(imp_avl_tree)
{

}