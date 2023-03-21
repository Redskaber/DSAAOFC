#pragma once

#ifndef __20_图_无向图_邻接矩阵的实现_H__
	#define __20_图_无向图_邻接矩阵的实现_H__
	#define MaxVertexNum 30
	#define exist 1
	#define notex 0
	typedef int VertexType;

	typedef struct QUEUE
	{
		VertexType queue[MaxVertexNum];
		int length;
	}Queue;

	typedef struct UndirectGraph
	{
		VertexType vexArr[MaxVertexNum];
		int edgeArr[MaxVertexNum][MaxVertexNum];
		int vexNum,arcNum;

	}UGraph;
	extern void createUGraphInit(UGraph* ugp, int vexNum, int arcNum);
	extern void printArcArr(UGraph* ugp);
	extern void printVexArr(UGraph* ugp);
	extern int vertexInGraph(UGraph* ugp, int vertex);
	extern int vertexDgree(UGraph* ugp, int vertex);
	extern void depthFirstSearch(UGraph* ugp);
	extern void breadthFirstSearch(UGraph* ugp);

#endif // !__20_图_无向图_邻接矩阵的实现_H__
