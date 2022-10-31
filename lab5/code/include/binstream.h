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
        obinstream() = default;
        obinstream(std::string);
        obinstream(const obinstream &) = delete;        // ��Ӧ�ñ�����
        obinstream & operator=(obinstream &) = delete;  // ����Ӧ�ñ�����
        ~obinstream();

        obinstream & operator<<(std::string);
        void rewind() {out.clear(); out.seekp(0, std::ios::beg);}
        void open(std::string);
        bool is_open() const {return open_flag;};
        void close();   // ���д��, �ر��ļ���

    private:
        char tochar(int pos) const;

        static const int BufSize = 8192;
        bool open_flag = false;         // �Ƿ��
        int8_t offset = 0;            // ���һ���ֽڵ���Чλ�ֽ�ƫ��
        int cursor = 0;               // �αָ꣬��ǰ��������λ��
        std::bitset<BufSize> buf;     // ������
        std::ofstream out;
    };

    class ibinstream
    {
    public:
        ibinstream() = default;
        ibinstream(std::string);
        ibinstream(const ibinstream &) = delete;
        ibinstream & operator=(const ibinstream &) = delete;
        ~ibinstream();

        bool get(bool &);
        void open(std::string);
        void close();
        bool is_open() const {return open_flag;}

    private:
        static const int BufSize = 8192;
        char mask[8] = {(char)1, (char)2,
                        (char)4, (char)8, (char)16, 
                        (char)32, (char)64, (char)128};
        int cursor = 0;
        int end = 0;
        int8_t offset = 0;

        bool open_flag = false;
        bool good = true;
        std::ifstream in;
        std::bitset<BufSize> buf;
    };
}

#endif