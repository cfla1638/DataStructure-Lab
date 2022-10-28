#ifndef H_HUFFMANCODER
#define H_HUFFMANCODER

#include <map>
#include <vector>
#include <iostream>

namespace huffmancoder {

    class HuffmanTree
    {
    public:
        // �����Ŀ������ƺ���ʹ�ñ��������ɵİ汾����
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