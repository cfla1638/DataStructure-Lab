#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int seqNumber;      // �洢ÿ���˵ı��
    int psd;            // �洢ÿ���˵�����
    struct node * next;
}Node, * NodePtr;

typedef struct
{
    NodePtr rear;       // �洢ѭ�������βָ��
    int length;
}CirLinkedList;

void InitList(CirLinkedList *);
void append(CirLinkedList *, int, int);
void CreateList(CirLinkedList *);
int empty(const CirLinkedList *);

// ɾ��NodePtrָ���Ԫ�أ�����NodePtrָ���ɾ����Ԫ�ص�ǰ��
void Remove(CirLinkedList *, NodePtr *);

void traverse(const CirLinkedList *);

int main(void)
{
    int m, step;
    NodePtr p;
    CirLinkedList L;
    
    InitList(&L);
    CreateList(&L);
    p = L.rear;
    printf("������m�ĳ�ֵ:");
    scanf("%d", &m);

    traverse(&L);

    while (!empty(&L)) {
        step = m % L.length;
        for (int i = 0; i < step; i++)
            p = p->next;
        printf("Number %d out\n", p->seqNumber);
        m = p->psd;
        Remove(&L, &p);
    }

    return 0;
}


void InitList(CirLinkedList * L)
{
    L->rear = NULL;
    L->length = 0;
}

inline int empty(const CirLinkedList * L)
{
    return !(L->length);
}

void append(CirLinkedList * L, int sq, int psd)
{
    NodePtr p = (NodePtr)malloc(sizeof(Node));
    p->seqNumber = sq;
    p->psd = psd;
    
    if (empty(L)) {
        L->rear = p;
        p->next = p;
    }
    else {
        p->next = L->rear->next;
        L->rear->next = p;
        L->rear = p;
    }
    L->length++;
}

void CreateList(CirLinkedList * L)
{
    int cnt, psd;

    printf("�������:");
    scanf("%d", &cnt);
    for (int i = 0; i < cnt; i++) {
        printf("������Ԫ��%d������:", i + 1);
        scanf("%d", &psd);
        append(L, i + 1, psd);
    }
}

void traverse(const CirLinkedList * L)
{
    if (empty(L)) return ;
    NodePtr p = (L->rear)->next;

    for (int i = 0; i < L->length + 1; i++) {
        printf("%4d ", p->seqNumber);
        p = p->next;
    }
    p = L->rear->next;
    printf("\n");
    for (int i = 0; i < L->length + 1; i++) {
        printf("%4d ", p->psd);
        p = p->next;
    }
    printf("\n");
}

void Remove(CirLinkedList * L, NodePtr *p)
{
    NodePtr prev = L->rear, t = *p;
    while (prev->next != (*p))
        prev = prev->next;
    prev->next = (*p)->next;
    *p = prev;
    if (t == L->rear) L->rear = prev;
    free(t);
    L->length--;
    if (L->length == 0)
        *p = NULL;
}