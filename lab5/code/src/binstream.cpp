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
        out << (char)0;     // һ�ֽ�ռλ
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

        offset = cursor - i;    // ��¼���һ���������ֽڵ��ֽ�ƫ��
        
        // �������һ���������ֽ�
        int p = 0;
        while (i < cursor) {
            if (buf[i++])
                ch += (char)pow(2, p);
            p++;
        }
        out << ch;
        // std::cout << (int)tochar(i) << ' ';
        rewind();       // ��λ����ͷ
        out << offset;  // �洢�ֽ�ƫ��
        out.close();
    }

    ibinstream::ibinstream(std::string filename)
    {
        in.open(filename, std::ios::in | std::ios::binary);
        if (in) {
            char ch;
            in >> offset;
        }
        else
            std::cout << "failed to open file\n";
    }

    bool ibinstream::get(bool &bit)
    {
        // �����������û�����ݣ�����������
        if ((cursor >= end) && good) {
            char ch;

            cursor = 0;
            end = 0;
            while (in.get(ch)) {
                for (int i = 0; i < 8; i++)
                    buf[end++] = (ch & mask[i]);
                if (end >= BufSize)
                    break;
            }
            if (end < BufSize) {
                end -= (8 - offset);
                good = false;
            }
        }
        else if ((cursor >= end) && !good)
            return false;
        bit = buf[cursor++];
        return true;
    }
}