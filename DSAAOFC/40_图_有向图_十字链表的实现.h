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

	/*十字链表*/
	typedef struct CrossLinkGraph
	{
		CrossList crossList;
		int vexNum, arcNum;

		void (*printVexEdgeSet)(struct CLGraph* clgp);
		void (*depthFirstSearch)(struct CLGraph* clgp, int vexInd);
		void (*breadthFirstSearch)(struct CLGraph* clgp, int vexInd);
	}CLGraph;

	extern void CrossLinkGraphInit(CLGraph* clgp, int vexNum, VertexType vexArr[], VertexType(*vexRelaArr)[VexRelaArrNum]);
	extern void destroyCrossGraph(CLGraph* clgp);


#endif // !__40_图_有向图_十字链表的实现_H__
