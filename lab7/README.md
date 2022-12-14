# 简易图书管理模拟系统

## 实验要求

1、问题描述：一个简易图书管理的基本业务活动包括：对新购入一种书的采编入库、图书的借阅和归还等。

2、基本要求：

（1）每种书的登记内容至少包括书号、书名、著者、现存量和总库存量等五项。

（2）作为演示系统，不必使用文件存储书籍数据和借阅登记信息。我们要求各种书的数据用平衡二叉树来存储，借阅登记信息采用顺序表—链表来存储。顺序表存储借阅者信息，链表存储借阅者所借的各种书籍信息。借阅登记信息的存储结构如下示意：

![img](https://cdn.jsdelivr.net/gh/cfla1638/Img/202211232018462.gif)

需要实现的三种主要功能定义如下：

①采编入库：新购入一种书，经分类和确定书号之后登记到图书帐目中去。如果这种书在帐中已有，则只将该书的总库存量增加。

②借阅：如果一种书的现存量大于零，则借出一本，登记借阅者的借书证号和归还期限。

③归还：删除这个借阅者对这种书的借阅登记，改变这种书的现存量。

3、测试数据示例：

入库书号（ISBN）： 9787302455882，9787302386346，9787115169853，9787302033141，9787111540090，9787121337826，9787302330646，9787302330653（这8种书各入库1本）

借书证号为081716的借阅者，先借阅上面8种图书各一本，后归还图书ISBN 9787302386346和ISBN 9787302330653。

借书证号为081710的借阅者，先借阅图书ISBN 9787302386346和ISBN 9787302330653各一本，后归还图书ISBN 9787302330653。

其余测试数据可自行设计，需要尽量多测试几种不同情况。

4、实现提示：

（1）各种图书按登记的先后顺序入库（利用平衡二叉树实现动态查找表的插入），书号（即ISBN）为图书的关键字。初始时，平衡二叉树为空树。

（2）借阅者借阅图书时，先检查借阅者有无超期未归还图书。如果有，则这个借阅者不能借阅。如果没有，则利用平衡二叉树实现动态查找表的查找，找到这本书以后检查这个借阅者是否已经借阅了这种书。如果没有借阅过则可以借这种书，系统接下来登记借阅信息。如果这个借阅者已经借阅了这本书，则系统提示他不能借这种书。

5、选做内容：

（1）实现图书管理的清除库存操作：如果某种书已无保留价值，可将它从系统中删除，即实现平衡二叉树的删除操作。

（2）实现图书管理的显示操作：在每次插入或删除平衡二叉树的一个结点之后，显示平衡二叉树的当前数据。平衡二叉树的显示可采用前面几个实验要求的凹入表或树形打印。

（3）图书管理模拟系统的其它合理功能的实现。

## 项目设计

本次实验实现了基本要求，和选做内容 (1) (2)

首先介绍本次实验的文件结构

~~~
include
 - avltree.h
 - basictype.h
 - libman.h
src
 - avltree.h
 - libman.h
 - main.cpp
~~~

在`basictype.h` 里存放着一些基础的类型，它们是书籍在平衡二叉树的记录类型`book_entry_t` ，借阅者类型`borrower_t` 和类似邻接表的边界点的`info_t` ，它存放着借阅人借阅的书籍信息。



`avltree.h` 和`avltree.cpp` 存放着平衡二叉树类`avl_tree` 

该类的接口如下 :

`void insert(elem_type)` : 向平衡二叉树里插入

`void remove(elem_type)` ：删除平衡二叉树的结点

`void exist(elem_type)` ：测试元素是否存在

`elem_type * pointer(elem_type)` ：返回某元素在平衡二叉树中的指针

`void show_all()` ：以凹入表的方式打印平衡二叉树



`libman.h` 和 `libman.cpp` 中定义了图书馆管理系统类 `libman_system`

`libman_system` 的接口如下:

`void warehouse(book_entry_t)` : 入库

`int borrow(std::string card_no, std::string isbn, std::string deadline)` :借阅

`void Return (std::string card_no, std::string isbn)` :还书

`bool remove(std::string isbn)` : 从库存中删除某本书

`void show_base` : 调用`avl_tree` 类的打印函数



## 总结分析

1. 还书截止日期功能实现如下：

   在每个借阅者的借阅信息中存放一个时间戳，表示截止日期。当借阅人想要借书时，首先使用当前的时间戳比对每一个截止日期的时间戳，检查有无逾期未还的书。

   在用户输入时，使用正则表达式验证输入的日期是否符合格式。

2. 在维护AVL树的时候，没有使用平衡因子来判断旋转，而是直接使用左子树和右子树的高度之差来判断旋转情况，这样会使代码比较简单易懂。

3. AVL树的删除共有四种情况：

   * 要删除的结点为叶子结点，直接删除它，并自下而上调整AVL树。
   * 要删除的结点只有左孩子，用其左孩子替换该节点，并删除其左孩子。因为AVL树的性质，左右子树高度只差不超过1，因此左孩子一定是叶子结点，这种情况便转换为了第一种情况。
   * 要删除的结点只有右孩子，和只有左孩子的情况相同。
   * 要删除的结点既有左孩子，也有右孩子，此时只需寻找其中序遍历的前驱节点或后继结点，用它们替换该结点，在删除它的中序前驱结点或后继结点，而它的中序前驱后后继必定是叶子结点，该情况也转换为了第一种情况。

4. 在处理AVL删除的最后一种情况——既有左孩子也有右孩子时，我遇到了一些问题也有一些思考：

   本次实验，我对于这种情况的处理方法是：用要被删除的结点的中序前驱结点（即要被删除的结点的左子树的最右边的结点）替换该结点，再在该节点的左子树中查找值等于其中序前驱结点的结点，删除它。

   这里真正被删除掉的结点，不一定是要删除结点的中序前驱结点，因为在被删除结点左子树中查找值等于其中序前驱结点的结点时，可能在遇到要删除结点的中序前驱结点之前，就找到了一个和其值相等的结点，提前删除了。

   我起初想要避免这种提前删除的情况，所以我在插入的时候想到，可以让值相同的新插入结点插入到根的左子树中，这样在根的右子树中一定没有和其值相等的结点。

   但后来，我发觉，这种做法只适用于二叉查找树，不适用于AVL树，因为AVL树的旋转会破坏在插入中维护的，根的右子树中一定没有和其值相等的结点，的特性，使得一个根结点的左孩子和右孩子的值都与根节点的值相同。