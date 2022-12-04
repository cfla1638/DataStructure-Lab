#include <ctime>
#include <iostream>
#include "libman.h"

namespace {
    /**
     * @brief 将字符串格式的时间转换为time_t
     * @param str 时间，例：20221201194830
     * @return time_t 
     */
    time_t string_to_time_t(const std::string &str)
    {
        tm tm_;                                    // 定义tm结构体。
        int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
        year = atoi((str.substr(0, 4)).c_str());
        month = atoi((str.substr(4, 2)).c_str());
        day = atoi((str.substr(6, 2)).c_str());
        hour = atoi((str.substr(8, 2)).c_str());
        minute = atoi((str.substr(10, 2)).c_str());
        second = atoi((str.substr(12, 2)).c_str());

        tm_.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。      
        tm_.tm_mon = month - 1;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
        tm_.tm_mday = day;                         // 日。
        tm_.tm_hour = hour;                        // 时。
        tm_.tm_min = minute;                       // 分。
        tm_.tm_sec = second;                       // 秒。
        tm_.tm_isdst = 0;                          // 非夏令时。
        time_t t_ = mktime(&tm_);                  // 将tm结构体转换成time_t格式。
        return t_;                                 // 返回值。
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
    if (pos >= borrowers_count) {     // 之前并未借过书
        borrowers[pos].card_no = borrower_card_no;
        borrowers_count++;

        book_entry_t * book;
        if (base.exist(book_entry_t(isbn))) {
            book = base.pointer(book_entry_t(isbn));
            if (book->cur_count <= 0) {
                std::cout << "要借阅的书籍已全部借出!" << std::endl;
                return 1;
            }
        }
        else {
            std::cout << "找不到要借阅的书籍!" << std::endl;
            return 1;
        }
        info_t * t = new info_t();
        t->ISBN = isbn;
        t->deadline = string_to_time_t(deadline);
        book->cur_count--;
        borrowers[pos].info_set = t;
    }
    else {  // 之前借过书
        for (auto i = borrowers[pos].info_set; i != nullptr; i = i->next) {
            auto cur_time = time(nullptr);
            if (i->deadline < cur_time) {
                std::cout << "有超期未还的书籍!" << std::endl;
                return 1;
            }
            if (i->ISBN == isbn) {
                std::cout << "已经借阅过该书籍!" << std::endl;
                return 1;
            }
        }

        book_entry_t * book;
        if (base.exist(book_entry_t(isbn))) {
            book = base.pointer(book_entry_t(isbn));
            if (book->cur_count <= 0) {
            std::cout << "要借阅的书籍已全部借出!" << std::endl;
            return 1;
            }
        }
        else {
        std::cout << "找不到要借阅的书籍!" << std::endl;
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
        std::cout << "借阅证号 " << borrower << " 不存在!" << std::endl;
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
        std::cout << "借阅证号" << borrower << "未借阅 ISBN:" << isbn << std::endl;
    else
        std::cout << "借阅证号" << borrower << "成功归还 ISBN:" << isbn << std::endl;
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
