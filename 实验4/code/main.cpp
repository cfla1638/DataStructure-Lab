#include <iostream>
#include <stack>
#include <queue>
using namespace std;
/**
 * 测试数据
 * -+a##*b##-c##d##/e##f##
 * 124#57##6###38##9##
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

}

int main(void)
{
    Tree T;
    CreateTree(T);
    InorderTraverse(T); cout << endl;
    InorderTraverseNonRec(T); cout << endl;
    return 0;
}