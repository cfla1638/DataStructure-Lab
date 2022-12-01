#ifndef H_BASICTYPE
#define H_BASICTYPE

#include <string>
#include <ctime>

class book_entry_t
{
public:
    book_entry_t() = default;
    book_entry_t(std::string para_isbn, std::string para_name, std::string para_author,
    int para_cur_count, int para_total_count) : ISBN(para_isbn), name(para_name),
    author(para_author), cur_count(para_cur_count), total_count(para_total_count) {}

    bool operator>(const book_entry_t &rhs) {return this->ISBN > rhs.ISBN;}
    bool operator<(const book_entry_t &rhs) {return this->ISBN < rhs.ISBN;}
    bool operator>=(const book_entry_t &rhs) {return this->ISBN >= rhs.ISBN;}
    bool operator<=(const book_entry_t &rhs) {return this->ISBN <= rhs.ISBN;}
    bool operator==(const book_entry_t &rhs) {return this->ISBN == rhs.ISBN;}
    bool operator!=(const book_entry_t &rhs) {return this->ISBN != rhs.ISBN;}

    std::string ISBN;       // ISBN
    std::string name;       // ����
    std::string author;     // ����
    int cur_count = 0;      // �ִ�����
    int total_count = 0;    // ����
};

// ������
class borrower_t
{
public:
    std::string card_no;
    info_t * info_set = nullptr;
};

// ������Ϣ���
class info_t
{
public:
    std::string ISBN;
    time_t deadline = 0;
    info_t * next = nullptr;
};

#endif