#ifndef H_HEAP
#define H_HEAP
#include <iostream>
#include <functional>

template <typename T, typename COMP = std::less<T> >
class heap
{
public:
    heap();
    heap(COMP cmp);

    bool empty() const {return !size;};
    void push(T elem);
    T top() const;
    void pop();

private:
    COMP cmp;
    int capacity = 600;     // 最多会有511个结点
    int size;
    T * base;
};

template <typename T, typename COMP>
heap<T, COMP>::heap() : capacity(512), size(0), base(nullptr)
{
    base = new T[capacity];
}

template <typename T, typename COMP>
heap<T, COMP>::heap(COMP cmp) : capacity(512), size(0), base(nullptr), cmp(cmp)
{
    base = new T[capacity];
}

template <typename T, typename COMP>
void heap<T, COMP>::push(T elem)
{
    int i;
    if (size + 1 >= capacity) {
        std::cerr << "heap is full" << std::endl;
        return ;
    }
    // 这里的顺序也是一个bug,应让i > 1作为第一个测试条件，不然会段错误!
    for (i = ++size; i > 1 && cmp(base[i / 2], elem); i /= 2)
        base[i] = base[i / 2];
    base[i] = elem;
}

template <typename T, typename COMP>
T heap<T, COMP>::top() const
{
    if (size != 0)      // TODO
        return base[1];
    else {
        std::cerr << "heap::top() : heap empty!" << std::endl;
        exit(1);
    }
}

template <typename T, typename COMP>
void heap<T, COMP>::pop()
{
    int last_elem = base[size--], i, child;

    for (i = 1; i * 2 <= size; i = child) {
        child = i * 2;  // 左孩子

        if (child != size && cmp(base[child], base[child + 1]))
            child++;
        if (cmp(last_elem, base[child]))
            base[i] = base[child];
        else
            break;
    }
    base[i] = last_elem;
}

#endif