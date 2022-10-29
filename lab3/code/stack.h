#ifndef H_STACK
#define H_STACK

namespace mystack {

    template <typename T>
    class stack
    {
    public:
        stack();
        stack(const stack &);
        stack & operator=(const stack &);
        ~stack() {delete[] baseptr;};

        // 提供类似STL的接口，方便调试
        void pop();
        void push(const T &);
        int size() const {return length; };
        T & top();
        bool empty() const {if (baseptr == topptr) return true; return false;}

    private:
        static const int MaxLength = 512;
        int length = 0;
        T * baseptr, * topptr;
    };

    template <typename T>
    stack<T>::stack() : length(0), baseptr(nullptr), topptr(nullptr)
    {
        baseptr = new T[MaxLength];
        topptr = baseptr;
    }

    template <typename T>
    T & stack<T>::top()
    {
        return *(topptr - 1);
    }

    template <typename T>
    void stack<T>::pop()
    {
        if (!this->empty()) {
            topptr--;
            length--;
        }
    }

    template <typename T>
    void stack<T>::push(const T &elem)
    {
        if (topptr - baseptr >= MaxLength)  // 栈满
            return ;
        *topptr++ = elem;
        length++;
    }

}       // namespace

#endif
