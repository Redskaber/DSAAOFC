#pragma once

#ifndef __30_ͼ_����ͼ_�ڽӱ��ʵ��_H__
	#define __30_ͼ_����ͼ_�ڽӱ��ʵ��_H__

	/*
	ͼ_����ͼ_�ڽӱ��ʵ��
		G(V,E)
			- �ڽӱ�(����+����)ʵ�֣� V(G)�е��κ�һ�����㼴�Ƕ������Ҳ�Ǳ߱��㣬��һ����������Ϊ׼�򣬵ڶ�����������Ϊ׼��
			- �ڽӱ���������������ͼ����Ľṹ�壬����һ���������黹��������ͼ��Ϣ
			- ������������ݣ���¼��һ���ߵ�ָ�룬������Ϣ��
			- �߱����㵽�ٵ�ıߣ���¼�ٵ�INd��ָ����һ���ٵ㣩
	*/

#define MaxVexNum 100	 
typedef int VertexType;
// typedef int EdgeType;

typedef struct EdgeNode
{
	int adjVexInd;
	// EdgeType weight;
	struct EdgeNode* next;

}EdgeNode;


typedef struct VertexNode
{
	VertexType data;
	EdgeNode* firstEdge;
}VertexNode, AdjList[MaxVexNum];


typedef struct AdjacencyGraph
{
	AdjList adjlist;
	int vexNum, arcNum;
}AGraph;

#endif // !__30_ͼ_����ͼ_�ڽӱ��ʵ��_H__
