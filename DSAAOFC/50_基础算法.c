#include<stdio.h>
#include<stdlib.h>

#include "51_基础算法_冒泡排序.h"
#include "52_基础算法_选择排序.h"
#include "53_基础算法_插入排序.h"
#include "54_基础算法_希尔算法.h"
#include "55_基础算法_归并算法.h"
#include "56_基础算法_快速排序.h"
#include "57_基础算法_堆排序.h"
#include "58_基础算法_计数排序.h"
#include "59_基础算法_桶排序.h"
#include "60_基础算法_基数排序.h"

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
