#include <iostream>
#include <regex>
#include "libman.h"
using namespace std;

void menu();    // 打印菜单

int main(void)
{
    // 初始化管理系统，并提前插入数据
    libman_system sys;
    sys.warehouse(book_entry_t("9787302455882", "", "", 1, 1));
    sys.warehouse(book_entry_t("9787302386346", "", "", 1, 1));
    sys.warehouse(book_entry_t("9787302033141", "", "", 1, 1));
    sys.warehouse(book_entry_t("9787111540090", "", "", 1, 1));
    sys.warehouse(book_entry_t("9787121337826", "", "", 1, 1));
    sys.warehouse(book_entry_t("9787302330646", "", "", 1, 1));
    sys.warehouse(book_entry_t("9787302330653", "", "", 1, 1));

    int opt;
    string card_no, author, name, isbn, date, pattern("(\\d{4})[-/](1[0,1,2]|0?\\d)[-/](3[0,1]|[1,2]\\d|0?\\d)");
    regex r(pattern);   // 验证输入日期的正则表达式
    while (true) {
        menu();
        cin >> opt;
        switch (opt)
        {
        case 0:
            cout << "请输入借阅证号:";
            cin >> card_no;
            cout << "请输入借阅书籍的ISBN:";
            cin >> isbn;
            cout << "请输入归还日期(yyyy-mm-dd):";
            cin >> date;
            while (!regex_match(date, r)) {
                cout << "日期格式有误, 请重新输入!" << endl << "请输入归还日期(yyyy-mm-dd):";
                cin >> date;
            }
            if (date.length() == 9) {
                if (date[6] == '-')
                    date.insert(5, 1, '0');
                else
                    date.insert(8, 1, '0');
            }
            else if (date.length() == 8) {
                date.insert(5, 1, '0');
                date.insert(8, 1, '0');
            }
            date.erase(4, 1);
            date.erase(6, 1);
            date += "000000";
            if (!sys.borrow(card_no, isbn, date))
                cout << "借阅成功!" << endl; 
            break;
        case 1:
            cout << "请输入借阅证号:";
            cin >> card_no;
            cout << "请输入归还书籍的ISBN:";
            cin >> isbn;
            sys.Rentrn(card_no, isbn);
            break;
        case 2:
            cout << "请输入书籍的ISBN:";
            cin >> isbn;
            cout << "请输入书名:";
            cin >> name;
            cout << "请输入书籍的著者:";
            cin >> author;
            sys.warehouse(book_entry_t(isbn, name, author, 1, 1));
            break;
        case 3:
            cout << "请要删除书籍的ISBN:";
            cin >> isbn;
            if (sys.remove(isbn))
                cout << "清除成功!" << endl;
            else
                cout << "库存中没有该书籍" << endl;
            break;
        case 4:
            sys.show_base();
            break;
        default:
            return 0;
            break;
        }
    }

    return 0;
}

void menu()
{
    cout << "图书管理系统" << endl;
    cout << " - 0: 借阅" << endl;
    cout << " - 1: 归还" << endl;
    cout << " - 2: 书籍入库" << endl;
    cout << " - 3: 清除库存" << endl;
    cout << " - 4: 凹入表显示AVL" << endl;
    cout << " - 其他: 退出" << endl;
    cout << ">";
}