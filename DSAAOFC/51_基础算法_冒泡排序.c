#include<stdio.h>
#include<stdlib.h>


int* bubble_sort(int arrLen, int *arr)
{
	for (int per = 0; per < arrLen; per++)
	{
		for (int next = 0; next < arrLen - 1; next++)
		{
			if (arr[next] > arr[next+1])
			{
				int temp = arr[next];
				arr[next] = arr[next + 1];
				arr[next + 1] = temp;
			}
		}
	}
	for (int i = 0; i < arrLen; i++) printf("%d ", arr[i]); printf("\n");
	return arr;
}