#pragma once

#ifndef __20_图_无向图_邻接矩阵的实现_H__
	#define __20_图_无向图_邻接矩阵的实现_H__
	#define MaxVertexNum 30
	#define VexRelaArrNum 10
	#define WeightMax 65535
	#define exist 1
	#define notex 0
	typedef int VertexType;

	typedef struct STACK
	{
		VertexType stack[MaxVertexNum];
		int length;
	}Stack;

	typedef struct UndirectGraph
	{
		VertexType vexArr[MaxVertexNum];
		int edgeArr[MaxVertexNum][MaxVertexNum];
		int vexNum, arcNum;

		void (*printArcArr)(struct UGraph* ugp);
		void (*printVexArr)(struct UGraph* ugp);
		int  (*vertexInGraph)(struct UGraph* ugp, int vertex);
		int  (*vertexDgree)(struct UGraph* ugp, int vertex);
		void (*depthFirstSearch)(struct UGraph* ugp);
		void (*breadthFirstSearch)(struct UGraph* ugp);
		void (*MiniSpanTree_Prim)(struct UGraph* ugp);


	}UGraph;
	extern void createUGraphInit(UGraph* ugp, int vexNum, int vexArr[], int(*vexRelaArr)[VexRelaArrNum]);

#endif // !__20_图_无向图_邻接矩阵的实现_H__
