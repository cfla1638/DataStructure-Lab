#ifndef H_BINSTREAM
#define H_BINSTREAM

#include <stdint.h>
#include <bitset>
#include <string>
#include <fstream>

namespace binstream {

    class obinstream
    {
    public:
        obinstream(std::string);
        obinstream & operator<<(std::string);
        void rewind() {out.clear(); out.seekp(0, std::ios::beg);}
        void close();   // ���д��, �ر��ļ���


        char tochar(int pos) const;
    private:

        static const int BufSize = 8192;
        int8_t offset = 0;            // ���һ���ֽڵ���Чλ�ֽ�ƫ��
        int cursor = 0;               // �αָ꣬��ǰ��������λ��
        std::bitset<BufSize> buf;     // ������
        std::ofstream out;
    };

    class ibinstream
    {
    public:
        ibinstream(std::string);
    private:
        
    };
}

#endif