#pragma once

#ifndef __30_ͼ_����ͼ_�ڽӱ��ʵ��_H__
	#define __30_ͼ_����ͼ_�ڽӱ��ʵ��_H__

	/*
	ͼ_����ͼ_�ڽӱ��ʵ��
		G(V,E)
			- �ڽӱ�(����+����)ʵ�֣� V(G)�е��κ�һ�����㼴�Ƕ������Ҳ�Ǳ߱��㣬��һ����������Ϊ׼�򣬵ڶ�����������Ϊ׼��
			- �ڽӱ���������������ͼ����Ľṹ�壬����һ���������黹��������ͼ��Ϣ
			- ������������ݣ���¼��һ���ߵ�ָ�룬������Ϣ��
			- �߱����㵽�ٵ�ıߣ���¼�ٵ�INd��ָ����һ���ٵ㣩
	*/

	#define MaxVexNum 100	 
	#define vertexInNum 6	 
	typedef int VertexType;
	// typedef int EdgeType;

	typedef struct QUEUE
	{
		int queue[MaxVexNum];
		int length;
	}Queue;

	typedef struct EdgeNode
	{
		int adjVexInd;
		// EdgeType weight;
		struct EdgeNode* next;

	}EdgeNode;


	typedef struct VertexNode
	{
		VertexType data;
		EdgeNode* firstEdge;
	}VertexNode, *AdjList[MaxVexNum];


	typedef struct AdjacencyGraph
	{
		AdjList adjlist;
		int vexNum, arcNum;
	}AGraph;

	Queue queue;

	extern void adjGraphInit(AGraph* agp, int vexNum, VertexType* vexArr, VertexType (*vexRela)[vertexInNum]);
	extern void printAGraph(AGraph* agp);
	extern void destroyAGraph(AGraph* agp);
	extern void printRelaArr(VertexType(*vexRelaArr)[vertexInNum]);
	extern void _depthFirstSearch(AGraph* agp, int adjInd);
	extern void depthFirstSearch(AGraph* agp, VertexType startVex);
	extern void printVexNodeLink(AGraph* agp, int adjInd);

#endif // !__30_ͼ_����ͼ_�ڽӱ��ʵ��_H__
