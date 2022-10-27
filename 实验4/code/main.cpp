#include <iostream>
#include "queue.h"
using namespace std;

/**
 * 测试数据
 * -+a##*b##-c##d##/e##f##
 * 124#78##9###35##6##
 * 124##5##36##7#8#9##
 */

typedef char ElemType;
typedef struct Node
{
    ElemType val;
    struct Node *left = nullptr;
    struct Node *right = nullptr;
} *Tree, Node;
const int MaxNodeCnt = 100;

void CreateTree(Tree &T)
{
    char ch = getchar();
    if (!T) 
        if (ch != '#') {
            T = new Node;
            T->val = ch;
            CreateTree(T->left);
            CreateTree(T->right);
        }
}

void PreorderTraverse(const Tree T)
{
    if (T) {
        cout << T->val << " ";
        PreorderTraverse(T->left);
        PreorderTraverse(T->right);
    }
}

void InorderTraverse(const Tree T)
{
    if (T) {
        InorderTraverse(T->left);
        cout << T->val << " ";
        InorderTraverse(T->right);
    }
}

void PostorderTraverse(const Tree T)
{
    if (T) {
        PostorderTraverse(T->left);
        PostorderTraverse(T->right);
        cout << T->val << " ";
    }
}

// 非递归版本
void PreorderTraverseNonRec(const Tree T)
{
    Tree cur = T;
    Tree stack[MaxNodeCnt];
    int top = 0;

    while (cur != nullptr || top != 0) {
        if (cur != nullptr) {
            cout << cur->val << " ";
            stack[top++] = cur;
            cur = cur->left;
        }
        else {
            cur = stack[--top];
            cur = cur->right;
        }
    }
}

void InorderTraverseNonRec(const Tree T)
{
    Tree cur = T;
    Tree stack[MaxNodeCnt];
    int top = 0;

    while (cur != nullptr || top != 0) {
        if (cur != nullptr) {
            stack[top++] = cur;
            cur = cur->left;
        }
        else {
            cur = stack[--top];
            cout << cur->val << " ";
            cur = cur->right;
        }
    }
}

void PostorderTraverseNonRec(const Tree T)
{
    Tree stack[MaxNodeCnt];
    int cnt[MaxNodeCnt], top = 0, tc;
    Tree cur = T, tt;

    while (cur != nullptr || top != 0) {
        if (cur) {
            stack[top] = cur;
            cnt[top++] = 0;
            cur = cur->left;
        }
        else {
            tt = stack[top - 1];
            tc = cnt[--top];
            if (tc) {
                cout << tt->val << " ";
                cur = nullptr;
            }
            else {
                stack[top] = tt;
                cnt[top++] = tc + 1;
                cur = tt->right;
            }
        }
    } 
}

// 层次遍历
void BFS(const Tree T)
{
    using myqueue::queue;
    if (!T) return ;
    queue<Tree> Q;
    Q.push(T);
    while (!Q.empty()) {
        Tree t = Q.front(); Q.pop();
        cout << t->val << " ";
        if (t->left) Q.push(t->left);
        if (t->right) Q.push(t->right);
    }
}

int main(void)
{
    Tree T = NULL;
    cout << "Please input the inorder traversal sequence:" << endl;
    CreateTree(T);
    cout << "Preorder traverse" << endl;
    PreorderTraverse(T); cout << endl;
    PreorderTraverseNonRec(T); cout << endl;
    cout << "Inorder traverse" << endl;
    InorderTraverse(T); cout << endl;
    InorderTraverseNonRec(T); cout << endl;
    cout << "Postorder traverse" << endl;
    PostorderTraverse(T); cout << endl;
    PostorderTraverseNonRec(T); cout << endl;
    cout << "Floor traverse" << endl;
    BFS(T); cout << endl;
    return 0;
}