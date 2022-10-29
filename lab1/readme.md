# 顺序表的基本操作

## 实验要求

实现顺序表的各种基本操作，具体内容如下：

1. 创建每个元素都是int类型的顺序表。
2. 输入顺序表的全部数据。
3. 输出顺序表的全部元素，每个元素后面加上一个空格，最后加上一个回车。
4. 插入新元素到指定序号的前面（序号从1开始）。
5. 删除指定序号的元素。
6. 获取指定序号的元素。
7. 获取顺序表的最大值元素。
8. 获取顺序表的最小值元素。
9. 查找等于某个值的第一个元素。
10. 顺序表元素逆置（最后一个元素放到开头，倒数第二个元素放到第二个位置……）



## 项目设计

本项目实现了一个顺序表和其基本操作。若要使用此表，请注意此表提供的接口，它们的下标是从1开始的。

本项目有一个SqList类，表示顺序表，顺序表的基本操作都被封装进了此类。

本项目有一个友元函数CreateSqList(),这个函数封装了SqList的基本操作，实现了一根据键盘输入来初始化表的功能。



## 分析总结

1. 顺序表的操作主要难在插入和删除。因为没有使用复杂的Allocater，但又想保持C++的风格，于是就没有使用c语言的realloc()函数。只用了C++的new和delete 运算符。因此需要自己改动一下书上的代码，来实现realloc()函数的功能。

2. 通过这次项目，我复习了顺序表的操作，练习了之前很少时间的面向对象的写法。。

3. 对于所有类中都存在的Ok,Error Overflow 与其把它们声明为const int不如将他们声明成与每个类的对象无关的enum,方便这个类的友元函数使用。 

4. 时间空间复杂度分析

   时间复杂度：

   `void traverse() const; `O(n)

   `void insert(int pos, ElemType elem);` O(n)

   `ElemType remove(int pos);`O(n)

   `ElemType getElem(int pos) const;`O(1)

   `ElemType getMaxElem() const;`O(n)

   `ElemType getMinElem() const;`O(n)

   `int find(ElemType val) const;`O(n)

   `void reverse();`O(n)

   空间复杂度

   `void traverse() const;` O(1)

   `void insert(int pos, ElemType elem);`O(1)

   `ElemType remove(int pos);`O(1)

   `ElemType getElem(int pos) const;`O(1)

   `ElemType getMaxElem() const;`O(1)

   `ElemType getMinElem() const;`O(1)

   `int find(ElemType val) const;`O(1)

   `void reverse();`O(1)

 

## 源代码

`sqlist.h`

`sqlist.cpp`

`main.cpp`