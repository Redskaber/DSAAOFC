#pragma once


#ifndef __40_图_有向图_十字链表的实现_H__
	#define __40_图_有向图_十字链表的实现_H__
	#include <stdbool.h>
	/* 图_有向图_十字链表的实现 */

	/*
		G(V,E)
		 - V(G)		顶点表
		 - E(G)		边表
		 - 十字链表（邻接表，逆向邻接表)
	*/
	#define VexMaxNum		10		// 最大顶点数
	#define VexRelaArrNum	6		// 外部传入顶点关系数组指针
	#define	VexMaxDistance	65535	// 顶点与顶点之间距离为 inf
	#define	VexMinDistance	0		// 顶点与顶点之间的最小值
	typedef int EdgeType;
	typedef int VertexType;

	/*遍历缓存temp*/
	typedef struct DepthVisited
	{
		bool* depthVisited;
		int length;
	}DVisited;

	typedef struct BreadthVisited
	{
		bool* breadthVisited;
		int length;
	}BVisited;

	typedef struct STACK
	{
		int* stack;
		int length;
	}Stack;


	/*边处理*/
	typedef struct InEdgeSet
	{
		EdgeType inWeight;
		int inVexInd;
		struct InEdge* next;
	}InEdge;

	typedef struct OutEdgeSet
	{
		EdgeType outWeight;
		int outToVexInd;
		struct OutEdge* next;
	}OutEdge;

	/*边表*/
	typedef struct EdgeNode
	{	
		InEdge* inEdgeSet;
		OutEdge* outEdgeSet;
	}EdgeNode;


	/*顶点表*/
	typedef struct VertexNode
	{
		VertexType data;
		EdgeNode* vexEdgeSet;
	}VertexNode, *CrossList[VexMaxNum];


	/*Prim 算法temp*/
	typedef struct PRIMTOOL
	{
		bool*   vexVisited;				// 标记每个顶点是否已经加入生成树, 当记录的数量等于图的顶点数时，表示结束，为true 的顶点表示已经访问过了
		int			length;				// 记录已经访问过的顶点数 已经访问过的顶点数（每次找寻最小权重都时从minTree中的邻接顶点边中找，类似辐射状的找寻）			
	}PrimTool;

	/*Kruskal算法temp*/
	typedef struct KEdge
	{
		int startVexInd, endVexInd;		// 记录图中的所有边的起始与终点
		EdgeType weight;				// 记录边的权重
	}KEdge, **KEdgeArr;
	
	typedef struct KRUSKALTOOL
	{
		KEdgeArr edgearr;				// 用来存储边的集合 
		int *parent;					// 定义parent数组用来判断边与边是否形成环路  初始化为0	
		int edgeSize;
		int length;						// 判断边添加到minTree的数目

	}KruskalTool;

	/*最小堆排序*/
	typedef struct MinHeap				// 最小堆
	{
		KEdge** edgeArr;				// 维护一个edge边集数组
		int length;
		int capacity;

		KEdge*	(*getWeightMinEdge)		(struct MinHeap* minHeap);
		void	(*minHeapInsert)		(struct MinHeap* minHeap, KEdge* edge);
		void	(*printMinHeapEdgeArr)	(struct MinHeap* minHeap);
	}MinHeap;


	/*Dijkstra算法：最短路径*/
	typedef struct DijkstraTool
	{
		int  *distic;					// 顶点之间的距离 
		bool *visited;					// 记录顶点之间是否访问
		int  vlength;					// 记录顶点的访问个数
		int startVexInd;
		int endVexInd;
	}DijkstraTool;

	/*Flody算法：最短路径*/



	/*十字链表*/
	typedef struct CrossLinkGraph
	{
		CrossList crossList;
		int vexNum, arcNum;

		void (*printVexEdgeSet)			(struct CLGraph* clgp);
		void (*depthFirstSearch)		(struct CLGraph* clgp, int vexInd);
		void (*breadthFirstSearch)		(struct CLGraph* clgp, int vexInd);
		int  (*vertexInedgeNumber)		(struct CLGraph* clgp, int vexInd);
		int  (*vertexOutedgeNumber)		(struct CLGraph* clgp, int vexInd);
		void (*MinimumSpanTree_Prim)	(struct CLGraph* clgp, int vexInd);
		void (*MinimumSpanTree_Kruskal) (struct CLGraph* clgp);
		void (*shortPathDijkstra)	    (struct CLGraph* clgp, int startVexInd, int endVexInd);
		void (*shortPathFloyd)			(int(*vexRelaArr)[VexRelaArrNum]);



	}CLGraph;

	extern void CrossLinkGraphInit(CLGraph* clgp, int vexNum, VertexType vexArr[], VertexType(*vexRelaArr)[VexRelaArrNum]);
	extern void destroyCrossGraph(CLGraph* clgp);


#endif // !__40_图_有向图_十字链表的实现_H__
