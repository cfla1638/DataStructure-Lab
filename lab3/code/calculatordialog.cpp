#include <string>
#include <sstream>
#include <QLabel>
#include <QEvent>
#include <QTimer>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "calculatordialog.h"

CalculatorDialog::CalculatorDialog(QWidget * parent) :
    QDialog(parent),
    expression(new class Expr())
{
    QFont ft, btnft;

    // QLabel的字体
    ft.setBold(true);
    ft.setPointSize(20);
    btnft.setPointSize(25); // 所有按钮的字体样式

    // 创建并设置显示计算结果的QLabel
    screem = new QLabel();
    screem->setText("Keyboard Available");
    screem->setFont(ft);

    // 创建所有的按钮
    for (int i = Zero; i <= Nine; i++) {
        QPushButton *t = new QPushButton(QString(i + 48));
        pushButton[i] = t;
    }

    pushButton[Add] = new QPushButton("+");
    pushButton[Sub] = new QPushButton("-");
    pushButton[Mult] = new QPushButton("*");
    pushButton[Div] = new QPushButton("/");
    pushButton[Point] = new QPushButton(".");
    pushButton[Enter] = new QPushButton("=");
    pushButton[LeftBracket] = new QPushButton("(");
    pushButton[RightBracket] = new QPushButton(")");
    pushButton[Clear] = new QPushButton("CLR");

    pushButton[Enter]->setDefault(true);
    pushButton[Enter]->setFocus();

    // 设置所有按钮的字体
    for (int i = 0; i < btnCnt; i++)
        pushButton[i]->setFont(btnft);

    // 设置Widget的布局
    QHBoxLayout * row1 = new QHBoxLayout();
    QHBoxLayout * row2 = new QHBoxLayout();
    QHBoxLayout * row3 = new QHBoxLayout();
    QHBoxLayout * row4 = new QHBoxLayout();
    QHBoxLayout * row5 = new QHBoxLayout();
    QHBoxLayout * row6 = new QHBoxLayout();
    QVBoxLayout * mainLayout = new QVBoxLayout();

    row1->addWidget(screem);

    row2->addWidget(pushButton[LeftBracket]);
    row2->addWidget(pushButton[RightBracket]);
    row2->addWidget(pushButton[Add]);
    row2->addWidget(pushButton[Sub]);

    row3->addWidget(pushButton[Seven]);
    row3->addWidget(pushButton[Eight]);
    row3->addWidget(pushButton[Nine]);
    row3->addWidget(pushButton[Mult]);

    row4->addWidget(pushButton[Four]);
    row4->addWidget(pushButton[Five]);
    row4->addWidget(pushButton[Six]);
    row4->addWidget(pushButton[Div]);

    row5->addWidget(pushButton[One]);
    row5->addWidget(pushButton[Two]);
    row5->addWidget(pushButton[Three]);
    row5->addWidget(pushButton[Point]);

    row6->addWidget(pushButton[Zero]);
    row6->addWidget(pushButton[Clear]);
    row6->addWidget(pushButton[Enter]);

    mainLayout->addLayout(row1);
    mainLayout->addLayout(row2);
    mainLayout->addLayout(row3);
    mainLayout->addLayout(row4);
    mainLayout->addLayout(row5);
    mainLayout->addLayout(row6);
    setLayout(mainLayout);

    // 设置按钮对应的槽函数
    connect(pushButton[One], SIGNAL(clicked()), this, SLOT(OneClicked()));
    connect(pushButton[Two], SIGNAL(clicked()), this, SLOT(TwoClicked()));
    connect(pushButton[Three], SIGNAL(clicked()), this, SLOT(ThreeClicked()));
    connect(pushButton[Four], SIGNAL(clicked()), this, SLOT(FourClicked()));
    connect(pushButton[Five], SIGNAL(clicked()), this, SLOT(FiveClicked()));
    connect(pushButton[Six], SIGNAL(clicked()), this, SLOT(SixClicked()));
    connect(pushButton[Seven], SIGNAL(clicked()), this, SLOT(SevenClicked()));
    connect(pushButton[Eight], SIGNAL(clicked()), this, SLOT(EightClicked()));
    connect(pushButton[Nine], SIGNAL(clicked()), this, SLOT(NineClicked()));
    connect(pushButton[Add], SIGNAL(clicked()), this, SLOT(AddClicked()));
    connect(pushButton[Sub], SIGNAL(clicked()), this, SLOT(SubClicked()));
    connect(pushButton[Mult], SIGNAL(clicked()), this, SLOT(MultClicked()));
    connect(pushButton[Div], SIGNAL(clicked()), this, SLOT(DivClicked()));
    connect(pushButton[Point], SIGNAL(clicked()), this, SLOT(PointClicked()));
    connect(pushButton[Zero], SIGNAL(clicked()), this, SLOT(ZeroClicked()));
    connect(pushButton[Enter], SIGNAL(clicked()), this, SLOT(EnterClicked()));
    connect(pushButton[LeftBracket], SIGNAL(clicked()), this, SLOT(LeftBracketClicked()));
    connect(pushButton[RightBracket], SIGNAL(clicked()), this, SLOT(RightBracketClicked()));
    connect(pushButton[Clear], SIGNAL(clicked()), this, SLOT(ClearClicked()));

    installEventFilter(this);       // 安装事件过滤器
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);     // 删除默认窗口的help
}

