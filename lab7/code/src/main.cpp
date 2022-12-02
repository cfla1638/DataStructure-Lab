#include <iostream>
#include <ctime>
#include <avltree.h>
using namespace std;

int main(void)
{
    // time_t cur_time = 1669383137;
    // cout << cur_time << endl;
    // tm * t = localtime(&cur_time);
    // cout << 1900 + t->tm_year << " " << 1 + t->tm_mon << " " << t->tm_mday << " "  
    // << t->tm_hour << " " << t->tm_min << " " << t->tm_sec << endl;
    // cout << mytime::string_to_time_t("20221125213217") << endl;

    avl_tree Tree;
    Tree.insert(book_entry_t("1"));
    Tree.insert(book_entry_t("2"));
    Tree.insert(book_entry_t("3"));
    Tree.insert(book_entry_t("4"));
    Tree.insert(book_entry_t("5"));
    Tree.show_all();
    cout << "-----------------\n";
    Tree.remove(book_entry_t("2"));
    Tree.show_all();
}