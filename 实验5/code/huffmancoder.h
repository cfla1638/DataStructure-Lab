#ifndef H_HUFFMANCODER
#define H_HUFFMANCODER

#include <map>
#include <vector>
#include <string>
#include <iostream>

class TreeNode
{
public:
    int weight = 0;
    int parent = -1, left = -1, right = -1;
    char ch = 0;
};

namespace huffmancoder {

    class HuffmanTree
    {
        friend class HuffmanCoder;
    public:
        // �����Ŀ������ƺ���ʹ�ñ��������ɵİ汾����
        HuffmanTree() = default;
        HuffmanTree(std::vector<char>, std::vector<int>);
        HuffmanTree(std::istream &);

        void display() const;
    
    private:
        std::map<char, int> base;
    };

    class HuffmanCoder
    {
    public:
        HuffmanCoder(const HuffmanTree &);
        HuffmanCoder(const HuffmanCoder &);     // �������캯��
        ~HuffmanCoder();

        void encode(std::istream &, std::ostream &);
        void decode(std::istream &, std::ostream &);
    private:
        void constructEncodingMap(int root);    // �ݹ�������������ӳ��

        int root = -1;
        TreeNode * base;
        std::map<char, std::string> encodingMap;
    };
}

#endif