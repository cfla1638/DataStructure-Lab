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
    obinstream out("output.txt");

    HuffmanTree hft(in);
    HuffmanCoder coder(hft);
    coder.displayEncodingMap();
    in.clear();
    in.seekg(0, ios::beg);
    
    coder.encode(in, out);
    out.close();

    /*
    obinstream s("content.txt");
    s << "10001100";
    cout << s.tochar(0) << endl;*/
    return 0;
}