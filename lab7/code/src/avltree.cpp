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
    // ����ɾ�����Ե�Ե�ʣ��ҽ���ͬ�ؼ��ֵĽ�������������
    else if (elem <= T->elem) {                     // �˴�
        T->left = imp_insert(T->left, elem);
        if (height(T->left) - height(T->right) == 2)
            if (elem <= T->left->elem)              // ��˴��Ĺ�ϵ�����Ҫ����һ��
                T = single_rotate_left(T);
            else
                T = double_rotate_left(T);
    }
    else {  // elem > T->elem                       // �˴�
        T->right = imp_insert(T->right, elem);
        if (height(T->right) - height(T->left) == 2)
            if (elem > T->right->elem)              // ��˴��Ĺ�ϵ�����Ҫ����һ��
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
    for (int i = 0; i < d; i++)
        std::cout << '#';
    if (T != nullptr) {
        std::cout << T->elem.ISBN << std::endl;
        imp_show_all(T->left, d + 1);
        imp_show_all(T->right, d + 1);
    }
    else 
        std::cout << '^' << std::endl;
}

bool avl_tree::exist(elem_type key)
{
    return imp_exist(tree, key);
}

bool avl_tree::imp_exist(imp_avl_tree T, elem_type key)
{
    if (T == nullptr)
        return false;
    else if (key < T->elem)
        return imp_exist(T->left, key);
    else if (key > T->elem)
        return imp_exist(T->right, key);
    else 
        return true;
}

bool avl_tree::remove(elem_type key)
{
    if (exist(key)) {
        tree = imp_remove(tree, key);
        return true;
    }
    else 
        return false;
}

// ���ɾ����T������ƽ��
imp_avl_tree avl_tree::imp_remove(imp_avl_tree T, elem_type key)
{
    if (key < T->elem) {
        T->left = imp_remove(T->left, key);
        if (height(T->right) - height(T->left) == 2) {
            if (height(T->right->left) < height(T->right->right))
                T = double_rotate_right(T);
            else
                T = single_rotate_right(T);
        }
        T->height = Max(height(T->left), height(T->right)) + 1;
    }
    else if (key > T->elem) {
        T->right = imp_remove(T->right, key);
        if (height(T->left) - height(T->right) == 2) {
            if (height(T->left->right) > height(T->left->left))
                T = double_rotate_left(T);
            else 
                T = single_rotate_left(T);
        }
        T->height = Max(height(T->left), height(T->right)) + 1;
    }
    else {      // ���ý��ΪҪɾ���Ľ��
        if (T->left == nullptr && T->right == nullptr) {
            delete T;
            T = nullptr;
        }
        else if (T->left != nullptr && T->right == nullptr) {
            T->elem = T->left->elem;
            delete T->left;
            T->left = nullptr;
        }
        else if (T->left == nullptr && T->right != nullptr) {
            T->elem = T->right->elem;
            delete T->right;
            T->right = nullptr;
        }
        else {      // ���ҽڵ㶼��Ϊ��
            imp_avl_tree pre = T->left;
            while (pre->right != nullptr)
                pre = pre->right;
            T->elem = pre->elem;
            T->left = imp_remove(T->left, pre->elem);
            if (height(T->right) - height(T->left) == 2) {
                if (height(T->right->left) < height(T->right->right))
                    T = double_rotate_right(T);
                else
                    T = single_rotate_right(T);
            }
            T->height = Max(height(T->left), height(T->right)) + 1;
        }
    }
    return T;
}