#include <ctime>
#include <iostream>
#include "libman.h"

namespace {
    /**
     * @brief ���ַ�����ʽ��ʱ��ת��Ϊtime_t
     * @param str ʱ�䣬����20221201194830
     * @return time_t 
     */
    time_t string_to_time_t(const std::string &str)
    {
        tm tm_;                                    // ����tm�ṹ�塣
        int year, month, day, hour, minute, second;// ����ʱ��ĸ���int��ʱ������
        year = atoi((str.substr(0, 4)).c_str());
        month = atoi((str.substr(4, 2)).c_str());
        day = atoi((str.substr(6, 2)).c_str());
        hour = atoi((str.substr(8, 2)).c_str());
        minute = atoi((str.substr(10, 2)).c_str());
        second = atoi((str.substr(12, 2)).c_str());

        tm_.tm_year = year - 1900;                 // �꣬����tm�ṹ��洢���Ǵ�1900�꿪ʼ��ʱ�䣬����tm_yearΪint��ʱ������ȥ1900��      
        tm_.tm_mon = month - 1;                    // �£�����tm�ṹ����·ݴ洢��ΧΪ0-11������tm_monΪint��ʱ������ȥ1��
        tm_.tm_mday = day;                         // �ա�
        tm_.tm_hour = hour;                        // ʱ��
        tm_.tm_min = minute;                       // �֡�
        tm_.tm_sec = second;                       // �롣
        tm_.tm_isdst = 0;                          // ������ʱ��
        time_t t_ = mktime(&tm_);                  // ��tm�ṹ��ת����time_t��ʽ��
        return t_;                                 // ����ֵ��
    }
}

libman_system::~libman_system()
{
    for (int i = 0; i < borrowers_count; i++)
        if (borrowers[i].info_set != nullptr)
            for (auto t = borrowers[i].info_set; t != nullptr; ) {
                auto tmp = t;
                t = t->next;
                delete tmp;
            }
}

void libman_system::warehouse(book_entry_t newbook)
{
    if (base.exist(newbook)) {
        auto p = base.pointer(newbook);
        p->cur_count++;
        p->total_count++;
    }
    else
        base.insert(newbook);
}

int libman_system::borrow(std::string borrower_card_no, std::string isbn, std::string deadline)
{
    int pos;
    for (pos = 0; pos < borrowers_count; pos++)
        if (borrowers[pos].card_no == borrower_card_no)
            break;
    if (pos >= borrowers_count) {     // ֮ǰ��δ�����
        borrowers[pos].card_no = borrower_card_no;
        borrowers_count++;

        book_entry_t * book;
        if (base.exist(book_entry_t(isbn))) {
            book = base.pointer(book_entry_t(isbn));
            if (book->cur_count <= 0) {
                std::cout << "Ҫ���ĵ��鼮��ȫ�����!" << std::endl;
                return 1;
            }
        }
        else {
            std::cout << "�Ҳ���Ҫ���ĵ��鼮!" << std::endl;
            return 1;
        }
        info_t * t = new info_t();
        t->ISBN = isbn;
        t->deadline = string_to_time_t(deadline);
        book->cur_count--;
        borrowers[pos].info_set = t;
    }
    else {  // ֮ǰ�����
        for (auto i = borrowers[pos].info_set; i != nullptr; i = i->next) {
            auto cur_time = time(nullptr);
            if (i->deadline < cur_time) {
                std::cout << "�г���δ�����鼮!" << std::endl;
                return 1;
            }
            if (i->ISBN == isbn) {
                std::cout << "�Ѿ����Ĺ����鼮!" << std::endl;
                return 1;
            }
        }

        book_entry_t * book;
        if (base.exist(book_entry_t(isbn))) {
            book = base.pointer(book_entry_t(isbn));
            if (book->cur_count <= 0) {
            std::cout << "Ҫ���ĵ��鼮��ȫ�����!" << std::endl;
            return 1;
            }
        }
        else {
        std::cout << "�Ҳ���Ҫ���ĵ��鼮!" << std::endl;
            return 1;
        }

        info_t * t = new info_t();
        t->ISBN = isbn;
        t->deadline = string_to_time_t(deadline);
        auto tmp = borrowers[pos].info_set;
        borrowers[pos].info_set = t;
        t->next = tmp;
        book->cur_count--;
        
    }
    return 0;
}

void libman_system::Rentrn(std::string borrower, std::string isbn)
{
    int pos;
    for (pos = 0; pos < borrowers_count; pos++)
        if (borrowers[pos].card_no == borrower)
            break;
    if (pos >= borrowers_count) {
        std::cout << "����֤�� " << borrower << " ������!" << std::endl;
        return ;
    }

    bool flag = 0;
    info_t * t = borrowers[pos].info_set, * pre = nullptr;
    while (t != nullptr) {
        if (t->ISBN == isbn) {
            if (pre == nullptr) {
                auto tmp = t;
                borrowers[pos].info_set = t->next;
                delete t;
                flag = 1;
                base.pointer(book_entry_t(isbn))->cur_count++;
                break;
            }
            else {
                auto tmp = t;
                pre->next = t->next;
                delete t;
                flag = 1;
                base.pointer(book_entry_t(isbn))->cur_count++;
                break;
            }
        }
        pre = t;
        t = t->next;
    }
    if (!flag)
        std::cout << "����֤��" << borrower << "δ���� ISBN:" << isbn << std::endl;
    else
        std::cout << "����֤��" << borrower << "�ɹ��黹 ISBN:" << isbn << std::endl;
    return ; 
}

bool libman_system::remove(std::string isbn)
{
    return base.remove(book_entry_t(isbn));
}

void libman_system::show_base()
{
    base.show_all();
}
