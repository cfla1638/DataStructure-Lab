#ifndef H_EXPR
#define H_EXPR

namespace Expr {
    class Expr
    {
    public:
        // 拷贝控制使用编译器生成的版本即可
        Expr();
        Expr(const char *);
        double eval() const;
        void set(const char *);

        // 错误处理
        mutable int Errno = 0;      // 错误代码
        const char * strErrno();    // 返回错误说明字符串

        enum {      // Errno的两种错误代码
            DivByZero = 1,
            SyntaxError = 2
        };

    private:
        static const int MaxLine = 512;
        char expression[MaxLine];
    };
}

#endif
