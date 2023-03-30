#pragma once


#ifndef __40_ͼ_����ͼ_ʮ�������ʵ��_H__
	#define __40_ͼ_����ͼ_ʮ�������ʵ��_H__
	#include <stdbool.h>
	/* ͼ_����ͼ_ʮ�������ʵ�� */

	/*
		G(V,E)
		 - V(G)		�����
		 - E(G)		�߱�
		 - ʮ�������ڽӱ������ڽӱ�)
	*/
	#define VexMaxNum		10		// ��󶥵���
	#define VexRelaArrNum	6		// �ⲿ���붥���ϵ����ָ��
	#define	VexMaxDistance	65535	// �����붥��֮�����Ϊ inf
	#define	VexMinDistance	0		// �����붥��֮�����Сֵ
	typedef int EdgeType;
	typedef int VertexType;

	/*��������temp*/
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


	/*�ߴ���*/
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

	/*�߱�*/
	typedef struct EdgeNode
	{	
		InEdge* inEdgeSet;
		OutEdge* outEdgeSet;
	}EdgeNode;


	/*�����*/
	typedef struct VertexNode
	{
		VertexType data;
		EdgeNode* vexEdgeSet;
	}VertexNode, *CrossList[VexMaxNum];


	/*Prim �㷨temp*/
	typedef struct PRIMTOOL
	{
		bool*   vexVisited;				// ���ÿ�������Ƿ��Ѿ�����������, ����¼����������ͼ�Ķ�����ʱ����ʾ������Ϊtrue �Ķ����ʾ�Ѿ����ʹ���
		int			length;				// ��¼�Ѿ����ʹ��Ķ����� �Ѿ����ʹ��Ķ�������ÿ����Ѱ��СȨ�ض�ʱ��minTree�е��ڽӶ�������ң����Ʒ���״����Ѱ��			
	}PrimTool;

	/*Kruskal�㷨temp*/
	typedef struct KEdge
	{
		int startVexInd, endVexInd;		// ��¼ͼ�е����бߵ���ʼ���յ�
		EdgeType weight;				// ��¼�ߵ�Ȩ��
	}KEdge, **KEdgeArr;
	
	typedef struct KRUSKALTOOL
	{
		KEdgeArr edgearr;				// �����洢�ߵļ��� 
		int *parent;					// ����parent���������жϱ�����Ƿ��γɻ�·  ��ʼ��Ϊ0	
		int edgeSize;
		int length;						// �жϱ���ӵ�minTree����Ŀ

	}KruskalTool;

	/*��С������*/
	typedef struct MinHeap				// ��С��
	{
		KEdge** edgeArr;				// ά��һ��edge�߼�����
		int length;
		int capacity;

		KEdge*	(*getWeightMinEdge)		(struct MinHeap* minHeap);
		void	(*minHeapInsert)		(struct MinHeap* minHeap, KEdge* edge);
		void	(*printMinHeapEdgeArr)	(struct MinHeap* minHeap);
	}MinHeap;


	/*Dijkstra�㷨�����·��*/
	typedef struct DijkstraTool
	{
		int  *distic;					// ����֮��ľ��� 
		bool *visited;					// ��¼����֮���Ƿ����
		int  vlength;					// ��¼����ķ��ʸ���
		int startVexInd;
		int endVexInd;
	}DijkstraTool;

	/*Flody�㷨�����·��*/



	/*ʮ������*/
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


#endif // !__40_ͼ_����ͼ_ʮ�������ʵ��_H__
