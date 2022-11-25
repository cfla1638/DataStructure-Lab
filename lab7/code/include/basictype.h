#ifndef H_BASICTYPE
#define H_BASICTYPE

#include <string>
#include <ctime>

class book_entry_t
{
public:
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