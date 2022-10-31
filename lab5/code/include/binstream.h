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
        obinstream(const obinstream &) = delete;        // 流应该被拷贝
        obinstream & operator=(obinstream &) = delete;  // 流不应该被拷贝
        ~obinstream();

        obinstream & operator<<(std::string);
        void rewind() {out.clear(); out.seekp(0, std::ios::beg);}
        void open(std::string);
        bool is_open() const {return open_flag;};
        void close();   // 完成写入, 关闭文件流

    private:
        char tochar(int pos) const;

        static const int BufSize = 8192;
        bool open_flag = false;         // 是否打开
        int8_t offset = 0;            // 最后一个字节的有效位字节偏移
        int cursor = 0;               // 游标，指向当前缓冲区的位置
        std::bitset<BufSize> buf;     // 缓冲区
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