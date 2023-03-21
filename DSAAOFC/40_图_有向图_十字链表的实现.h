#pragma once


#ifndef __40_ͼ_����ͼ_ʮ�������ʵ��_H__
	#define __40_ͼ_����ͼ_ʮ�������ʵ��_H__
	
	/* ͼ_����ͼ_ʮ�������ʵ�� */

	/*
		G(V,E)
		 - V(G)		�����
		 - E(G)		�߱�
		 - ʮ�������ڽӱ������ڽӱ�)
	*/
	typedef int EdgeType;
	typedef int VertexType;

	/*�߱�*/
	typedef struct EdgeNode
	{	
		EdgeType weight;
		int VexInInd;
		int VexOutInd;
		EdgeNode* nextVexIn;
		EdgeNode* nextVexOut;
	}EdgeNode;

	/*�����*/
	typedef struct VertexNode
	{
		VertexType data;
		EdgeNode* firstVexIn;
		EdgeNode* firstVexOut;
	}VertexNode, *CrossList;

	/*ʮ������*/
	typedef struct CrossLinkGraph
	{
		CrossList crossList;
		int vexNum, arcNum;
	}CLGraph;


#endif // !__40_ͼ_����ͼ_ʮ�������ʵ��_H__
