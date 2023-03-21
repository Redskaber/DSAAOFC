#pragma once


#ifndef __40_ͼ_����ͼ_�ڽӶ��ر�ʵ��_H__
	#define __40_ͼ_����ͼ_�ڽӶ��ر�ʵ��_H__

	/*�ڽӶ��ر�(�ڽӱ��˫�����ʽ��left,right,llink,rlink��)*/
	
	typedef int EdgeType;
	typedef int VertexType;

	/*�ڽӶ��أ��߱�*/
	typedef struct EdgeNode
	{
		/*left(default) <--->right*/
		EdgeType weight;
		int leftVexInd;
		int rightVexInd;
		struct EdgeNode* leftEdgeNextLink;
		struct EdgeNode* rightEdgeNextLink;
	}EdgeNode;

	/*�ڽӶ��أ������*/
	typedef struct VertexNode
	{
		VertexType data;
		EdgeNode* firstEdge;
	}VertexNode, *AdjList;

	/*�ڽӶ��أ��ڽӶ��ر�*/
	typedef struct AdjacencyMultipleGraph
	{
		AdjList adjlist;
		int vexNum, arcNum;
	}AMGraph;

#endif // !__40_ͼ_����ͼ_�ڽӶ��ر�ʵ��_H__
