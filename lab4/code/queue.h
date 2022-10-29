#ifndef H_QUEUE
#define H_QUEUE

namespace myqueue {
    template <typename T>
    class queue
    {
    public:
        queue() = default;

        bool empty() const;
        T front() const;
        void pop();
        void push(T);
    private:
        static constexpr int MaxLength = 100;
        int head = 0, rear = 0;
        T base[MaxLength];
    };

    template <typename T>
    bool queue<T>::empty() const
    {
        if (head == rear)
            return true;
        return false;
    }

    template <typename T>
    T queue<T>::front() const
    {
        return base[rear];
    }

    template <typename T>
    void queue<T>::pop()
    {
        if (!empty())
            rear++;
    }

    template <typename T>
    void queue<T>::push(T t)
    {
        if (head + 1 != rear) {
            base[head++] = t;
        }
    }
}
#endif