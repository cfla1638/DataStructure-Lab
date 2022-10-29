#include <iostream>
#include <fstream>
#include "huffmancoder.h"
#include "binstream.h"
using namespace std;
using binstream::obinstream;
using binstream::ibinstream;
using huffmancoder::HuffmanTree;
using huffmancoder::HuffmanCoder;

// g++ main.cpp huffmancoder.cpp -o prog && prog.exe
// g++ main.cpp binstream.cpp -o prog && prog.exe
// g++ main.cpp binstream.cpp huffmancoder.cpp -o prog && prog.exe

int main(void)
{
    ifstream in("../src/main.cpp", ios::in | ios::binary);
    // ofstream out("../_io/decode_output.txt", ios::out | ios::binary);
    // ibinstream binin("../_io/output.txt");
    obinstream binout("../_io/output.txt");

    HuffmanTree hft(in);
    HuffmanCoder coder(hft);
    coder.displayEncodingMap();
    in.clear();
    in.seekg(0, ios::beg);
    
    coder.encode(in, binout);
    // coder.decode(binin, out);
    binout.close();

    return 0;
}