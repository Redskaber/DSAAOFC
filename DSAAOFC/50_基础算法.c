#include<stdio.h>
#include<stdlib.h>

#include "51_�����㷨_ð������.h"
#include "52_�����㷨_ѡ������.h"
#include "53_�����㷨_��������.h"
#include "54_�����㷨_ϣ���㷨.h"
#include "55_�����㷨_�鲢�㷨.h"
#include "56_�����㷨_��������.h"
#include "57_�����㷨_������.h"
#include "58_�����㷨_��������.h"
#include "59_�����㷨_Ͱ����.h"
#include "60_�����㷨_��������.h"

int start_sort()
{
	int arr[10] = {13,27,32,49,11,3,36,58,64,70};
	bubble_sort(10, arr);
	select_sort(10, arr);
	insert_sort(10, arr);
	shell_sort(10, arr);
	merge_sort(10, arr);
	quick_sort(arr, 10);
	heap_sort(arr, 10);
    counting_sort(arr, 10);
	bucket_sort(arr, 10);
	radix_sort(arr, 10);

	return 0;
}
