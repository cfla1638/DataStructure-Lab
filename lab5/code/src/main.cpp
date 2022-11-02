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
    cout << "�������� �������" << endl;
    cout << " * I : ��ʼ��" << endl;
    cout << " * E : ����" << endl;
    cout << " * D : ����" << endl;
    cout << " * P : ��������ļ�" << endl;
    cout << " * T : �����������(�����)" << endl;
    cout << " * 1 : �Զ������" << endl;
    cout << " * 2 : �Զ������" << endl;
    cout << " * Q : �˳�" << endl;
    cout << ">";
}

void init()
{
    cout << endl;

    int n;
    
    vector<char> chvec;
    vector<uint32_t> wvec;
    cout << "�������ַ�����:";
    cin >> n;
    getchar();
    cout << "������" << n << "���ַ�:" << endl;
    for (int i = 0; i < n; i++) {
        int ch;
        ch = getchar();
        chvec.push_back(ch);
    }
    cout << "�������ַ���Ȩ��:" << endl;
    for (int i = 0; i < n; i++) {
        int w;
        cin >> w;
        wvec.push_back(w);
    }
    tree = new HuffmanTree(chvec, wvec);
    tree->save("hfmTree.txt");
    cout << "��ʼ�����!" << endl;
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
        cout << "���ܴ� : ToBeTranslated.txt" << endl;
        return ;
    }
    obinstream out("CodeFile.dat");
    if (!out.is_open()) 
        return ;
    coder->encode(in, out);
    out.close();
    in.close();
    cout << "�������, �������CodeFile.dat" << endl;
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
        cout << "���ܴ� : TextFile.txt" << endl;
        return ;
    }
    coder->decode(in, out);
    in.close();
    out.close();
    cout << "�������, �������TextFile.txt" << endl;
}

void print()
{
    ibinstream in("Codefile.dat");
    if (!in.is_open())
        return ;
    ofstream out("CodePrint.txt", ios::out);
    if (!out.is_open()) {
        cout << "���ܴ� : CodePrint.txt";
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
        cout << "����" << endl;
        return ;
    }
    tree->display();
}

void optional_encode()
{
    cout << endl;
    string input, output;
    cout << "��������ļ�:";
    cin >> input;
    
    ifstream in(input, ios::in | ios::binary);
    if (!in) {
        cout << "���ܴ�Ҫ������ļ�!" << endl;
        return ;
    }

    cout << "���ļ������:";
    cin >> output;

    obinstream out(output);
    HuffmanTree hft(in);
    HuffmanCoder coder(hft);
    in.clear();
    in.seekg(0, ios::beg);
    coder.encode(in, out);
    out.close();
    cout << "�ɹ����ļ� " << input << " ���룬����� " << output << endl;
    cout << "�Ƿ�Ҫ����������� ? (y/n) ";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        string savePath;
        cout << "���������浽:";
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

    cout << "����������ļ�:";
    cin >> input_filename;

    cout << "�Ƿ�Ҫָ��һ����������? (y/n):";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        cout << "����������·��:";
        cin >> HftFilename;
        cout << HftFilename << endl;
        hft.load(HftFilename);
    }
    else {
        if (tree != nullptr)
            hft = *(tree);
        else {
            cout << "�ڴ��в����ڹ�������,�޷�����!" << endl;
            return ;
        }
    }

    HuffmanCoder coder(hft);
    ibinstream ibin(input_filename);
    cout << "���ļ��������������:";
    cin >> decode_output;
    out.open(decode_output, ios::out | ios::binary);
    coder.decode(ibin, out);
    cout << "������ɣ�" << endl;
}