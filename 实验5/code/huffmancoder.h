#ifndef H_HUFFMANCODER
#define H_HUFFMANCODER

#include <map>
#include <bitset>
#include <vector>
#include <string>
#include <fstream>

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
        // 其他的拷贝控制函数使用编译器生成的版本即可
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
        HuffmanCoder(const HuffmanCoder &);     // 拷贝构造函数
        ~HuffmanCoder();

        void displayEncodingMap() const;
        void encode(std::istream &, std::ostream &);
        void decode(std::istream &, std::ostream &);
    private:
        static const int BufSize = 1024;

        int root = -1;
        TreeNode * base;
        std::map<char, std::string> encodingMap;
    };

    // Beta : 本想直接继承ostream, 但考虑到标准库可能没有虚析构函数，因此只能放弃
    class obinstream
    {
    public:
        obinstream(std::string);
        obinstream & operator<<(std::string);
        void rewind() {out.clear(); out.seekp(0, std::ios::beg);}
        void close();   // 完成写入, 关闭文件流
    private:
        // TODO : 添加一个64位的整数表示已经输出了多少字节
        int cursor = 0;     // 游标，指向当前缓冲区的位置
        bitset<64> buf;     // 缓冲区
        std::ofstream out;
    };
}

#endif