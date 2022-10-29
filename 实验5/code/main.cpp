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

int main(void)
{
    /*
    ifstream in("content.txt", ios::in | ios::binary);

    HuffmanTree hft(in);
    HuffmanCoder coder(hft);
    coder.displayEncodingMap();
    in.clear();
    in.seekg(0, ios::beg);
    
    coder.encode(in, std::cout);*/
    obinstream s("content.txt");
    s << "00001100";
    cout << s.tochar(0) << endl;
    return 0;
}