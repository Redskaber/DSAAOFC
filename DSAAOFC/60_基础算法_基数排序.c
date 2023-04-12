#include<stdio.h>
#include<stdlib.h>


static void dispaly(int* arr, int len) {
	for (int i = 0; i < len; i++)
		printf("%d ",arr[i]);
	printf("\n");
}


int maxCompareNum(int *arr, int len){

	int maxcNum, maxData, radix, i;

	maxData = arr[0];
	for (i = 1; i < len; i++)
		if (arr[i] > maxData)
			maxData = arr[i];
	
	maxcNum = 1;
	radix = 10;
	while ((maxData >= radix))
	{
		maxData /= radix;
		maxcNum++;
	}

	return maxcNum;
}



void radix_sort(int* arr, int len) {

	int i, radix, exp;
	int temp[10];

	exp = 1;		// 控制位进
	radix = 10;		// 控制进制
	int maxcNum = maxCompareNum(arr, len);	/*获取数组中的最大值，并通过此获取位比较次数*/

	/*整体上只需要比较最大数值的各个位值之间即可*/
	while (maxcNum--)
	{
		/*重置计数器*/
		int bucket[10] = { 0 };
		/*使用桶记录每数量*/ 
		for (i = 0; i < len; i++) {
			bucket[(arr[i] / exp) % radix]++;		// (arr[i] / exp) 表示取数值中的进制位，将器放入桶中
		}

		/*记录数据存放桶的位置信息:*/ 
		for (i = 1; i < radix; i++) {
			bucket[i] += bucket[i - 1];
		}

		/*对数组进行基数比较*/
		for (i = len - 1; i >= 0; i--) {
			temp[--bucket[((arr[i]) / exp) % radix]] = arr[i];		// ((arr[i]) / exp) % radix: (arr[i]) / exp：数值的进制位；% radix:选择的桶index
		}

		/*更新数组信息*/
		for (i = 0; i < len; i++) {
			arr[i] = temp[i];
		}

		/*进制高位*/
		exp *= radix;		
	}
	dispaly(arr, len);
}
