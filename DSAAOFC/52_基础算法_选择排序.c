#include<stdio.h>
#include<stdlib.h>



int select_sort(int arrlen, int* arr)
{
	/*从数组中选择最值并替换到第一个，剩下的继续*/

	int temp;
	for (int i = 0; i < arrlen - 1; i++)
	{
		int minInd = i;
		for (int j = i+1; j < arrlen; j++)
			if (arr[minInd] > arr[j]) minInd = j;
		temp = arr[i];
		arr[i] = arr[minInd];
		arr[minInd] = temp;
	}

	for (int z = 0; z < arrlen; z++) printf("%d ", arr[z]); printf("\n");
	return arr;
}

