#ifndef H_HUFFMANCODER
#define H_HUFFMANCODER

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <stdint.h>

#include "binstream.h"
using binstream::obinstream;
using binstream::ibinstream;

class TreeNode
{
public:
    uint32_t weight = 0u;
    int parent = -1, left = -1, right = -1;
    char ch = 0;
};

namespace huffmancoder {

    class HuffmanTree
    {
        friend class HuffmanCoder;
        
    public:
        HuffmanTree() = default;
        HuffmanTree(std::vector<char>, std::vector<uint32_t>);
        HuffmanTree(std::istream &);

        HuffmanTree(const HuffmanTree &);
        HuffmanTree & operator=(const HuffmanTree &);
        ~HuffmanTree();

        void display() const;
        int load(std::string);
        void save(std::string);
    
    private:
        void construct_tree();
        void do_display(int, int) const;

        std::map<char, uint32_t> base;

        int root = -1;
        int tree_size = 0;
        TreeNode * tree_base = nullptr;
    };

    class HuffmanCoder
    {
    public:
        HuffmanCoder() = default;
        HuffmanCoder(const HuffmanTree &);

        void displayEncodingMap() const;
        void set(const HuffmanTree &);
        void encode(std::istream &, std::ostream &);
        void encode(std::istream &, obinstream &);
        void decode(std::istream &, std::ostream &);
        void decode(ibinstream &, std::ostream &);
    private:
        void construct_encoding_map();

        static const int BufSize = 1024;
        HuffmanTree Tree;
        std::map<char, std::string> encodingMap;
    };
}

#endif