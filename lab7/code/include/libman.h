#ifndef H_LIBRARY
#define H_LIBRARY
#include "avltree.h"

class libman_system
{
public:
    libman_system();
    libman_system(std::string filename);
    libman_system(const libman_system &) = delete;
    libman_system & operator=(const libman_system &) = delete;
    ~libman_system();

    void warehouse(book_entry_t);                       // 入库
    int borrow(std::string, std::string, std::string);     // 借阅
    void Rentrn(std::string, std::string);                               // 还书
    void remove(std::string);                               // 清除库存
    void show_base();
private:
    static const int max_count = 512;   // 最大借书人数

    int borrowers_count = 0;            // 当前借过书的人
    borrower_t borrowers[max_count];
    avl_tree base;                      // 库存
};


#endif