#include <iostream>
#include <fstream>
#include "huffmancoder.h"
#include "binstream.h"
using namespace std;
using binstream::obinstream;
using binstream::ibinstream;
using huffmancoder::HuffmanTree;
using huffmancoder::HuffmanCoder;

void encode()
{
    cout << endl;
    string input, output;
    cout << "input filename:";
    cin >> input;
    cout << "output filename:";
    cin >> output;

    ifstream in(input, ios::in | ios::binary);
    if (!in) {
        cout << "failed to open input file " << endl;
        return ;
    }
    obinstream out(output);
    HuffmanTree hft(in);
    HuffmanCoder coder(hft);
    in.clear();
    in.seekg(0, ios::beg);
    coder.encode(in, out);
    out.close();
    cout << "successfully encode " << input << " to " << output << endl;
    cout << "save huffmancode ? (y/n) ";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        string savePath;
        cout << "save path:";
        cin >> savePath;
        hft.save(savePath);
    }
}

void decode()
{
    cout << endl;
    string HftFilename, input_filename, decode_output;
    HuffmanTree hft;
    ifstream in;
    ofstream out;

    cout << "input filename to decode:";
    cin >> input_filename;

    cout << "Specify a HuffmanTree? (y/n):";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        cout << "specify huffmantree path:";
        cin >> HftFilename;
        cout << HftFilename << endl;
        hft.load(HftFilename);
    }
    else {
        string ori;
        cout << "ori:";
        cin >> ori;
        in.open(ori, ios::in | ios::binary);
        hft = HuffmanTree(in);
        in.close();
    }

    cout << "start display\n";
    // hft.display();
    cout << "start create coder\n";
    HuffmanCoder coder(hft);
    cout << "create coder ok\n";
    ibinstream ibin(input_filename);
    cout << "decode output filename:";
    cin >> decode_output;
    out.open(decode_output, ios::out | ios::binary);
    coder.decode(ibin, out);
}

int main(void)
{
    while (true) {
        int sel;
        cout << "* encode:0\n* decode:1\n* 2 exit\n" << '>';
        cin >> sel;
        switch (sel)
        {
        case 0:
            encode();
            break;
        case 1:
            decode();
            break;
        case 2 :
            return 0;
        default:
            continue;
        }
        cout << endl;
    }
    return 0;
}

/*
int main(void)
{
    ifstream in("../_io/code.cpp", ios::binary | ios::in);
    obinstream binout("../_io/en_op");
    HuffmanTree hft(in);
    // hft.load("../_io/h");
    HuffmanCoder coder(hft);
    in.clear();
    in.seekg(0, ios::beg);
    coder.encode(in, binout);
    binout.close();
    
    
    ifstream in("../_io/code.cpp", ios::binary | ios::in);
    ofstream out("../_io/de_op", ios::out | ios::binary);
    ibinstream binin("../_io/en_op");
    HuffmanTree hft(in);
    //hft.load("../_io/h");
    HuffmanCoder coder(hft);
    in.clear();
    in.seekg(0, ios::beg);
    coder.decode(binin, out);
}*/