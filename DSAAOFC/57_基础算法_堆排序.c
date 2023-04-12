#include <stdio.h>
#include <stdlib.h>

static void display(int arr[], int len)
{
    for (int ind = 0; ind < len; ind++)
        printf("%d ",arr[ind]);
    printf("\n");
}

static void swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

static void max_heapify(int arr[], int start, int end) {
    // ���������cָ�˺��ӹ��cָ��
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) {               // ���ӹ��cָ���ڹ����Ȳ������^
        if (son + 1 <= end && arr[son] < arr[son + 1])      // �ȱ��^�ɂ��ӹ��c��С���x������
            son++;
        if (arr[dad] > arr[son])     // ��������c����ӹ��c�����{���ꮅ��ֱ����������
            return;
        else {                       // ��t���Q���Ӄ������^�m�ӹ��c�͌O���c���^
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heap_sort(int arr[], int len) {
    int i;
    // ��ʼ����i������һ�������c�_ʼ�{��
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    // �Ȍ���һ��Ԫ�غ����ź�Ԫ��ǰһλ�����Q���������{����ֱ�������ꮅ
    for (i = len - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        max_heapify(arr, 0, i - 1);
    }
    display(arr, len);
}