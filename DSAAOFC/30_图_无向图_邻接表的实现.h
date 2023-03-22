#pragma once

#ifndef __30_图_无向图_邻接表的实现_H__
	#define __30_图_无向图_邻接表的实现_H__

	/*
	图_无向图_邻接表的实现
		G(V,E)
			- 邻接表(数组+链表)实现： V(G)中的任何一个顶点即是顶点表结点也是边表结点，第一个是以自身为准则，第二个是以他人为准则。
			- 邻接表本质上是用来管理图顶点的结构体，管理一个顶点数组还有其他的图信息
			- 顶点表（顶点数据，记录第一个边的指针，其它信息）
			- 边表（顶点到临点的边，记录临点INd与指向下一个临点）
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

#endif // !__30_图_无向图_邻接表的实现_H__
