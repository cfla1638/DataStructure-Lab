#include <QApplication>
#include "calculatordialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalculatorDialog * dialog = new CalculatorDialog();
    dialog->show();
    return a.exec();
}
