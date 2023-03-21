#pragma once


#ifndef __40_图_有向图_邻接多重表实现_H__
	#define __40_图_有向图_邻接多重表实现_H__

	/*邻接多重表：(邻接表的双结点形式【left,right,llink,rlink】)*/
	
	typedef int EdgeType;
	typedef int VertexType;

	/*邻接多重：边表*/
	typedef struct EdgeNode
	{
		/*left(default) <--->right*/
		EdgeType weight;
		int leftVexInd;
		int rightVexInd;
		struct EdgeNode* leftEdgeNextLink;
		struct EdgeNode* rightEdgeNextLink;
	}EdgeNode;

	/*邻接多重：顶点表*/
	typedef struct VertexNode
	{
		VertexType data;
		EdgeNode* firstEdge;
	}VertexNode, *AdjList;

	/*邻接多重：邻接多重表*/
	typedef struct AdjacencyMultipleGraph
	{
		AdjList adjlist;
		int vexNum, arcNum;
	}AMGraph;

#endif // !__40_图_有向图_邻接多重表实现_H__
