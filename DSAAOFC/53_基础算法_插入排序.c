#include<stdio.h>
#include<stdlib.h>


int insert_sort(int arrlen, int *arr)
{
	/*ǰ�沿��������Ϊ�������У����沿����Ϊ��������*/
	int i, j, temp;
	for (i = 1; i < arrlen; i++)
	{
		if (arr[i - 1] > arr[i])
		{
			temp = arr[i];	
			for (j = i - 1; j >= 0 && arr[j] > temp; j--) arr[j + 1] = arr[j];	/*��ȡ�������λ��*/
			arr[j + 1] = temp;
		}
	}
	for (int i = 0; i < arrlen; i++) printf("%d ", arr[i]); printf("\n");
	return arr;
}

