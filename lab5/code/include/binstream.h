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
        void close();   // 完成写入, 关闭文件流


        char tochar(int pos) const;
    private:

        static const int BufSize = 8192;
        int8_t offset = 0;            // 最后一个字节的有效位字节偏移
        int cursor = 0;               // 游标，指向当前缓冲区的位置
        std::bitset<BufSize> buf;     // 缓冲区
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