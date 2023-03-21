#pragma once


#ifndef __40_图_有向图_十字链表的实现_H__
	#define __40_图_有向图_十字链表的实现_H__
	
	/* 图_有向图_十字链表的实现 */

	/*
		G(V,E)
		 - V(G)		顶点表
		 - E(G)		边表
		 - 十字链表（邻接表，逆向邻接表)
	*/
	typedef int EdgeType;
	typedef int VertexType;

	/*边表*/
	typedef struct EdgeNode
	{	
		EdgeType weight;
		int VexInInd;
		int VexOutInd;
		EdgeNode* nextVexIn;
		EdgeNode* nextVexOut;
	}EdgeNode;

	/*顶点表*/
	typedef struct VertexNode
	{
		VertexType data;
		EdgeNode* firstVexIn;
		EdgeNode* firstVexOut;
	}VertexNode, *CrossList;

	/*十字链表*/
	typedef struct CrossLinkGraph
	{
		CrossList crossList;
		int vexNum, arcNum;
	}CLGraph;


#endif // !__40_图_有向图_十字链表的实现_H__
