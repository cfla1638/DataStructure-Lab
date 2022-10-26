#include <iostream>
#include "sqlist.h"
using namespace std;

int main(void)
{
    SqList L;
    int pos;
    SqList::ElemType t;
    
    CreateSqList(L);
    L.traverse();
    cout << "--insert--\n";
    cout << "please input the pos to insert: ";
    cin >> pos;
    cout << "please input an element to insert : ";
    cin >> t;
    L.insert(pos, t);
    cout << "After insert():\n";
    L.traverse();
    cout << "--remove--\n";
    cout << "please input the pos to be removed : ";
    cin >> pos;
    L.remove(pos);
    cout << "After remove():\n";
    L.traverse();
    cout << "--Get the specified element--\n";
    cout << "please input the pos to get:";
    cin >> pos;
    cout << "it is " << L.getElem(pos) << '\n';
    cout << "--getMaxElem--\n";
    cout << "the largest element is " << L.getMaxElem() << '\n';
    cout << "--getMinElem--\n";
    cout << "the smallest element is " << L.getMinElem() << '\n';
    cout << "--find element--\n";
    cout << "please input the value of the element to be found : ";
    cin >> t;
    cout << "the " << t << " is in " << L.find(t) << "\n";
    cout << "--reverse--\n";
    L.reverse();
    cout << "After reverse() : \n";
    L.traverse();
    
    return 0;
}