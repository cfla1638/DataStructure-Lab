#ifndef H_SQLIST
#define H_SQLIST

class SqList
{
    friend void CreateSqList(SqList &);

public:
    typedef int ElemType;
    // ���캯�� & ��������
    SqList();
    explicit SqList(int size, int val = 0);
    SqList(const SqList &);
    ~SqList();
    SqList & operator=(const SqList &);

    // ���Ա����
    void traverse() const;
    void insert(int pos, ElemType elem);
    ElemType remove(int pos);
    ElemType getElem(int pos) const;
    ElemType getMaxElem() const;
    ElemType getMinElem() const; 
    int find(ElemType val) const;
    void reverse();

private:
    const int ListInitSize = 100;
    const int ListIncrement = 10;
    enum {Ok = 0, Error = 1, Overflow = 2};
    
    ElemType * base = nullptr;
    int length = 0;         // ��ǰ����
    int listSize = 0;       // ��ǰ����ռ��С
};

#endif