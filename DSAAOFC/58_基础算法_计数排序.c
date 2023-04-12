#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void print_arr(int* arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void counting_sort(int* arr, int len) {
    int* count_arr = malloc(100 * sizeof(int));     // 需要指定排序数组中的最大值(最大值、最小值，这里偷懒了)
    assert(count_arr != NULL);
    int i, j, k, n=0;

    /*计数数组初始化*/
    for (i = 0; i < 100; i++)
        count_arr[i] = 0;

    /*将数组中的值读取并修改计数数组中的值*/
    for (j = 0; j < len; j++)
        count_arr[arr[j]]++;

    /*读取计数数组的值并重新排序*/
    for (k = 0; k < 100; k++)
        while (count_arr[k]-- != 0) arr[n++] = k;

    print_arr(arr, len);
    free(count_arr);
}