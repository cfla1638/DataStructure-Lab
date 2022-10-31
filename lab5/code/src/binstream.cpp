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

    obinstream::obinstream(std::string filename) : open_flag(false)
    {
        out.open(filename, std::ios::out | std::ios::binary);
        if (!out.is_open())
            std::cerr << "obinstream::constructor : fail to open file!" << std::endl;
        else {
            out << (char)0;     // һ�ֽ�ռλ
            open_flag = true;
        }
    }

    obinstream & obinstream::operator<<(std::string str)
    {
        int len = str.size();
        
        // �����ַ��� 
        for (int i = 0; i < len; ) {
            // ��������δ����������������
            if (cursor < BufSize) {
                if (str[i] == '1') buf.set(cursor++, true);
                else if (str[i] == '0') buf.set(cursor++, false);
                i++;    // i++ һ��Ҫд�����λ��!!!
            }
            else {  // ����������, ���ļ���д�������ֽ�
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

        // ���������һ�����ܲ��������ֽ�������ֽ�д���ļ�
        for (i = 0; i < nbyte * 8; i += 8)
            out << tochar(i);

        offset = cursor - i;    // ��¼���һ���������ֽڵ��ֽ�ƫ��
        
        // �������һ���������ֽ�
        int p = 0;
        while (i < cursor) {
            if (buf[i++])
                ch += (char)pow(2, p);
            p++;
        }
        out << ch;      // д�����һ���������ֽ�

        rewind();       // ��λ����ͷ
        out << offset;  // �洢�ֽ�ƫ��

        // �ر��ļ���
        out.close();
        open_flag = false;
        out.clear();    // �����״̬���Ա��´�ʹ��
    }

    obinstream::~obinstream()
    {
        if (out.is_open()) {
            out.close();
            open_flag = false;
        }
    }

    void obinstream::open(std::string filename)
    {
        if (open_flag) {
            std::cerr << "obinstream::open() : Cannot open an already open stream" << std::endl;
            return ;
        }
        out.open(filename, std::ios::out | std::ios::binary);
        if (!out.is_open())
            std::cerr << "obinstream::open() : fail to open file!" << std::endl;
        else {
            out << (char)0;     // һ�ֽ�ռλ
            open_flag = true;
        }
    }

    ibinstream::ibinstream(std::string filename) : open_flag(false)
    {
        in.open(filename, std::ios::in | std::ios::binary);
        if (in.is_open()) {
            in >> offset;
            open_flag = true;
        }
        else
            std::cout << "ibinstream::constructer: fail to open file" << std::endl;
    }

    ibinstream::~ibinstream()
    {
        if (in.is_open()) {
            in.close();
            open_flag = false;
        }
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

    void ibinstream::open(std::string filename)
    {
        if (open_flag) {
            std::cerr << "ibinstream::open() : Cannot open an already open stream" << std::endl;
            return ;
        }
        in.open(filename, std::ios::in | std::ios::binary);
        if (in.is_open()) {
            in >> offset;
            open_flag = true;
        }
        else
            std::cout << "ibinstream::constructer: fail to open file" << std::endl;
    }

    void ibinstream::close()
    {
        in.close();
        in.clear();
        open_flag = false;
    }
}