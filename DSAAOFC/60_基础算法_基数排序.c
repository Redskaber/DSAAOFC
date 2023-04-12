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

	exp = 1;		// ����λ��
	radix = 10;		// ���ƽ���
	int maxcNum = maxCompareNum(arr, len);	/*��ȡ�����е����ֵ����ͨ���˻�ȡλ�Ƚϴ���*/

	/*������ֻ��Ҫ�Ƚ������ֵ�ĸ���λֵ֮�伴��*/
	while (maxcNum--)
	{
		/*���ü�����*/
		int bucket[10] = { 0 };
		/*ʹ��Ͱ��¼ÿ����*/ 
		for (i = 0; i < len; i++) {
			bucket[(arr[i] / exp) % radix]++;		// (arr[i] / exp) ��ʾȡ��ֵ�еĽ���λ����������Ͱ��
		}

		/*��¼���ݴ��Ͱ��λ����Ϣ:*/ 
		for (i = 1; i < radix; i++) {
			bucket[i] += bucket[i - 1];
		}

		/*��������л����Ƚ�*/
		for (i = len - 1; i >= 0; i--) {
			temp[--bucket[((arr[i]) / exp) % radix]] = arr[i];		// ((arr[i]) / exp) % radix: (arr[i]) / exp����ֵ�Ľ���λ��% radix:ѡ���Ͱindex
		}

		/*����������Ϣ*/
		for (i = 0; i < len; i++) {
			arr[i] = temp[i];
		}

		/*���Ƹ�λ*/
		exp *= radix;		
	}
	dispaly(arr, len);
}
