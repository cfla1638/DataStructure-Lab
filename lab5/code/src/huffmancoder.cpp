#include <iostream>
#include <algorithm>
#include <queue>
#include "heap.h"
#include "binstream.h"
#include "huffmancoder.h"

using binstream::obinstream;
using binstream::ibinstream;

namespace huffmancoder {

    void HuffmanTree::construct_tree()
    {
        // 构造哈夫曼树
        int leafCnt = base.size();
        int nodeCnt = 2 * leafCnt - 1;
        tree_base = new TreeNode[nodeCnt];

        // 初始化优先队列
        auto cmp = [&](int a, int b) {return tree_base[a].weight > tree_base[b].weight;};
        // std::priority_queue<int, std::vector<int>,decltype(cmp)> heap(cmp);
        heap<int, decltype(cmp)> heap(cmp);

        // 初始化叶子节点
        int n = 0;
        for (auto t : base) {
            tree_base[n].ch = t.first;
            tree_base[n].weight = t.second;
            n++;
        }

        // 将所有的叶子节点入优先队列
        for (int i = 0; i < leafCnt; i++)
            heap.push(i);

        // 构造最优树
        for (int i = leafCnt; i < nodeCnt; i++) {
            int t1 = heap.top(); heap.pop();
            int t2 = heap.top(); heap.pop();

            tree_base[t1].parent = tree_base[t2].parent = i;
            tree_base[i].left = t1;
            tree_base[i].right = t2;
            tree_base[i].weight = tree_base[t1].weight + tree_base[t2].weight;
            tree_base[i].ch = '#';

            heap.push(i);
        }
        root = heap.top();  // 存储最优Huffman树的根
        tree_size = nodeCnt;
    }

    HuffmanTree::HuffmanTree(std::vector<char> cvec, std::vector<uint32_t> ivec)
    {
        // 统计权重键值对
        int minLen = (cvec.size() < ivec.size() ? cvec.size() : ivec.size());
        for (int i = 0; i < minLen; i++)
            base.insert(std::pair<char, uint32_t>(cvec[i], ivec[i]));

        construct_tree();
    }

    HuffmanTree::HuffmanTree(std::istream & in)
    {
        char ch;
        while (in.get(ch)) {
            if (base.count(ch) == 0)
                base.insert(std::pair<char, uint32_t>(ch, 1u));
            else
                base[ch]++;
        }

        construct_tree();
    }

    void HuffmanTree::do_display(int tree, int n) const
    {   // 先序遍历，打印打印凹入表
        if (tree != -1) {
            for (int i = 0; i < n; i++)
                std::cout << '*';
            std::cout << tree_base[tree].ch << std::endl;
            do_display(tree_base[tree].left, n + 1);
            do_display(tree_base[tree].right, n + 1); 
        }
    }

    void HuffmanTree::display() const
    {
        if (!tree_base) {
            std::cerr << "HuffmanTree::display() : empty tree!\n" << std::endl;
            return ;
        }
        do_display(root, 0);
    }

    void HuffmanTree::save(std::string filename)
    {
        if (base.empty()) {
            std::cerr << "HuffmanTree::save() : Try to save an empty tree!" << std::endl;
            return ;
        }

        std::ofstream out(filename, std::ios::out | std::ios::binary);

        if (!out) {
            std::cerr << "HuffmanTree::save: failed to open file" << std::endl;
            return ;
        }

        for (auto i : base) {
            out.write(&i.first, 1);
            out.write((char *)(&i.second), 4);
        }
        out.close();
    }

    int HuffmanTree::load(std::string filename)
    {
        std::ifstream in(filename, std::ios::in | std::ios::binary);

        if (!in.is_open()) {
            std::cerr << "HuffmanTree::load: failed to open file" << std::endl;
            return 1;
        }

        base.clear();
        char ch; uint32_t w;
        while (in) {
            in.get(ch);
            in.read((char *)(&w), 4);
            base.insert(std::pair<char, int>(ch, w));
        }
        in.close();

        construct_tree();
        return 0;
    }

    HuffmanTree::HuffmanTree(const HuffmanTree &rhs)
    {
        base = rhs.base;
        root = rhs.root;
        tree_size = rhs.tree_size;
        tree_base = new TreeNode[rhs.tree_size];
        for (int i = 0; i < rhs.tree_size; i++)
            tree_base[i] = rhs.tree_base[i];
    }

