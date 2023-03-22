#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "20_ͼ_����ͼ_�ڽӾ����ʵ��.h"

/*
	ͼ_����ͼ���ڽӾ���ʵ���ļ�

	G(V,E)		// ͼ�Ķ���һ��Ҫ��(V>0),��ͼ�ı߿���û��(E>=0)
		- INIT
			-> Vertex		>  0
			-> Edge			>= 0

		����ͼ��Ȩ�صĳ�ʼ��
		�����ⲿ����ͼ�Ķ������������Ϊ�������д���ͼ
		:int verNum  ������
		:int arcNum  ����		 ���������������Ĭ��ѡ��������ӣ�(VerNum-1)*VerNum��/2
		1 - (0*1)/2 = 0
		2 - (1*2)/2 = 1
		3 - (2*3)/2 = 3
		4 - (3*4)/2 = 6
		n - (n-1*n)/2
*/

static bool depthvisited[MaxVertexNum];	//���ʱ������
static bool breadthvisited[MaxVertexNum];	//���ʱ������

static int vertexDgree(UGraph* ugp, int vertex);
static int vertexInGraph(UGraph* ugp, int vertex);
static void depthFirstSearch(UGraph* ugp);
static void printArcArr(UGraph* ugp);
static void printVexArr(UGraph* ugp);
static void breadthFirstSearch(UGraph* ugp);

void createUGraphInit(UGraph* ugp, int vexNum, int arcNum)
{
	assert(vexNum <= MaxVertexNum);
	int maxArcNum = (vexNum * (vexNum - 1)) / 2;
	if (arcNum > maxArcNum) arcNum = maxArcNum;

	memset(ugp, 0, sizeof(UGraph));
	ugp->vexNum = vexNum;
	ugp->arcNum = arcNum;

	/*�����Ĭ�ϴ�0��ʼ*/
	for (int i = 0; i < ugp->vexNum; i++) ugp->vexArr[i] = i;
	/*�߱�����Ｋ��*/
	int arcTemp = arcNum;
	for (int row = 0; row < ugp->vexNum; row++)
	{
		for (int col = 0; col < ugp->vexNum; col++) 
		{
			if (row == col) ugp->edgeArr[row][col] = notex;		// �Խ���
			if (row != col)
			{
				if (ugp->edgeArr[col][row]) ugp->edgeArr[row][col] = exist;		// �Խ��߶���
				else
				{
					if (arcTemp-- > 0) ugp->edgeArr[row][col] = exist;			// �µı�
					else ugp->edgeArr[row][col] = notex;			
				}
			}
			printf("%d ", ugp->edgeArr[row][col]);
		}
		printf("\n");
	}

	ugp->printArcArr = printArcArr;
	ugp->printVexArr = printVexArr;
	ugp->vertexInGraph = vertexInGraph;
	ugp->vertexDgree = vertexDgree;
	ugp->depthFirstSearch = depthFirstSearch;
	ugp->breadthFirstSearch = breadthFirstSearch;
}

static int vertexInGraph(UGraph* ugp, int vertex)
{
	for (int i = 0; i < ugp->vexNum; i++)
		if (ugp->vexArr[i] == vertex) return i;		// row for
	return -1;
}

static int vertexDgree(UGraph* ugp, int vertex)
{
	int cout = 0;
	int inInd = vertexInGraph(ugp, vertex);
	if (inInd != -1)
	{
		for (int i = 0; i < ugp->vexNum; i++)
			if (ugp->edgeArr[inInd][i] != notex) cout++;
	}
	return cout;
}

static void visit(UGraph* ugp, int vexInd)
{
	printf("%d ",ugp->vexArr[vexInd]);
}

static int depthfirstNeihbor(UGraph* ugp, int vexInd)
{
	//��ͼG�ж���v�ĵ�һ���ڽӵ㣬�����򷵻ض����±꣬���򷵻�-1��
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		/*�ߴ��ڲ�����δ����������*/
		if (ugp->edgeArr[row][col] != notex && !depthvisited[col]) return col;
		else if (ugp->edgeArr[row][col] != notex && depthvisited[col] && vexInd > 1) 
			depthfirstNeihbor(ugp, vexInd - 1); /*�߽����*/
	}

	return -1;
}

static int depthnextNeighbor(UGraph* ugp, int vexInd, int nextInd)
{
	//����ͼG�ж���vexInd�Ƕ���nextVex��һ���ڽӵ㣬���س�vexInd�ⶥ��nextVex	
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		int edgeEx = ugp->edgeArr[row][col];	// �ɶ���vex���ڽӵ����ж��㼯��
		if (edgeEx == exist && ugp->vexArr[vexInd]!= ugp->vexArr[nextInd] && !depthvisited[col]) return col;
	}
	return  -1;
}

static void DFS(UGraph* ugp, int vexInd)
{
	/*
	���ȷ���ͼ��ĳһ��ʼ����vexInd��Ȼ����vexInd������������vexInd�ڽ���δ�����ʵ���һ����nextVexInd���ٷ�����nextVexInd�ڽ���δ�����ʵ���һ����
	���ظ��������̡�
	*/
	int nextVexInd;
	visit(ugp, vexInd);
	depthvisited[vexInd] = true;

	nextVexInd = depthfirstNeihbor(ugp, vexInd);
	for (nextVexInd; nextVexInd > 0; nextVexInd) {
		if (!depthvisited[nextVexInd]) DFS(ugp, nextVexInd); 		//nextVexIndΪvexInd����δ���ʵ��ڽӶ���	
		nextVexInd = depthnextNeighbor(ugp, vexInd, nextVexInd);
	}
}

