#ifndef H_LIBRARY
#define H_LIBRARY
#include "avltree.h"

class libman_system
{
public:
    libman_system();
    libman_system(const libman_system &) = delete;
    libman_system & operator=(const libman_system &) = delete;
    ~libman_system();

    void warehouse(std::string, int);
    void borrow(std::string, std::string, std::string);
    void Rentrn(std::string);
    void Delete(std::string);
private:
    static const int max_count = 512;

    int borrowers_count = 0;
    borrower_t borrowers[max_count];
    avl_tree base;
};


#endif