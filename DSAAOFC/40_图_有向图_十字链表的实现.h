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

	/*ʮ������*/
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


#endif // !__40_ͼ_����ͼ_ʮ�������ʵ��_H__
