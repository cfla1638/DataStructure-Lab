#include <iostream>
#include "huffmancoder.h"
using namespace std;
using huffmancoder::HuffmanTree;
using huffmancoder::HuffmanCoder;

// g++ main.cpp huffmancoder.cpp -o prog && prog.exe

int main(void)
{
    HuffmanTree hft(cin);
    hft.display();
    HuffmanCoder coder(hft);
    coder.displayEncodingMap();
    return 0;
}