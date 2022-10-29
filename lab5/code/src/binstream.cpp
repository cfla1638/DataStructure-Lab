#include "binstream.h"

#include <cmath>
#include <iostream>

namespace binstream {
    char obinstream::tochar(int pos) const
    {
        char ch = 0;
        for (int i = 0; i < 8; i++)
            if (buf[pos + i])
                ch += (char)pow(2, i);
        return ch;
    }

    obinstream::obinstream(std::string filename)
    {
        out.open(filename, std::ios::out | std::ios::binary);
        out << (char)0;     // 一字节占位
    }

    obinstream & obinstream::operator<<(std::string str)
    {
        int len = str.size();
        // std::cout << str << " ";
        for (int i = 0; i < len; i++) {
            if (cursor < BufSize) {
                if (str[i] == '1') buf.set(cursor++, true);
                else if (str[i] == '0') buf.set(cursor++, false);
            }
            else {
                for (int j = 0; j < BufSize; j += 8)
                    out << tochar(j);
                cursor = 0;
            }
        }
        return *this;
    }

    void obinstream::close()
    {
        int i, nbyte = cursor / 8;
        char ch = 0;

        // std::cout << cursor;

        for (i = 0; i < nbyte * 8; i += 8)
            out << tochar(i);
            // std::cout << (int)tochar(i) << ' ';

        offset = cursor - i;    // 记录最后一个不完整字节的字节偏移
        
        // 处理最后一个不完整字节
        int p = 0;
        while (i < cursor) {
            if (buf[i++])
                ch += (char)pow(2, p);
            p++;
        }
        out << ch;
        // std::cout << (int)tochar(i) << ' ';
        rewind();       // 定位到开头
        out << offset;  // 存储字节偏移
        out.close();
    }
}