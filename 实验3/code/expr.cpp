#include <cmath>
#include <cstdio>
#include <cctype>
#include <cstring>

#include "expr.h"
#include "stack.h"

// 辅助函数
namespace {

    // 判断当前位置的字符是不是一个运算数
    int isopnd(char c)
    {
        if (isdigit(c))
            return 1;
        if (c == '.')
            return -1;
        return 0;
    }

    // 将运算符映射成索引
    int toIndex(char optr)
    {
        switch (optr)
        {
            case '+':
                return 0;
            case '-':
                return 1;
            case '*':
                return 2;
            case '/':
                return 3;
            case '(':
                return 4;
            case ')':
                return 5;
            case '^':
                return 6;
            case '#':
                return 7;
        }
        return -1;
    }

    // 存储不同运算符的优先级
    int priority[8][8] = {
        {1, 1, -1, -1, -1, 1, -1, 1},
        {1, 1, -1, -1, -1, 1, -1, 1},
        {1, 1, 1, 1, -1, 1, -1, 1},
        {1, 1, 1, 1, -1, 1, -1, 1},
        {-1, -1, -1, -1, -1, 0, -1, -2},
        {1, 1, 1, 1, -2, 1, 1, 1},
        {1, 1, 1, 1, -1, 1, 1, 1},
        {-1, -1, -1, -1, -1, -2, -1, 0}
    };

    // optr1的优先级是否大于optr2
    int precede(char optr1, char optr2)
    {
        return priority[toIndex(optr1)][toIndex(optr2)];
    }

    // 完成一次二元运算
    double evaluate(double opnd1, char optr, double opnd2)
    {
        switch (optr) {
            case '+':
            return opnd1 + opnd2;
            case '-':
            return opnd1 - opnd2;
            case '*':
            return opnd1 * opnd2;
            case '/':
            return opnd1 / opnd2;
            case '^':
            return pow(opnd1, opnd2);
        }
        return 0;
    }
}

namespace Expr {

    Expr::Expr()
    {
        memset(expression, 0, sizeof(expression));
        expression[0] = '#';
    }

    Expr::Expr(const char *str)
    {
        memset(expression, 0, sizeof(expression));
        // 复制
        strcpy(expression, str);

        // 移除所有的空格
        char * cur = expression;
        while (*cur != '\0') {
            if (isspace(*cur)) {
                int len = strlen(cur);
                for (int i = 0; i < len; i++)
                    cur[i] = cur[i + 1];
            }
            else
                cur++;
        }

        // 将所有的 ** 替换成 ^
        char * t;
        while ((t = strstr(expression, "**")) != NULL) {
            t[0] = '^'; t[1] = 0;
            strcat(expression, t + 2);
        }

        // 在字符串最后添加 '#'
        int len = strlen(expression);
        expression[len] = '#';
        expression[len+1] = 0;
    }

    // 设置当前的表达式
    void Expr::set(const char * str)
    {
        *this = Expr(str);
    }

    // 表达式求值
    double Expr::eval() const
    {
        // using std::stack;
        using mystack::stack;   // 最好用标准库的栈模板，因为是实验课，所以使用自己的栈模板
        const char *cur = expression;
        stack<char> optr;
        stack<double> opnd;
        Errno = 0;

        optr.push('#');
        while (*cur != '\0') {
            if (isopnd(*cur)) {
                double num;
                sscanf(cur, "%lf", &num);
                while (isopnd(*cur))
                    cur++;
                opnd.push(num);
            }
            else {
                switch (precede(optr.top(), *cur)) {
                    default :
                        Errno = SyntaxError;
                        return 0;
                    case -1:
                        optr.push(*cur);
                        cur++;
                        break;
                    case 0:
                        optr.pop();
                        cur++;
                        break;
                    case 1:
                        if (opnd.size() < 2) {
                            Errno = SyntaxError;
                            return 0;
                        }
                        double a, b = opnd.top();
                        char theta = optr.top();
                        optr.pop();
                        opnd.pop();
                        a = opnd.top(); opnd.pop();
                        if (b == 0) {
                            Errno = DivByZero;
                            return 0;
                        }
                        opnd.push(evaluate(a, theta, b));
                        break;
                }   // switch
            }   // else
        }   // while
        if (!optr.empty() || opnd.size() != 1) {
            Errno = SyntaxError;
            return 0;
        }
        return opnd.top();
    }

    const char * Expr::strErrno()
    {
        switch (Errno) {
            case DivByZero :
                return "Divide by zero";
            case SyntaxError :
                return "Syntax Error";
            default :
                return "";
        }
    }

}   // namespace
