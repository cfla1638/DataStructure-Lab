#ifndef H_BASICTYPE
#define H_BASICTYPE

#include <string>
#include <ctime>

class book_entry_t
{
public:
    std::string ISBN;       // ISBN
    std::string name;       // 书名
    std::string author;     // 著者
    int cur_count = 0;      // 现存数量
    int total_count = 0;    // 总数
};

// 借阅人
class borrower_t
{
public:
    std::string card_no;
    info_t * info_set = nullptr;
};

// 借阅信息结点
class info_t
{
public:
    std::string ISBN;
    time_t deadline = 0;
    info_t * next = nullptr;
};

#endif