// 事件过滤器：接受键盘事件
bool CalculatorDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    }
    else
        return QObject::eventFilter(watched, event);
}

// 处理键盘输入
void CalculatorDialog::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_0:
            ZeroClicked();
            break;
        case Qt::Key_1:
            OneClicked();
            break;
        case Qt::Key_2:
            TwoClicked();
            break;
        case Qt::Key_3:
            ThreeClicked();
            break;
        case Qt::Key_4:
            FourClicked();
            break;
        case Qt::Key_5:
            FiveClicked();
            break;
        case Qt::Key_6:
            SixClicked();
            break;
        case Qt::Key_7:
            SevenClicked();
            break;
        case Qt::Key_8:
            EightClicked();
            break;
        case Qt::Key_9:
            NineClicked();
            break;
        case Qt::Key_Plus:
            AddClicked();
            break;
        case Qt::Key_Minus:
            SubClicked();
            break;
        case Qt::Key_Asterisk:
            MultClicked();
            break;
        case Qt::Key_Slash:
            DivClicked();
            break;
        case Qt::Key_Enter:
            EnterClicked();
            break;
        case Qt::Key_Return:
            EnterClicked();
            break;
        case Qt::Key_Period:
            PointClicked();
            break;
        case Qt::Key_ParenLeft:
            LeftBracketClicked();
            break;
        case Qt::Key_ParenRight:
            RightBracketClicked();
            break;
        case Qt::Key_Delete:
        case Qt::Key_Backspace:
            DeleteClicked();
            break;
        case Qt::Key_C:
            ClearClicked();
            break;
    }
}

// 按下Enter, 调用Expr的接口进行计算
void CalculatorDialog::EnterClicked() {
    if (buf.isEmpty())
        return ;

    std::string str = buf.toStdString();
    expression->set(str.c_str());

    std::ostringstream stream;
    stream << expression->eval();

    QString ans = QString::fromStdString(stream.str());
    if (expression->Errno)
        screem->setText(expression->strErrno());
    else
        screem->setText(ans);
    buf.clear();
}

/* 以下是所有其他槽函数的定义 */

void CalculatorDialog::ClearClicked() {
    buf.clear();
    screem->setText("Keyboard Available");
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::OneClicked() {
    buf.append('1');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::TwoClicked() {
    buf.append('2');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::ThreeClicked() {
    buf.append('3');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::FourClicked() {
    buf.append('4');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::FiveClicked() {
    buf.append('5');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::SixClicked() {
    buf.append('6');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::SevenClicked() {
    buf.append('7');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::EightClicked() {
    buf.append('8');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::NineClicked() {
    buf.append('9');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::AddClicked() {
    buf.append('+');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::SubClicked() {
    buf.append('-');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::MultClicked() {
    buf.append('*');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::DivClicked() {
    buf.append('/');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}
void CalculatorDialog::PointClicked() {
    buf.append('.');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::ZeroClicked() {
    buf.append('0');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::LeftBracketClicked() {
    buf.append('(');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::RightBracketClicked() {
    buf.append(')');
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}

void CalculatorDialog::DeleteClicked() {
    buf = buf.left(buf.size() - 1);
    screem->setText(buf);
    pushButton[Enter]->setFocus();
}
