#include<stdio.h>
#include<stdlib.h>


int insert_sort(int arrlen, int *arr)
{
	/*前面部分区间作为有序序列，后面部分作为排序序列*/
	int i, j, temp;
	for (i = 1; i < arrlen; i++)
	{
		if (arr[i - 1] > arr[i])
		{
			temp = arr[i];	
			for (j = i - 1; j >= 0 && arr[j] > temp; j--) arr[j + 1] = arr[j];	/*获取有序插入位置*/
			arr[j + 1] = temp;
		}
	}
	for (int i = 0; i < arrlen; i++) printf("%d ", arr[i]); printf("\n");
	return arr;
}

