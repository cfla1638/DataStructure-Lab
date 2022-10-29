#include "sqlist.h"
#include <iostream>

SqList::SqList() : length(0), listSize(ListInitSize)
{
    base = new ElemType[ListInitSize];
    if (base == nullptr) {
        std::cerr << "SqList(): initialize error\n";
        exit(Overflow);
    }
}

SqList::SqList(int size, int val) : length(size)
{
    if (size < ListInitSize && size >= 0) {
        base = new ElemType[ListInitSize];
        if (base == nullptr) {
            std::cerr << "SqList(): initialize error\n";
            exit(Overflow);
        }
        for (int i = 0; i < size; i++)
            base[i] = val;
        listSize = ListInitSize;
    }
    else if (size > ListInitSize && size < (ListInitSize + ListIncrement)) {
        base = new ElemType[ListInitSize + ListIncrement];
        if (base == nullptr) {
            std::cerr << "SqList(): initialize error\n";
            exit(Overflow);
        }
        for (int i = 0; i < size; i++)
            base[i] = val;
        listSize = ListInitSize + ListIncrement;
    }
    else {
        std::cerr << "SqList(): size exceeds the limit\n";
        exit(Error);
    }
}

SqList::SqList(const SqList &ori) : length(ori.length), listSize(ori.listSize)
{
    base = new ElemType[ori.listSize];
    if (base == nullptr) {
        std::cerr << "SqList(): initialize error\n";
        exit(Overflow);
    }
    for (int i = 0; i < ori.length; i++)
        base[i] = ori.base[i];
}

SqList::~SqList()
{
    if (base != nullptr)
        delete[] base;
}

SqList & SqList::operator=(const SqList &rhs)
{
    if (this != &rhs) {     // 防止自赋值
        length = rhs.length;
        listSize = rhs.listSize;
        delete[] base;
        base = new ElemType[rhs.listSize];
        if (base == nullptr) {
            std::cerr << "copy assignment operator : Allocate memory error\n";
            exit(Overflow);
        }
        for (int i = 0; i < rhs.length; i++)
            base[i] = rhs.base[i];
    }
    return *this;
}

void SqList::traverse() const
{
    for (int i = 0; i < length; i++)
        std::cout << base[i] << " ";
    std::cout << std::endl;
}

void SqList::insert(int pos, ElemType elem)    // 序号 1~length
{
    if (pos < 1 || pos > length + 1) { // length + 1 即插入在最后一位
        std::cerr << "insert(): Insert into an illegal location\n";
        exit(Error);
    }
    if (length >= listSize) {
        ElemType * newbase = new ElemType[ListInitSize + ListIncrement];
        if (newbase == nullptr) {
            std::cerr << "insert(): realloc error\n";
            exit(Overflow);
        }
        for (int i = 0; i < length; i++)
            newbase[i] = base[i];
        delete[] base;
        base = newbase;
        listSize += ListIncrement;
    }
    for (int i = length; i >= pos; i--)
        base[i] = base[i - 1];
    base[pos - 1] = elem;
    length++;
}

SqList::ElemType SqList::remove(int pos)
{
    ElemType ret;

    if (pos < 1 || pos > length) {
        std::cerr << "remove(): remove an illegal location\n";
        exit(Error);
    }

    ret = base[pos - 1];
    for (int i = pos; i <= length; i++)
        base[i - 1] = base[i];
    length--;

    return ret;
}

SqList::ElemType SqList::getElem(int pos) const
{
    if (pos < 1 || pos > length) {
        std::cerr << "getElem(): try to get an illegal location\n";
        exit(Error);
    }
    return base[pos - 1];
}

SqList::ElemType SqList::getMaxElem() const
{
    if (length != 0) {
        ElemType maxElem = base[0];
        for (int i = 1; i < length; i++)
            if (base[i] > maxElem)
                maxElem = base[i];
        return maxElem;
    }
    else {
        std::cerr << "getMaxElem() : Try to get the largest element of an empty table\n";
        exit(Error);
    }
}

SqList::ElemType SqList::getMinElem() const
{
    if (length != 0) {
        ElemType minElem = base[0];
        for (int i = 1; i < length; i++)
            if (base[i] < minElem)
                minElem = base[i];
        return minElem;
    }
    else {
        std::cerr << "getMinElem() : Try to get the smallest element of an empty table\n";
        exit(Error);
    }
}

int SqList::find(ElemType val) const
{
    for (int i = 0; i < length; i++)
        if (base[i] == val)
            return i + 1;
    return 0;
}

void SqList::reverse()
{
    int i = 0, j = length - 1;
    ElemType t;

    while (i <= j) {
        t = base[i];
        base[i] = base[j];
        base[j] = t;
        i++;
        j--;
    }
}

void CreateSqList(SqList &list)
{
    int n;
    SqList::ElemType elem;

    std::cout << "Please input list's length : ";
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cout << "Please input an element : ";
        std::cin >> elem;
        list.insert(list.length + 1, elem);
    }

    std::cout << "Successfully create a SqList\n";
}
