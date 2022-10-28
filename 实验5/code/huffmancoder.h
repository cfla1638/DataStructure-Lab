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

        void displayEncodingMap() const;
        void encode(std::istream &, std::ostream &);
        void decode(std::istream &, std::ostream &);
    private:
        static const int BufSize = 1024;

        int root = -1;
        TreeNode * base;
        std::map<char, std::string> encodingMap;
    };

    // Beta : ����ֱ�Ӽ̳�ostream, �����ǵ���׼�����û�����������������ֻ�ܷ���
    class obinstream
    {
    public:
        obinstream(std::string);
        obinstream & operator<<(std::string);
        void rewind() {out.clear(); out.seekp(0, std::ios::beg);}
        void close();   // ���д��, �ر��ļ���
    private:
        // TODO : ���һ��64λ��������ʾ�Ѿ�����˶����ֽ�
        int cursor = 0;     // �αָ꣬��ǰ��������λ��
        bitset<64> buf;     // ������
        std::ofstream out;
    };
}

#endif