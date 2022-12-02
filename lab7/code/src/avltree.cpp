#include "avltree.h"
#include <iostream>

int avl_tree::Max(int a, int b)
{
    return (a > b ? a : b);
}

int avl_tree::height(imp_avl_tree pos)
{
    if (pos == nullptr)
        return -1;          // ����: ���ڵ�Ϊnullptr�����ĸ߶�Ϊ-1
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

// ���뵽K2�����������������ϣ�����K2��ƽ��
imp_avl_tree avl_tree::single_rotate_left(imp_avl_tree K2)
{
    imp_avl_tree K1;
    K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;

    /**
     * 1. ��Ϊֻ��K1, K2�����������λ�÷����˱仯�����ǵ�������û�з����ṹ�仯��
     *    �����ǵ������ĸ߶�����ȷ�ģ�����Ҫ����
     * 2. ��Ϊ�������K1��K2�����棬��Ҫ�ȼ���K2�ĸ߶ȣ���ȥ����K1�ĸ߶�
     */
    K2->height = Max(height(K2->left), height(K2->right)) + 1;
    K1->height = Max(height(K1->left), height(K1->right)) + 1;
    return K1;
}

// ���뵽K2�����������������ϣ�����K2��ƽ��
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

// ���뵽K3�����������������ϣ�����K3��ƽ��
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