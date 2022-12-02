#include <iostream>
#include <ctime>
#include <avltree.h>
#include "libman.h"
using namespace std;

int main(void)
{
    // time_t cur_time = time(nullptr);
    // cout << cur_time << endl;
    // tm * t = localtime(&cur_time);
    // cout << 1900 + t->tm_year << " " << 1 + t->tm_mon << " " << t->tm_mday << " "  
    // << t->tm_hour << " " << t->tm_min << " " << t->tm_sec << endl;
    // // cout << mytime::string_to_time_t("20221125213217") << endl;

    libman_system sys;
    sys.warehouse(book_entry_t("9787302455882", "", "", 10, 10));
    sys.warehouse(book_entry_t("9787302386346", "", "", 10, 10));
    sys.warehouse(book_entry_t("9787302033141", "", "", 10, 10));
    sys.warehouse(book_entry_t("9787111540090", "", "", 10, 10));
    sys.warehouse(book_entry_t("9787121337826", "", "", 10, 10));
    sys.warehouse(book_entry_t("9787302330646", "", "", 10, 10));
    sys.warehouse(book_entry_t("9787302330653", "", "", 10, 10));
    sys.borrow("123", "9787302330653", "20221202230800");
    sys.borrow("123", "9787302330653", "20221202230100");

    return 0;
}