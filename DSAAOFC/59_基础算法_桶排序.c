#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>


typedef struct BUCKET
{
	int* bucket;
	int length;
	int size;
}Bucket;


static Bucket* createBucket(int memNum)
{
	Bucket* newBucket = NULL;
	newBucket = (Bucket*)malloc(sizeof(Bucket));
	assert(newBucket !=NULL);
	newBucket->bucket = (int*)malloc(memNum * sizeof(int));
	assert(newBucket->bucket != NULL);
	memset(newBucket->bucket, 0, memNum * sizeof(int));
	newBucket->length = 0;
	newBucket->size = memNum;
	return newBucket;
}

static Bucket** createBucketArr(int bNum)
{
	Bucket** newBucketArr = NULL;
	newBucketArr = (Bucket**)malloc(bNum * sizeof(Bucket*));
	assert(newBucketArr != NULL);
	return newBucketArr;
}

static void destroyBucket(Bucket* bucket) {
	if (bucket)
	{
		free(bucket->bucket);
		free(bucket);
		bucket = NULL;
	}
}

static void destoryBucketArr(Bucket** bucketArr, int buckNum) {
	if (bucketArr)
	{
		for (int i = 0; i < buckNum; i++) destroyBucket(bucketArr[i]);
		free(bucketArr);
		bucketArr = NULL;
	}
}


static void push(Bucket* bucket, int data){
	assert(bucket->length <= bucket->size);
	bucket->bucket[bucket->length++]= data;
}

static void swap(const void* a, const void* b){
	return (*(int*)a) - (*(int*)b);
}

static void display(int* arr, int len) {
	for (int i = 0; i < len; i++)
		printf("%d ", arr[i]);
}

static void setbucketNumAndbMem(int* arr, int len, int* bnum, int* bmem){
	/*��������ĳ�����ֵ����Ͱ��Ͱ��Ա�ĳ�ʼ��*/
	int arrMax = arr[0];
	for (int i = 1; i < len; i++){
		if (arrMax < arr[i]) arrMax = arr[i];
	}

	*bnum = (int)sqrt(arrMax);
	*bmem = len;
}



/*��һ�����ݣ�����ָ���Ĺ���ƽ������m��Ͱ�У��Ե���Ͱ��������������*/
void bucket_sort(int* arr, int len){
	// coin:���ڵ����������غϵ���ֵʱ��

	int bInd, bnum, memnum, arrInd, Bindex;
	setbucketNumAndbMem(arr, len, &bnum, &memnum);
	Bucket** bucketArr = createBucketArr(bnum);
	Bucket*	bucket= NULL;

	// ��ʼ��Ͱ��m��,ÿ��Ͱ len / m ��
	for (bInd = 0; bInd < bnum; bInd++)
	{
		bucket = createBucket(memnum);
		bucketArr[bInd] = bucket;
	}

	/*�����ݴ����Ӧ��Ͱ�У�ʹ�ö���Ĺ���*/
	for (arrInd = 0; arrInd < len; arrInd++)
	{
		// 2Ϊ����Ӧ���ݷֵ���ͬͰ�еĹ���[0,1][2,3][4,5][6,7][8,9]
		Bindex = arr[arrInd] / 14;		
		push(bucketArr[Bindex], arr[arrInd]);
	}

	/*��ÿ��Ͱ��������������ʽ��*/
	for (bInd = 0; bInd < bnum; bInd++)
	{
		bucket = bucketArr[bInd];
		qsort(bucket->bucket, bucket->length, sizeof(int),swap);	// ʹ��c�Դ���qsort
		display(bucket->bucket, bucket->length);
	}
	destoryBucketArr(bucketArr, bnum);
	printf("\n");
}
