#include <iostream>
#include <fstream>
#include "huffmancoder.h"
#include "binstream.h"
using namespace std;
using binstream::obinstream;
using huffmancoder::HuffmanTree;
using huffmancoder::HuffmanCoder;

// g++ main.cpp huffmancoder.cpp -o prog && prog.exe
// g++ main.cpp binstream.cpp -o prog && prog.exe
// g++ main.cpp binstream.cpp huffmancoder.cpp -o prog && prog.exe

int main(void)
{
    ifstream in("content.txt", ios::in | ios::binary);
    // obinstream out("output.txt");

    HuffmanTree hft({'a', 'b', 'c', 'd', 'e'},{5, 4, 3, 2, 1});
    HuffmanCoder coder(hft);
    coder.displayEncodingMap();
    in.clear();
    in.seekg(0, ios::beg);
    
    coder.decode(in, cout);
    // out.close();
    return 0;
}