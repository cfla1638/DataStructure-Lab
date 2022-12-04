#include <iostream>
#include <regex>
#include "libman.h"
using namespace std;

void menu();    // ��ӡ�˵�

int main(void)
{
    // ��ʼ������ϵͳ������ǰ��������
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
    regex r(pattern);   // ��֤�������ڵ�������ʽ
    while (true) {
        menu();
        cin >> opt;
        switch (opt)
        {
        case 0:
            cout << "���������֤��:";
            cin >> card_no;
            cout << "����������鼮��ISBN:";
            cin >> isbn;
            cout << "������黹����(yyyy-mm-dd):";
            cin >> date;
            while (!regex_match(date, r)) {
                cout << "���ڸ�ʽ����, ����������!" << endl << "������黹����(yyyy-mm-dd):";
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
                cout << "���ĳɹ�!" << endl; 
            break;
        case 1:
            cout << "���������֤��:";
            cin >> card_no;
            cout << "������黹�鼮��ISBN:";
            cin >> isbn;
            sys.Rentrn(card_no, isbn);
            break;
        case 2:
            cout << "�������鼮��ISBN:";
            cin >> isbn;
            cout << "����������:";
            cin >> name;
            cout << "�������鼮������:";
            cin >> author;
            sys.warehouse(book_entry_t(isbn, name, author, 1, 1));
            break;
        case 3:
            cout << "��Ҫɾ���鼮��ISBN:";
            cin >> isbn;
            if (sys.remove(isbn))
                cout << "����ɹ�!" << endl;
            else
                cout << "�����û�и��鼮" << endl;
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
    cout << "ͼ�����ϵͳ" << endl;
    cout << " - 0: ����" << endl;
    cout << " - 1: �黹" << endl;
    cout << " - 2: �鼮���" << endl;
    cout << " - 3: ������" << endl;
    cout << " - 4: �������ʾAVL" << endl;
    cout << " - ����: �˳�" << endl;
    cout << ">";
}