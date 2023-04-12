#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void print_arr(int* arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void counting_sort(int* arr, int len) {
    int* count_arr = malloc(100 * sizeof(int));     // ��Ҫָ�����������е����ֵ(���ֵ����Сֵ������͵����)
    assert(count_arr != NULL);
    int i, j, k, n=0;

    /*���������ʼ��*/
    for (i = 0; i < 100; i++)
        count_arr[i] = 0;

    /*�������е�ֵ��ȡ���޸ļ��������е�ֵ*/
    for (j = 0; j < len; j++)
        count_arr[arr[j]]++;

    /*��ȡ���������ֵ����������*/
    for (k = 0; k < 100; k++)
        while (count_arr[k]-- != 0) arr[n++] = k;

    print_arr(arr, len);
    free(count_arr);
}