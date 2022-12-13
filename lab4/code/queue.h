#ifndef H_QUEUE
#define H_QUEUE
#include <iostream>

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

    template<typename T>
    void queue<T>::push(T elem) 
    {
        if ((rear + 1) % MaxLength != head) {
            base[rear] = elem;
            rear = (rear + 1) % MaxLength;
        }
        else
            std::cerr << "queue::push(): queue is full!\n";
    }

    template <typename T>
    void queue<T>::pop()
    {
        if (head != rear)
            head = (head + 1) % MaxLength;
        else
            std::cerr << "queue::pop(): queue is empty\n";
    }

    template <typename T>
    T queue<T>::front() const
    {
        if (head != rear)
            return base[head];
        else {
            std::cerr << "queue::front(): queue is empty\n";
            std::abort();
        }
    }

    template <typename T>
    bool queue<T>::empty() const
    {
        return head == rear;
    }
}
#endif