    HuffmanTree & HuffmanTree::operator=(const HuffmanTree & rhs)
    {
        if (this == &rhs)   // 处理自赋值
            return *this;
        else {
            base = rhs.base;
            root = rhs.root;
            tree_size = rhs.tree_size;
            tree_base = new TreeNode[rhs.tree_size];
            for (int i = 0; i < rhs.tree_size; i++)
                tree_base[i] = rhs.tree_base[i];
            return *this;
        }
    }

    HuffmanTree::~HuffmanTree()
    {
        delete[] tree_base;
    }

    void HuffmanCoder::construct_encoding_map()
    {
        int leafCnt = Tree.base.size();

        encodingMap.clear();
        for (int i = 0; i < leafCnt; i++) {
            std::string code;
            int cur = i, par = Tree.tree_base[cur].parent;
            while (par != -1) {
                if (Tree.tree_base[par].left == cur)
                    code += '0';
                else
                    code += '1';
                cur = par;
                par = Tree.tree_base[par].parent;
            }
            std::reverse(code.begin(), code.end());
            encodingMap.insert(std::pair<char, std::string>(Tree.tree_base[i].ch, code));
        }
    }

    void HuffmanCoder::set(const HuffmanTree &tree)
    {
        Tree = tree;
        construct_encoding_map();
    }

    HuffmanCoder::HuffmanCoder(const HuffmanTree &tree) : Tree(tree)
    {
        construct_encoding_map();
    }

    void HuffmanCoder::displayEncodingMap() const
    {
        std::cout << "Map size :" << encodingMap.size() << '\n';
        for (auto i : encodingMap)
            std::cout << i.first << " " << i.second << std::endl;
    }

    void HuffmanCoder::encode(std::istream &in, std::ostream &out)
    {
        if (Tree.tree_base == nullptr) {
            std::cerr << "HuffmanCoder::encode() : HuffmanTree empty!" << std::endl;
            return ;
        }

        char buf[BufSize];

        while (true) {
            if (in)
                in.read(buf, BufSize);
            else
                break;
            int size = in.gcount();
            for (int i = 0; i < size; i++)
                out << encodingMap[buf[i]];     // TODO : 处理异常
        }
    }

    void HuffmanCoder::encode(std::istream &in, obinstream & out)
    {
        if (Tree.tree_base == nullptr) {
            std::cerr << "HuffmanCoder::encode() : HuffmanTree empty!" << std::endl;
            return ;
        }

        char buf[BufSize];

        while (true) {
            if (in)
                in.read(buf, BufSize);
            else
                break;
            int size = in.gcount();
            for (int i = 0; i < size; i++)
                out << encodingMap[buf[i]];     // TODO : 处理异常
        }
    }

    void HuffmanCoder::decode(std::istream &in, std::ostream &out)
    {
        if (Tree.tree_base == nullptr) {
            std::cerr << "HuffmanCoder::decode() : HuffmanTree empty!" << std::endl;
            return ;
        }

        char ch;
        int cur = Tree.root;
        while (in >> ch) {
            if (ch == '0')
                cur = Tree.tree_base[cur].left;
            else
                cur = Tree.tree_base[cur].right;
            if (Tree.tree_base[cur].left == -1 && Tree.tree_base[cur].right == -1) {
                out.write(&(Tree.tree_base[cur].ch), 1);
                cur = Tree.root;
            }
        }
    }

    void HuffmanCoder::decode(ibinstream &in, std::ostream &out)
    {
        if (Tree.tree_base == nullptr) {
            std::cerr << "HuffmanCoder::decode() : HuffmanTree empty!" << std::endl;
            return ;
        }

        bool ch;
        int cur = Tree.root;
        while (in.get(ch)) {
            if (!ch)
                cur = Tree.tree_base[cur].left;
            else
                cur = Tree.tree_base[cur].right;
            if (Tree.tree_base[cur].left == -1 && Tree.tree_base[cur].right == -1) {
                out.write(&(Tree.tree_base[cur].ch), 1);
                cur = Tree.root;
            }
        }
    }
}