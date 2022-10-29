#include "binstream.h"

#include <cmath>

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
    }

    obinstream & obinstream::operator<<(std::string str)
    {
        int len = str.size();
        for (int i = 0; i < len; i++) {
            if (cursor < BufSize) {
                if (str[i] == '1') buf.set(cursor++, true);
                else if (str[i] == '0') buf.set(cursor++, false);
            }
            else {
                for (int j = 0; j < BufSize; j += 8)
                    out << tochar(j);
            }
        }
    }
}