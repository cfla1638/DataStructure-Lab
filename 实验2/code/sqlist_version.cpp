#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /**
     * len      表长
     * list     顺序表
     * m        题面的m
     * curlen   处理时，删除部分元素后，剩余的表长
     * cur      游标
     */
    int len, * list, m, curlen, cur;
    
    // input
    printf("请输入表长:");
    scanf("%d", &len);
    curlen = len;
    cur = len - 1;
    list = (int *)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        printf("请输入元素%d的密码:", i + 1);
        scanf("%d", &list[i]);
    }
    printf("请输入m的初值:");
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