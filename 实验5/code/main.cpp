#include <iostream>
#include "huffmancoder.h"
using namespace std;
using huffmancoder::HuffmanTree;
using huffmancoder::HuffmanCoder;

int main(void)
{
    HuffmanTree hft(cin);
    hft.display();

    return 0;
}