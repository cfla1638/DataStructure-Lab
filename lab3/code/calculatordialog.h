#ifndef CALCULATORDIALOG_H
#define CALCULATORDIALOG_H
#include <QDialog>
#include "expr.h"

using Expr::Expr;
class QLabel;
class QPushButton;

class CalculatorDialog : public QDialog
{
    Q_OBJECT
public:
    CalculatorDialog(QWidget * parent = 0);

    // 共十九个按钮
    enum { Zero, One, Two, Three, Four, Five,
           Six, Seven, Eight, Nine, Point, Add,
           Sub, Mult, Div, Enter, LeftBracket,
           RightBracket, Clear };

public slots:
    // 按钮对应的槽函数
    void OneClicked();
    void TwoClicked();
    void ThreeClicked();
    void FourClicked();
    void FiveClicked();
    void SixClicked();
    void SevenClicked();
    void EightClicked();
    void NineClicked();
    void AddClicked();
    void SubClicked();
    void MultClicked();
    void DivClicked();
    void PointClicked();
    void ZeroClicked();
    void EnterClicked();
    void ClearClicked();
    void DeleteClicked();
    void LeftBracketClicked();
    void RightBracketClicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event);  // 事件过滤器

private:
    void handleKeyPressed(QKeyEvent * event);

    static const int btnCnt = 19;
    QString buf;    // 存储输入的表达式
    QLabel * screem;    // 显示计算结果的QLable
    class Expr * expression;    // 表达式求值的类
    QPushButton * pushButton[btnCnt];   // 存储所有按钮的指针
};

#endif // CALCULATORDIALOG_H
