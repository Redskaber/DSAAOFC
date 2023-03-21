#pragma once

#ifndef __40_ͼ_����ͼ_�߼�����ʵ��_H__
	#define __40_ͼ_����ͼ_�߼�����ʵ��_H__

	/*
		����ͼ_�߼�����
		G(V,E)
			- V(G)	�����
			- E(G)	�߱�
		- G(V,E) 
			��������
			������
	*/

	typedef int EdgeType;
	typedef int VertexType;
	
	/*�߼����飺�߱�*/
	typedef struct EdgeNode
	{
		EdgeType weight;		// �ߵ�Ȩ��
		int begin;				// �ߵ���ʼ
		int end;				// �ߵ��ն�
	}EdgeNode, *EdgeArr;

	/*�߼����飺�����*/
	typedef struct VertexNode
	{
		VertexType data;		// �����ֵ
	}VertexNode, *VertexArr;

	/*�߼����飺�߼�����*/
	typedef struct EdgeSetGraph
	{
		EdgeArr edgearr;		// �߼�
		VertexArr vertexarr;	// ���㼯
		int arcNum, vexNum;
	}ESGraph;

#endif // !__40_ͼ_����ͼ_�߼�����ʵ��_H__

