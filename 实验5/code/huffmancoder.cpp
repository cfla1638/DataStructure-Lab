#include "huffmancoder.h"
#include <queue>

namespace huffmancoder {
    HuffmanTree::HuffmanTree(std::vector<char> cvec, std::vector<int> ivec)
    {
        int minLen = (cvec.size() < ivec.size() ? cvec.size() : ivec.size());
        for (int i = 0; i < minLen; i++)
            base.insert(std::pair<char, int>(cvec[i], ivec[i]));
    }

    HuffmanTree::HuffmanTree(std::istream & in)
    {
        char ch;
        while (in >> ch) {
            if (base.count(ch) == 0)
                base.insert(std::pair<char, int>(ch, 1));
            else
                base[ch]++;
        }
    }

    void HuffmanTree::display() const
    {
        std::cout << "Huffman Map Size:" << base.size() << '\n';
        for (auto i : base)
            std::cout << i.first << " " << i.second << std::endl;
    }

    HuffmanCoder::HuffmanCoder(const HuffmanTree &data)
    {
        int leafCnt = data.base.size();
        int nodeCnt = 2 * leafCnt - 1;
        base = new TreeNode[nodeCnt];

        // 初始化优先队列
        auto cmp = [&](int a, int b) {return base[a].weight > base[b].weight;};
        std::priority_queue<int, std::vector<int>,decltype(cmp)> heap(cmp);

        // 初始化叶子节点
        int n = 0;
        for (auto t : data.base) {
            base[n].ch = t.first;
            base[n].weight = t.second;
            n++;
        }

        // 将所有的叶子节点入优先队列
        for (int i = 0; i < leafCnt; i++)
            heap.push(i);

        // 构造最优树
        for (int i = leafCnt; i < nodeCnt; i++) {
            int t1 = heap.top(); heap.pop();
            int t2 = heap.top(); heap.pop();

            base[t1].parent = base[t2].parent = i;
            base[i].left = t1;
            base[i].right = t2;
            base[i].weight = base[t1].weight + base[t2].weight;

            heap.push(i);
        }
        root = heap.top();  // 存储最优Huffman树的根

        // 构造字符映射表
        for (int i = 0; i < leafCnt; i++) {
            std::string code;
            int cur = i, par = base[cur].parent;
            while (par != -1) {
                if (base[par].left == cur)
                    code += '1';
                else
                    code += '0';
                cur = par;
                par = base[par].parent;
            }
            code.reserve();
            encodingMap.insert(std::pair<char, std::string>(base[i].ch, code));
        }

        /* debug
        for (int i = 0; i <nodeCnt; i++) {
            std::cout << base[i].ch << " " << base[i].weight << " "
            << base[i].left << " " <<base[i].right << " " << base[i].parent << '\n';
        }*/
    }

    HuffmanCoder::~HuffmanCoder()
    {
        delete[] base;
    }

    void HuffmanCoder::displayEncodingMap() const
    {
        std::cout << "Map size :" << encodingMap.size() << '\n';
        for (auto i : encodingMap)
            std::cout << i.first << " " << i.second << std::endl;
    }
}