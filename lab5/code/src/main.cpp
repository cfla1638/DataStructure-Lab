#include <iostream>
#include <fstream>
#include "binstream.h"
#include "huffmancoder.h"
using namespace std;
using binstream::obinstream;
using binstream::ibinstream;
using huffmancoder::HuffmanTree;
using huffmancoder::HuffmanCoder;

HuffmanTree * tree = nullptr;
HuffmanCoder * coder = nullptr;

void menu();
void encode();
void decode();
void print();
void tree_print();
void init();

void optional_encode();
void optional_decode();

int main(void)
{  
    while (true) {
        char ch;
        menu();
        cin >> ch;
        getchar();
        switch (ch) {
            case 'i':
            case 'I':
                init();
                break;
            case 'e':
            case 'E':
                encode();
                break;
            case 'd':
            case 'D':
                decode();
                break;
            case 'p':
            case 'P':
                print();
                break;
            case 't':
            case 'T':
                tree_print();
                break;
            case '1':
                optional_encode();
                break;
            case '2':
                optional_encode();
                break;
            case 'q':
            case 'Q':
                return 0;
        }
    }
    return 0;
}

void tree_print()
{
    if (tree == nullptr) {
        cout << "树空" << endl;
        return ;
    }
    tree->display();
}

void print()
{
    ibinstream in("Codefile.dat");
    if (!in.is_open())
        return ;
    ofstream out("CodePrint.txt", ios::out);
    if (!out.is_open()) {
        cout << "不能打开 : CodePrint.txt";
        return ;
    }
    
    int cnt = 0;
    bool bit;
    while (in.get(bit)) {
        if (bit) {
            cout << '1';
            out << '1';
        }
        else {
            cout << '0';
            out << '0';
        }
        cnt++;
        if (cnt == 50) {
            cout << '\n';
            out << '\n';
        }
    }
    cout << endl;
}

void decode()
{
    if (coder == nullptr) {
        if (tree == nullptr) {
            if (tree->load("hfmTree.txt"))
                return ;
        }
        coder = new HuffmanCoder(*tree);
    }
    ibinstream in("CodeFile.dat");
    if (!in.is_open()) 
        return ;
    ofstream out("TextFile.txt", ios::out | ios::binary);
    if (!out.is_open()) {
        cout << "不能打开 : TextFile.txt" << endl;
        return ;
    }
    coder->decode(in, out);
    in.close();
    out.close();
}

void encode()
{
    if (tree == nullptr) {
        if (tree->load("hfmTree.txt"))
        return ;
    }
    coder = new HuffmanCoder(*tree);

    ifstream in("ToBeTranslated.txt", ios::in | ios::binary);
    if (!in.is_open()) {
        cout << "不能打开 : ToBeTranslated.txt" << endl;
        return ;
    }
    obinstream out("CodeFile.dat");
    if (!out.is_open()) 
        return ;
    coder->encode(in, out);
    out.close();
    in.close();
}

void init()
{
    cout << endl;

    int n;
    
    vector<char> chvec;
    vector<uint32_t> wvec;
    cout << "请输入字符个数:";
    cin >> n;
    getchar();
    cout << "请输入" << n << "个字符:" << endl;
    for (int i = 0; i < n; i++) {
        int ch;
        ch = getchar();
        chvec.push_back(ch);
    }
    cout << "请输入字符的权重:" << endl;
    for (int i = 0; i < n; i++) {
        int w;
        cin >> w;
        wvec.push_back(w);
    }
    tree = new HuffmanTree(chvec, wvec);
    tree->save("hfmTree.txt");
}

void menu()
{
    cout << "哈夫曼树 编解码器" << endl;
    cout << " * I : 初始化" << endl;
    cout << " * E : 编码" << endl;
    cout << " * D : 解码" << endl;
    cout << " * P : 输出代码文件" << endl;
    cout << " * T : 输出哈夫曼树(凹入表)" << endl;
    cout << " * 1 : 自定义编码" << endl;
    cout << " * 2 : 自定义解码" << endl;
    cout << " * Q : 退出" << endl;
    cout << ">";
}

void optional_encode()
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

void optional_decode()
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