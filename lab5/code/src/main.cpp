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
void init();
void encode();
void decode();
void print();
void tree_print();

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
                optional_decode();
                break;
            case 'q':
            case 'Q':
                return 0;
        }
    }
    return 0;
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
    cout << "初始化完成!" << endl;
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
    cout << "编码完成, 已输出至CodeFile.dat" << endl;
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
    cout << "解码完成, 已输出至TextFile.txt" << endl;
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
            cnt = 0;
        }
    }
    cout << endl;
}

void tree_print()
{
    if (tree == nullptr) {
        cout << "树空" << endl;
        return ;
    }
    tree->display();
}

void optional_encode()
{
    cout << endl;
    string input, output;
    cout << "输入编码文件:";
    cin >> input;
    
    ifstream in(input, ios::in | ios::binary);
    if (!in) {
        cout << "不能打开要编码的文件!" << endl;
        return ;
    }

    cout << "把文件输出到:";
    cin >> output;

    obinstream out(output);
    HuffmanTree hft(in);
    HuffmanCoder coder(hft);
    in.clear();
    in.seekg(0, ios::beg);
    coder.encode(in, out);
    out.close();
    cout << "成功将文件 " << input << " 编码，输出到 " << output << endl;
    cout << "是否要保存哈夫曼树 ? (y/n) ";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        string savePath;
        cout << "将此树保存到:";
        cin >> savePath;
        hft.save(savePath);
    }
}

void optional_decode()
{
    cout << endl;
    string HftFilename, input_filename, decode_output;
    HuffmanTree hft;
    ofstream out;

    cout << "请输入解码文件:";
    cin >> input_filename;

    cout << "是否要指定一个哈夫曼树? (y/n):";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        cout << "哈夫曼树的路径:";
        cin >> HftFilename;
        cout << HftFilename << endl;
        hft.load(HftFilename);
    }
    else {
        if (tree != nullptr)
            hft = *(tree);
        else {
            cout << "内存中不存在哈夫曼树,无法解码!" << endl;
            return ;
        }
    }

    HuffmanCoder coder(hft);
    ibinstream ibin(input_filename);
    cout << "将文件解码内容输出到:";
    cin >> decode_output;
    out.open(decode_output, ios::out | ios::binary);
    coder.decode(ibin, out);
    cout << "解码完成！" << endl;
}