#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /**
     * len      ��
     * list     ˳���
     * m        �����m
     * curlen   ����ʱ��ɾ������Ԫ�غ�ʣ��ı�
     * cur      �α�
     */
    int len, * list, m, curlen, cur;
    
    // input
    printf("�������:");
    scanf("%d", &len);
    curlen = len;
    cur = len - 1;
    list = (int *)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        printf("������Ԫ��%d������:", i + 1);
        scanf("%d", &list[i]);
    }
    printf("������m�ĳ�ֵ:");
    scanf("%d", &m);

    // slove
    while (curlen > 0) {
        for (int i = 0; i < m; ) {
            cur = ((++cur) % len);
            if (list[cur] > 0)
                i++;
        }
        m = list[cur];
        list[cur] = -list[cur];
        printf("Number %d out\n", cur + 1);
        curlen--;
    }

    // free
    free(list);
    return 0;
}