static void depthFirstSearch(UGraph* ugp)
{
	/*ͼ����������㷨�������������������
				0
			1		2
		3	4		5	6	
		=>0,1,3,4,2,5,6
	*/
	if (ugp->vexNum - 1 >= ugp->arcNum) return;
	memset(depthvisited, false, sizeof(depthvisited));
	for (int vexInd = 0; vexInd < ugp->vexNum; ++vexInd) 
		if (!depthvisited[vexInd]) DFS(ugp, vexInd);	// ���ʵ�һ������
	printf("\n");
}

static void queueInit(Queue* queue)
{
	memset(queue->queue, -1, sizeof(queue->queue));
	queue->length = 0;
}

static void enqueue(Queue* queue, int data)
{
	queue->queue[queue->length++] = data;
}

static void unqueue(Queue* queue, int ind)
{
	for (int i = 0; i < queue->length; i++)
	{
		if (i == queue->length - 1) queue->queue[i] = -1;
		else if (i >= ind) queue->queue[i] = queue->queue[i + 1];
	}
	queue->length--;
}

static bool queueEmpty(Queue* queue)
{
	return queue->length == 0;
}

static void printQueue(Queue* queue)
{
	for (int i = 0; i < queue->length; i++) 
		printf("%d ", (int)queue->queue[i]);
	printf("\n");
}

static int breadthfirstNeihbor(UGraph* ugp, int vexInd)
{
	//��ͼG�ж���v�ĵ�һ���ڽӵ㣬�����򷵻ض����±꣬���򷵻�-1��
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		/*�ߴ��ڲ�����δ����������*/
		if (ugp->edgeArr[row][col] != notex && !breadthvisited[col]) return col;
		else if (ugp->edgeArr[row][col] != notex && breadthvisited[col] && vexInd > 1) 
			breadthfirstNeihbor(ugp, vexInd - 1); /*�߽����*/
	}

	return -1;
}

static int breadthnextNeighbor(UGraph* ugp, int vexInd, int nextInd)
{
	//����ͼG�ж���vexInd�Ƕ���nextVex��һ���ڽӵ㣬���س�vexInd�ⶥ��nextVex		
	int row = vexInd, col;
	for (col = 0; col < ugp->vexNum; col++)
	{
		int edgeEx = ugp->edgeArr[row][col];	// �ɶ���vex���ڽӵ����ж��㼯��
		if (edgeEx == exist && ugp->vexArr[vexInd] != ugp->vexArr[nextInd] && !breadthvisited[col]) 
			return col;
	}
	return  -1;
}

static void breadthFirstSearch(UGraph* ugp)
{
	/* ͼ�Ĺ�����ȱ����㷨�����������Ĳ㼶����
				0
			1		2
		3	4		5	6	
		=> 0,1,2,3,4,5,6
		queue
			v0 v1 v2 v3
		v0	0  1  1	 1
		v1	1  0  1	 1
		v2	1  1  0	 0
		v3	1  1  0	 0

		v0 -> queue[1,2,3] && visit(v0)  && breadthvisited[v0]
		for vex in (queue) -> breadthvisited[vex] && if(!breadthvisited[vex]) queue 
	*/
	if (ugp->vexNum - 1 >= ugp->arcNum) return;
	int nextVexInd;

	Queue queue;
	queueInit(&queue);
	memset(breadthvisited, false, sizeof(breadthvisited));
	for (int vexInd = 0; vexInd < ugp->vexNum; vexInd++)
	{
		if (!breadthvisited[vexInd])
		{
			visit(ugp, vexInd);				// ���ʶ���
			breadthvisited[vexInd] = true;	// ���
			enqueue(&queue, vexInd);		// ���˶��������

			while (!queueEmpty(&queue)) {	// ����ǰ���в�Ϊ��

				unqueue(&queue, vexInd);	// ����i������

				nextVexInd = breadthfirstNeihbor(ugp, vexInd);
				for (nextVexInd; nextVexInd >= 0; nextVexInd) {
					if (!breadthvisited[nextVexInd])
					{
						visit(ugp, nextVexInd);					// ���ʶ���
						breadthvisited[nextVexInd] = true;		// ���ʱ��
						enqueue(&queue, nextVexInd);			//����j�����
					}
					nextVexInd = breadthnextNeighbor(ugp, vexInd, nextVexInd);
				}
			}
		}
	};
}

static void printArcArr(UGraph* ugp)
{
	for (int row = 0; row < ugp->vexNum; row++)
	{
		for (int col = 0; col < ugp->vexNum; col++)
		{
			printf("%d ", ugp->edgeArr[row][col]);
		}
		printf("\n");
	}
}

static void printVexArr(UGraph* ugp)
{
	for (int i = 0; i < ugp->vexNum; i++) printf("%d ",ugp->vexArr[i]);
	printf("\n");
}