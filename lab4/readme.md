# 二叉树的遍历

## 实验要求

基本要求：以二叉链表为存储结构，实现二叉树的先、中、后三种次序的递归遍历。

选做内容：

1. 以二叉链表为存储结构，实现二叉树的先、中、后三种次序的非递归遍历。

2. 使用队列来实现二叉树的层序遍历（不要使用STL的队列）。

3. 按凹入表或树形打印所遍历的二叉树。



## 源文件

`main.cpp`

`queue.h` 



## 长了个记性

当程序在不同编译器下表现出不同行为时，第一时间就要考虑是不是本地自动变量默认初始化导致了未定义行为。

这次的实验就是这样子的，忘记初始化主函数的`Tree T` 了，导致程序在我的编译器下表现正常，在同学的编译器下就会导致段错误。