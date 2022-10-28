#ifndef H_HUFFMANCODER
#define H_HUFFMANCODER

#include <map>
#include <vector>
#include <iostream>

namespace huffmancoder {

    class HuffmanTree
    {
    public:
        // 其他的拷贝控制函数使用编译器生成的版本即可
        HuffmanTree() = default;
        HuffmanTree(std::vector<char>, std::vector<int>);
        HuffmanTree(std::istream &);

        void display() const;
        
        std::map<char, int> base;
    };

    class HuffmanCoder
    {

    };
}

#endif