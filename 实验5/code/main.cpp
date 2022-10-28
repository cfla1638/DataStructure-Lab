#include <iostream>
#include <fstream>
#include "huffmancoder.h"
using namespace std;
using huffmancoder::HuffmanTree;
using huffmancoder::HuffmanCoder;

// g++ main.cpp huffmancoder.cpp -o prog && prog.exe

int main(void)
{
    ifstream in("content.txt", ios::in | ios::binary);

    HuffmanTree hft(in);
    HuffmanCoder coder(hft);
    coder.displayEncodingMap();
    in.clear();
    in.seekg(0, ios::beg);
    
    coder.encode(in, std::cout);
    return 0;
}